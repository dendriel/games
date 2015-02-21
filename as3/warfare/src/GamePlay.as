package src
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	
	import src.maps.GameMap;
	import src.as3.math.Calc;
	
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
	 * |                                                            |  -\
	 * |                                                            |    gameMenuScreen:MovieClip
	 * +------------------------------------------------------------+  -/
	 */
	public class GamePlay extends MovieClip 
	{
		// Images.
		var gamePlayFrameR:GamePlayFrame;
		
		// Screens.
		private var gameMapScreen:MovieClip;
		private var gameMapScreenMask:MovieClip;
		private var gameMapR:GameMap;
		
		//private var gameMenuScreen:MovieClip; // will handle this latter.
		
		// Internal state.
		private var mouseButtonDown:Boolean;
		private var mouseButtonPressPoint:Point;
		
		public function GamePlay()
		{
			// Initialize internal variables.
			mouseButtonDown = false;
			mouseButtonPressPoint = new Point();
			
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
			
			addChild(gameMapScreen);
		}
		
//##################################################################################################
// Public functions.
//##################################################################################################

		public function loadMap(map:GameMap) : void
		{		
			gameMapR = map;
			gameMapScreen.addChild(gameMapR);
			gameMapR.addEventListener(MouseEvent.MOUSE_DOWN, handleMouseDownOnMap, false, 0, true);
			gameMapR.addEventListener(MouseEvent.MOUSE_UP, handleMouseUpOnMap, false, 0, true);
			gameMapR.addEventListener(MouseEvent.MOUSE_MOVE, handleMouseMoveOnMap, false, 0, true);
		}
		
		public function unloadMap() : void
		{
			if (gameMapScreen.contains(gameMapR) != true)
			{
				trace("Error: there is no game map to unload");
				return;
			}
			
			gameMapR.removeEventListener(MouseEvent.MOUSE_DOWN, handleMouseDownOnMap);
			gameMapR.removeEventListener(MouseEvent.MOUSE_UP, handleMouseUpOnMap);
			gameMapR.removeEventListener(MouseEvent.MOUSE_MOVE, handleMouseMoveOnMap);
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
		}
		
		private function handleMouseUpOnMap(e:MouseEvent) : void
		{
			mouseButtonDown = false;
		}
		
		private function handleMouseMoveOnMap(e:MouseEvent) : void
		{
			if (mouseButtonDown != true)
			{
				return;
			}
			
			var offsetX = mouseX - mouseButtonPressPoint.x;
			var offsetY = mouseY - mouseButtonPressPoint.y;
			
			offsetX = Calc.clipGT(offsetX, Const.MAX_MAP_MOVE_OFFSET);
			offsetX = Calc.clipLT(offsetX, (Const.MAX_MAP_MOVE_OFFSET * -1) );
			
			offsetY = Calc.clipGT(offsetY, Const.MAX_MAP_MOVE_OFFSET);
			offsetY = Calc.clipLT(offsetY, (Const.MAX_MAP_MOVE_OFFSET * -1) );	
			
			mouseButtonPressPoint.x = mouseX;
			mouseButtonPressPoint.y = mouseY;
			
			moveMap(offsetX, offsetY);
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
			
			trace("map height: " + (-1 * (gameMapR.height - Const.MAP_AREA_H) ) + "; temp: " + pyTemp);
		}

	}
	
}