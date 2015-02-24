package src
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.ui.Keyboard;
	import src.as3.io.KeyObject;
	import src.maps.GameMap;
	import src.as3.math.Calc;
	import src.tiles.ConstTile;
	import src.tiles.IElementTileInfo;
	import src.ui.GameTileDisplay;
	import src.ui.GameUnitDisplay;
	import src.units.IElementUnitInfo;
	import src.units.GameUnit;
	
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
		// Constants.
		private const statusDisplayX:int = 8;
		private const statusDisplayY:int = 8;
		
		// Images.
		private var gamePlayFrameR:GamePlayFrame;
		private var gameTarget:Target01;
		
		// Screens.
		private var gameMapScreen:MovieClip;
		private var gameMapScreenMask:MovieClip;
		private var gameMapR:GameMap;
		private var gameMenuScreen:MovieClip;
		private var gameUnitDisplay:GameUnitDisplay;
		private var gameTileDisplay:GameTileDisplay;
		private var timer:GameTimer;
		
		// Input/Output.
		private var key:KeyObject;
		private var controlPressed:Boolean;
		
		// Internal state.
		private var mouseButtonDown:Boolean;
		private var mouseButtonPressPoint:Point;
		
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
			
			// Create displays.
			gameUnitDisplay = new GameUnitDisplay(statusDisplayX, statusDisplayY);
			gameTileDisplay = new GameTileDisplay(statusDisplayX, statusDisplayY);
			
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
			
			// TODO: make timer appear on the screen!!
			
			addChild(gameMapScreen);
			addChild(gameMenuScreen);
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
			gameMapScreen.removeChild(gameMapR);
		}

//##################################################################################################
// Private functions.
//##################################################################################################

		private function handleMouseDownOnMap(e:MouseEvent) : void
		{
			mouseButtonPressPoint.x = mouseX;
			mouseButtonPressPoint.y = mouseY;
			mouseButtonDown = true;
			
			if (key.isDown(Keyboard.CONTROL))
			{
				controlPressed = true;
			}
		}
		
		private function handleMouseUpOnMap(e:MouseEvent) : void
		{
			mouseButtonDown = false;
			
			if (controlPressed)
			{
				controlPressed = false;
				var pointOnMapFrom:Point = screenToMapCoor(mouseButtonPressPoint.x, mouseButtonPressPoint.y);
				var from = Calc.pixel_to_idx(pointOnMapFrom.x, pointOnMapFrom.y, ConstTile.TILE_W, gameMapR.width_tiles);
				var pointOnMapTo:Point = screenToMapCoor(mouseX, mouseY);
				var to = Calc.pixel_to_idx(pointOnMapTo.x, pointOnMapTo.y, ConstTile.TILE_W, gameMapR.width_tiles);
				
				moveUnit(from, to);
			}
		}
		
		private function handleMouseMoveOnMap(e:MouseEvent) : void
		{
			if (mouseButtonDown != true)
			{
				return;
			}
			
			// If control is pressed. (code relative to unit movement).
			if (controlPressed)
			{
				// If control keeps pressed.
				if (key.isDown(Keyboard.CONTROL) )
				{
					return;
				}
				// If control was released.
				else if (key.isDown(Keyboard.CONTROL) == false)
				{
					controlPressed = false;
				}
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
			
			gameTarget.x = tilex * ConstTile.TILE_W;
			gameTarget.y = tiley * ConstTile.TILE_H;
			gameTarget.visible = true;
			//trace("clicked on: " + pxOnMap + ", " + pyOnMap + "; tile: " + tilex + "," + tiley + " idx: " + tile_idx);
			
			// Display the element in the Menu.
			displayElementInfo(tile_idx);
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
			
			gameMapR.x = pxTemp;
			gameMapR.y = pyTemp;
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
			
			switch(elem.elemType)
			{
				case ElementType.UNIT:
					displayElementUnit(elem);
					break;
				case ElementType.BUILDING:
					displayElementBuilding(elem);
					break;
				case ElementType.TILE:
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
			gameUnitDisplay.set_soldiers(unit.soldiers, unit.soldiers_injuried);
			gameUnitDisplay.attack   = unit.attack;
			gameUnitDisplay.defense  = unit.defense;
			gameUnitDisplay.distance = unit.distance;
			gameUnitDisplay.move     = unit.move_time;
			gameUnitDisplay.cost     = unit.recruit_cost;
			
			gameMenuScreen.addChild(gameUnitDisplay);
		}
		
		private function displayElementBuilding(elem:IElementInfo) : void
		{
			// Clear menu from previous information.
			removeElementInformation();
			
			trace("Name: " + elem.elemName);
			trace("Desc: " + elem.elemDesc);
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
		
		private function moveUnit(from:int, to:int) : void
		{
			if (from == to)
			{
				return;
			}
			
			var unit:GameUnit = gameMapR.getUnit(from);
			
			if (unit == null)
			{
				// There is no unit to move from this position.
				return;
			}
			
			displayElementInfo(from);
			gameMapR.moveUnit(from, to);
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
	}
}