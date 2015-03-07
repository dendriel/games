package src
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.ui.Keyboard;
	import flash.text.TextField;
	import src.as3.io.KeyObject;
	import src.maps.GameMap;
	import src.as3.math.Calc;
	import src.tiles.ConstTile;
	import src.tiles.IElementTileInfo;
	import src.ui.GameTileDisplay;
	import src.ui.GameUnitDisplay;
	import src.ui.GameTextFormat;
	import src.as3.ui.Chat;
	import src.as3.ui.ChatInputEvent;
	import src.units.IElementUnitInfo;
	import src.units.GameUnit;
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * 
	 * +------------------------------------------------------------+ -\  
	 * |+----------------------------------------------------------+|
	 * |[                                                          ]|
	 * |[                                                          ]|
	 * |[                                                          ]|    gameMapScreen:MovieClip
	 * |[           loaded gameMapR:GameMap:MovieClip              ]|
	 * |[                                                          ]|
	 * |[                                                          ]|
	 * |[                                                          ]|
	 * |[                                                          ]|
	 * ++__________________________________________________________++  -/
	 * |    Status    |         Actions Display        |            |  -\
	 * |    Display   |                                |            |    gameMenuScreen:MovieClip
	 * +------------------------------------------------------------+  -/
	 */
	public class GamePlay extends MovieClip 
	{		
		// Images.
		private var gamePlayFrameR:GamePlayFrame; // Border drawing of the map.
		private var gameTarget:Target01; // Indication of what tile is in focus.
		
		// Screens.
		private var gameMapScreen:MovieClip;			// Contains the game map.
		private var gameMapScreenMask:MovieClip;		// Limits the game map view.
		private var gameMapR:GameMap;					// Loaded game map reference.
		private var gameMenuScreen:MovieClip;			// Contains the menu area.
		private var gameUnitDisplay:GameUnitDisplay;	// Unit status display.
		private var gameTileDisplay:GameTileDisplay;	// Tile status display.
		private var timer:GameTimer;					// Date/time object handler.
		
		// Input/Output.
		private var key:KeyObject;
		private var gameChat:Chat;
		// Chat Commands.
		private const spawnUnitCmd:String = "/spawn";
		
		// Internal state.
		private var mouseButtonDown:Boolean;
		private var mouseButtonPressPoint:Point;
		private var controlPressed:Boolean;
		private var cPressed:Boolean;
		
		// Info text.
		private var coorTxt:TextField;	// Coordinates in focus. Temporary TODO: remove.
		
		// Players.
		private var player:GamePlayer;
		
		public function GamePlay()
		{
			// Initialize internal variables.
			mouseButtonDown = false;
			mouseButtonPressPoint = new Point();
			gameTarget = new Target01();
			gameTarget.visible = false;
			
			// Unitialize Input/Output.
			key = new KeyObject(GameStage.stageR);
			controlPressed = false;
			gameChat = new Chat(Const.CHAT_WIDTH, Const.CHAT_HEIGHT);
			gameChat.x = Const.CHAT_POX_X;
			gameChat.y = Const.CHAT_POX_Y;
			gameChat.registerCallback(spawnUnitCmd, handleSpawnUnitCmd);
			gameChat.addText(GameLanguage.lang.chat_help_str, false);
			
			// Create displays.
			gameUnitDisplay = new GameUnitDisplay(Const.STATUS_DISPLAY_POS_X, Const.STATUS_DISPLAY_POS_Y);
			gameTileDisplay = new GameTileDisplay(Const.STATUS_DISPLAY_POS_X, Const.STATUS_DISPLAY_POS_Y);
			
			// Load game frame.
			gamePlayFrameR = new GamePlayFrame();
			gamePlayFrameR.x = 0;
			gamePlayFrameR.y = 0;
			addChild(gamePlayFrameR);
			
			// Create Mask and Game Map.
			gameMapScreenMask = new MovieClip();
			gameMapScreenMask.graphics.beginFill(0x7ebff1);
            gameMapScreenMask.graphics.drawRect(0, 0, Const.MAP_AREA_W, Const.MAP_AREA_H);
			gameMapScreenMask.graphics.endFill();
			gameMapScreenMask.x = Const.MAP_AREA_POS_X;
			gameMapScreenMask.y = Const.MAP_AREA_POS_Y;
			
			gameMapScreen = new MovieClip();
			gameMapScreen.x = Const.MAP_AREA_POS_X;
			gameMapScreen.y = Const.MAP_AREA_POS_Y;
			gameMapScreen.mask = gameMapScreenMask;
			
			// Create Game Menu screen.
			gameMenuScreen = new MovieClip();
			gameMenuScreen.x = Const.MENU_AREA_POS_X;
			gameMenuScreen.y = Const.MENU_AREA_POS_Y;
			gameMenuScreen.addChild(new GameMenuBar);
			
			// Create timer.
			timer = new GameTimer();
			timer.x = Const.TIMER_POS_X;
			timer.y = Const.TIMER_POS_Y;
			gameMenuScreen.addChild(timer);
			
			// Create coordinates text.
			coorTxt = GameTextFormat.newDisplayTextTitle(Const.COOR_TXT_POS_X, Const.COOR_TXT_POS_Y);
			
			addChild(gameMapScreen);
			addChild(gameMenuScreen);
			addChild(gameChat);
			addChild(coorTxt);
		}
		
//##################################################################################################
// Public functions.
//##################################################################################################

		public function loadMap(map:GameMap) : void
		{		
			gameMapR = map;
			gameMapR.addChild(gameTarget);
			gameMapScreen.addChild(gameMapR);
			gameMapR.addEventListener(MouseEvent.MOUSE_DOWN, handleMouseDownOnMap, false, 0, true);
			gameMapR.addEventListener(MouseEvent.MOUSE_UP, handleMouseUpOnMap, false, 0, true);
			gameMapR.addEventListener(MouseEvent.MOUSE_MOVE, handleMouseMoveOnMap, false, 0, true);
			gameMapR.addEventListener(MouseEvent.CLICK, handleMouseClickOnMap, false, 0, true);
			addEventListener(Event.ENTER_FRAME, handleEnterFrame, false, 0, true);
			
			player = gameMapR.players[0];
			
			// Start timer.
			timer.start();
		}
		
		public function unloadMap() : void
		{
			if (gameMapScreen.contains(gameMapR) != true)
			{
				trace("Error: there is no game map to unload");
				return;
			}
			
			if (gameMapR.contains(gameTarget))
			{
				gameMapR.removeChild(gameTarget);
			}
			gameMapR.removeEventListener(MouseEvent.MOUSE_DOWN, handleMouseDownOnMap);
			gameMapR.removeEventListener(MouseEvent.MOUSE_UP, handleMouseUpOnMap);
			gameMapR.removeEventListener(MouseEvent.MOUSE_MOVE, handleMouseMoveOnMap);
			gameMapR.removeEventListener(MouseEvent.CLICK, handleMouseClickOnMap);
			removeEventListener(Event.ENTER_FRAME, handleEnterFrame);
			gameMapScreen.removeChild(gameMapR);
		}

//##################################################################################################
// Private functions.
//##################################################################################################

		private function handleEnterFrame(e:Event) : void
		{
			if (key.isDown(Keyboard.CONTROL))
			{
				controlPressed = true;
				gameTarget.visible = false;
			}
			// I don't know if worth checking the variable before, or just setting it to false anyway.
			else
			{
				controlPressed = false;
			}
			
			// We check f1Pressed to avoid repeating the action many times until the key is released.
			if (key.isDown(Keyboard.C))
			{
				if (cPressed == false)
				{
					gameChat.visible = !gameChat.visible;
					if (gameChat.visible)
					{
						gameMapR.stage.focus = gameChat.inputTxt;
						gameChat.clearInputField();
					}
				}
				cPressed = true;
			}
			else
			{
				cPressed = false;
			}
		}

		private function handleMouseDownOnMap(e:MouseEvent) : void
		{
			mouseButtonPressPoint.x = mouseX;
			mouseButtonPressPoint.y = mouseY;
			mouseButtonDown = true;
		}
		
		private function handleMouseUpOnMap(e:MouseEvent) : void
		{
			mouseButtonDown = false;
			
			if (controlPressed)
			{
				var pointOnMapFrom:Point = screenToMapCoor(mouseButtonPressPoint.x, mouseButtonPressPoint.y);
				var from = Calc.pixel_to_idx(pointOnMapFrom.x, pointOnMapFrom.y, ConstTile.TILE_W, gameMapR.width_tiles);
				var pointOnMapTo:Point = screenToMapCoor(mouseX, mouseY);
				var to = Calc.pixel_to_idx(pointOnMapTo.x, pointOnMapTo.y, ConstTile.TILE_W, gameMapR.width_tiles);
				
				moveUnit(from, to);
			}
		}
		
		private function handleMouseMoveOnMap(e:MouseEvent) : void
		{
			if ( (mouseButtonDown != true) ||
				// If control is pressed. (code relative to unit movement).
				controlPressed )
			{
				return;
			}
			
			var offsetX = mouseX - mouseButtonPressPoint.x;
			var offsetY = mouseY - mouseButtonPressPoint.y;
			
			// Limit movement speed.
			offsetX = Calc.clipGT(offsetX, Const.MAX_MAP_MOVE_OFFSET);
			offsetX = Calc.clipLT(offsetX, (Const.MAX_MAP_MOVE_OFFSET * -1) );
			
			offsetY = Calc.clipGT(offsetY, Const.MAX_MAP_MOVE_OFFSET);
			offsetY = Calc.clipLT(offsetY, (Const.MAX_MAP_MOVE_OFFSET * -1) );	
			
			mouseButtonPressPoint.x = mouseX;
			mouseButtonPressPoint.y = mouseY;
			
			moveMap(offsetX, offsetY);
		}
		
		private function handleMouseClickOnMap(e:MouseEvent) : void
		{
			var pointOnMap:Point = screenToMapCoor(mouseX, mouseY);
			
			var tilex = Calc.pixel_to_tile(pointOnMap.x, ConstTile.TILE_W);
			var tiley = Calc.pixel_to_tile(pointOnMap.y, ConstTile.TILE_H);
			var tile_idx = Calc.coor_to_idx(tilex, tiley, gameMapR.width_tiles);
			//trace("clicked on: " + pxOnMap + ", " + pyOnMap + "; tile: " + tilex + "," + tiley + " idx: " + tile_idx);
			
			gameTarget.x = tilex * ConstTile.TILE_W;
			gameTarget.y = tiley * ConstTile.TILE_H;
			
			gameTarget.visible = false;
			gameMapR.setUnitOnFocus(null);
			
			// Display the element in the Menu.
			displayElementInfo(tile_idx);
		}
		
		private function displayElementInfo(idx:int) : void
		{
			// Get information from the element under the cursor.
			var elem:IElementInfo = gameMapR.getElement(idx);
			if (elem == null)
			{
				trace("Something went wrong. No element reference found for pos " + idx);
				return;
			}
			
			var pointOnMap:Point = Calc.idx_to_coor(idx, gameMapR.width_tiles);
			coorTxt.text = pointOnMap.y + "," + pointOnMap.x;
			
			switch(elem.elemType)
			{
				case ElementType.UNIT:
					// Kind a workaround... maybe we need to create a "setFocus" function for every type of element.
					var unit:GameUnit = gameMapR.getUnitAt(idx);
					gameMapR.setUnitOnFocus(unit);
					displayElementUnit(elem);
					break;
				case ElementType.BUILDING:
					gameTarget.visible = true;
					displayElementBuilding(elem);
					break;
				case ElementType.TILE:
					gameTarget.visible = true;
					displayElementTile(elem);
					break;
				default:
					trace("Invalid element type received: " + elem.elemType);
					break;
			}
		}
		
		/**
		 * @brief Undisplay all elements from menu screen.
		 */
		private function removeElementInformation() : void
		{
			if (gameMenuScreen.contains(gameUnitDisplay))
			{
				gameMenuScreen.removeChild(gameUnitDisplay);
			}
			
			if (gameMenuScreen.contains(gameTileDisplay))
			{
				gameMenuScreen.removeChild(gameTileDisplay);
			}
			
			// TODO: another displays.
		}
		
		private function displayElementUnit(elem:IElementInfo) : void
		{
			// Clear menu from previous information.
			removeElementInformation();
			
			var unit:IElementUnitInfo = IElementUnitInfo(elem);
			
			gameUnitDisplay.elemName = elem.elemName;
			gameUnitDisplay.set_soldiers(unit.soldiers, unit.soldiers_max);
			gameUnitDisplay.attack   = unit.attack;
			gameUnitDisplay.defense  = unit.defense;
			gameUnitDisplay.distance = unit.distance;
			gameUnitDisplay.move     = unit.move_time;
			gameUnitDisplay.cost     = unit.recruit_cost;
			
			gameMenuScreen.addChild(gameUnitDisplay);
		}
		
		private function displayElementBuilding(elem:IElementInfo) : void
		{
			displayElementTile(elem);
			// Clear menu from previous information.
			//removeElementInformation();
			
		}
		
		private function displayElementTile(elem:IElementInfo) : void
		{
			// Clear menu from previous information.
			removeElementInformation();
			
			var tile:IElementTileInfo = IElementTileInfo(elem);
			
			gameTileDisplay.elemName = elem.elemName;
			gameTileDisplay.fortifyBonus = tile.def;
			gameTileDisplay.moveBonus = tile.moveEffort;
			gameTileDisplay.moveable = tile.moveable;
			
			gameMenuScreen.addChild(gameTileDisplay);
		}
		
		private function moveMap(px:int, py:int) : void
		{
			var pxTemp = gameMapR.x + px;
			var pyTemp = gameMapR.y + py;
			
			// Does not scroll if there is no map to show.
			pxTemp = Calc.clipGT(pxTemp, 0);
			pxTemp = Calc.clipLT(pxTemp, ( -1 * (gameMapR.width - Const.MAP_AREA_W) ));
			
			pyTemp = Calc.clipGT(pyTemp, 0);
			pyTemp = Calc.clipLT(pyTemp, ( -1 * (gameMapR.height - Const.MAP_AREA_H) ));
			
			gameTarget.visible = false;
			gameMapR.setUnitOnFocus(null);
			
			gameMapR.x = pxTemp;
			gameMapR.y = pyTemp;
		}
		
		private function moveUnit(from:int, to:int) : void
		{
			if (from == to)
			{
				return;
			}
			
			displayElementInfo(from);
			gameMapR.moveUnit(player, from, to);
		}
		
		/**
		 * @brief Transform real coordinates to relative (to the map) coordinates.
		 * @param	px
		 * @param	py
		 * @return
		 */
		private function screenToMapCoor(px:int, py:int) : Point
		{
			var p:Point = new Point;
			// Calculate click position on game map.
			//real pos + relative pos    - offset.
			p.x = px + (gameMapR.x * -1) - Const.MAP_AREA_POS_X;
			p.y = py + (gameMapR.y * -1) - Const.MAP_AREA_POS_Y;
			
			return p;
		}
		
//################
// Chat commands.
		private function handleSpawnUnitCmd(cmd:String) : void
		{
			var args:Array = cmd.split(/\s/);
			
			trace("args len: " + args.length);
			if (args.length < 4)
			{
				gameChat.addText("Usage: /spawn <type> <column> <row>");
				return;
			}
			
			var type:int = args[1];
			var posy:int = args[2];
			var posx:int = args[3];
			
			gameMapR.spawnUnit(player, type, posx, posy);
		}
	}
}