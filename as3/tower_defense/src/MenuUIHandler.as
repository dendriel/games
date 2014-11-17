package src
{
	import flash.display.MovieClip;
	import flash.geom.Point;
	import flash.ui.Mouse;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import src.com.senocular.utils.KeyObject;
	import flash.ui.Keyboard;
	import flash.utils.getDefinitionByName;
	import flash.utils.getQualifiedClassName;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MenuUIHandler extends MovieClip
	{
		private var gameStage:GameStage;
		private var menuUI:MenuUI;
		private var selectedTower:MovieClip;
		private var key:KeyObject;
		private var towerFactory:TowerFactory;
		
		public function MenuUIHandler(gameStageRef:GameStage, keyRef:KeyObject, towerFactoryRef:TowerFactory)
		{
			gameStage = gameStageRef;
			key = keyRef;
			towerFactory = towerFactoryRef;
		}
		
		public function loadGameUI(menu:MenuUI) : void
		{
			selectedTower = null;
			menuUI = menu;
			
			// Towers selection.
			menu.btnFireTower.addEventListener(MouseEvent.CLICK, fireTowerClickHandler, false, 0, true);
			menu.btnFireTower.addEventListener(MouseEvent.ROLL_OVER, fireTowerRollOverHandler, false, 0, true);
			menu.btnFireTower.addEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler, false, 0, true);
			
			menu.btnMoonTower.addEventListener(MouseEvent.CLICK, moonTowerClickHandler, false, 0, true);
			menu.btnMoonTower.addEventListener(MouseEvent.ROLL_OVER, moonTowerRollOverHandler, false, 0, true);
			menu.btnMoonTower.addEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler, false, 0, true);
			
			
			// Dynamic texts.
			menu.txtTowerDesc.text = "";
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			gameStage.addEventListener(MouseEvent.CLICK, mouseClickHandler, false, 0, true);
			// My engine weakeness. Adding objects into stage directly (through adobe flash cs6;
			// should be added through GameStage movieclip).
			gameStage.stageR.addEventListener(MouseEvent.CLICK, mouseClickHandler, false, 0, true);
			
			menu.mouseEnabled = false;
			gameStage.mouseEnabled = false;
		}
		
		public function unloadGameUI() : void
		{
			menuUI.btnFireTower.removeEventListener(MouseEvent.CLICK, fireTowerClickHandler);
			menuUI.btnFireTower.removeEventListener(MouseEvent.ROLL_OVER, fireTowerRollOverHandler);
			menuUI.btnFireTower.removeEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler);
			
			menuUI.btnMoonTower.removeEventListener(MouseEvent.CLICK, moonTowerClickHandler);
			menuUI.btnMoonTower.removeEventListener(MouseEvent.ROLL_OVER, moonTowerRollOverHandler);
			menuUI.btnMoonTower.removeEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler);
			
			removeEventListener(Event.ENTER_FRAME, update);
			gameStage.removeEventListener(MouseEvent.CLICK, mouseClickHandler);
			// My engine weakeness. Adding objects into stage directly (through adobe flash cs6).
			gameStage.stageR.removeEventListener(MouseEvent.CLICK, mouseClickHandler);
			
			// Remove selected tower if it exists.
			handleSelectedTower(null);
		}
		
		public function setGold(value:Number) : void
		{
			menuUI.txtGold.text = String(value);
		}
		
		public function setWave(value:Number) : void
		{
			menuUI.txtWave.text = String(value);
		}
		
		public function setLevel(value:Number) : void
		{
			menuUI.txtLevel.text = String(value);
		}
		
		public function setMissed(value:Number) : void
		{
			menuUI.txtMissed.text = String(value);
		}
		
		private function mouseClickHandler(e:MouseEvent) : void
		{
			gameStage.stageR.stageFocusRect = false;
			gameStage.stageR.focus = gameStage;
			
			if (selectedTower == null)
			{
				return;
			}
			
			// Check if is a valid point.
			if ( (mouseY >= Const.MENU_UPPER_BAR_SIZE.y) &&
				(mouseY < Const.MENU_BOTTOM_BAR_POS.y) )
				{
					placeTower();
					handleSelectedTower(null);
				}
		}
		
		private function placeTower() : void
		{
			//x, y, towetype.
			
			var pos:Point = Calc.coorToTile(gameStage.mouseX, gameStage.mouseY,
											Const.TILE_W, Const.TILE_H);
			
			var towerNameUI:String = getQualifiedClassName(selectedTower);

			if (towerNameUI == "FireTowerImgUI")
			{
				towerFactory.createFireTower(pos.x, pos.y);
			}
			else if (towerNameUI == "MoonTowerImgUI")
			{
				towerFactory.createMoonTower(pos.x, pos.y);
			}

			
		}
		
		private function update(e:Event) : void
		{
			if (key.isDown(Keyboard.ESCAPE) == true)
			{
				if ( (selectedTower != null) && gameStage.contains(selectedTower) )
				{
					handleSelectedTower(null);
				}
			}
			
			if (selectedTower != null)
			{
				selectedTower.x = gameStage.mouseX - (selectedTower.width/2 );
				selectedTower.y = gameStage.mouseY - (selectedTower.height/2 );
			}
		}
		
		private function handleSelectedTower(tower:MovieClip) : void
		{
			if (selectedTower == null)
			{
				selectedTower = tower;
				gameStage.addChildAt(selectedTower, gameStage.numChildren);
				Mouse.hide();
			}
			else
			{
				if (gameStage.contains(selectedTower))
				{
					gameStage.removeChild(selectedTower);
				}
				selectedTower = null;
				Mouse.show();
			}
		}
		
		private function fireTowerClickHandler(e:MouseEvent) : void
		{
			handleSelectedTower(new FireTowerImgUI);
		}
		
		private function fireTowerRollOverHandler(e:MouseEvent) : void
		{
			menuUI.txtTowerDesc.text = Const.FIRE_TOWER_NAME + "\n" +
								Const.FIRE_TOWER_DESC + "\n" +
								"Price: " + Const.FIRE_TOWER_PRICE +
								" Dmg: " + Const.FIRE_BULLET_DMG + 
								" Speed: " + ( (Const.MAX_COOLDOWN_MS / 1000) - (Const.FIRE_TOWER_COOLDOWN_MS / 1000)) +
								" Range: " + Const.FIRE_TOWER_RANGE / Const.TILE_R;
		}
		
		private function moonTowerClickHandler(e:MouseEvent) : void
		{
			handleSelectedTower(new MoonTowerImgUI);
		}
		
		private function moonTowerRollOverHandler(e:MouseEvent) : void
		{
			menuUI.txtTowerDesc.text = Const.MOON_TOWER_NAME + "\n" +
								Const.MOON_TOWER_DESC + "\n" +
								"Price: " + Const.MOON_TOWER_PRICE +
								" Dmg: " + Const.MOON_BULLET_DMG + 
								" Speed: " + ( (Const.MAX_COOLDOWN_MS / 1000) - (Const.MOON_TOWER_COOLDOWN_MS / 1000) ) +
								" Range: " + Const.MOON_TOWER_RANGE / Const.TILE_R;
		}
		
		private function towerRollOutHandler(e:MouseEvent) : void
		{
			menuUI.txtTowerDesc.text = "";
		}
		
	}
	
}