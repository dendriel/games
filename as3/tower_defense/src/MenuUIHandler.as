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
	 * 
	 * This code ins't very good.. some entities are accessed from here, others are accessed via the Engine..
	 */
	public class MenuUIHandler extends MovieClip
	{
		private var gameStage:GameStage;
		private var menuUI:MenuUI;
		private var selectedTower:MovieClip;
		private var key:KeyObject;
		private var towerFactory:TowerFactory;
		private var score:ScoreHUD;
		private var level:Level;
		
		public function MenuUIHandler(gameStageRef:GameStage, keyRef:KeyObject, towerFactoryRef:TowerFactory, scoreRef:ScoreHUD)
		{
			gameStage = gameStageRef;
			key = keyRef;
			towerFactory = towerFactoryRef;
			score = scoreRef;
			menuUI = new MenuUI;
			
			this.addChild(menuUI);
			
			selectedTower = null;
			
			// Dynamic texts.
			menuUI.txtTowerDesc.text = "";
			menuUI.txtGameEvent.text = "";
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			gameStage.addEventListener(MouseEvent.CLICK, mouseClickHandler, false, 0, true);
			// My engine weakeness. Adding objects into stage directly (through adobe flash cs6;
			// should be added through GameStage movieclip).
			gameStage.stageR.addEventListener(MouseEvent.CLICK, mouseClickHandler, false, 0, true);
			
			menuUI.mouseEnabled = false;
			gameStage.mouseEnabled = false;
		}
		
		public function loadLevel(levelR:Level) : void
		{
			selectedTower = null;
			level = levelR;
			
			// Dynamic texts.
			menuUI.txtTowerDesc.text = "";
			
			// Towers selection.
			menuUI.btnFireTower.addEventListener(MouseEvent.CLICK, fireTowerClickHandler, false, 0, true);
			menuUI.btnFireTower.addEventListener(MouseEvent.ROLL_OVER, fireTowerRollOverHandler, false, 0, true);
			menuUI.btnFireTower.addEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler, false, 0, true);
			
			menuUI.btnMoonTower.addEventListener(MouseEvent.CLICK, moonTowerClickHandler, false, 0, true);
			menuUI.btnMoonTower.addEventListener(MouseEvent.ROLL_OVER, moonTowerRollOverHandler, false, 0, true);
			menuUI.btnMoonTower.addEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler, false, 0, true);
			
			menuUI.mouseEnabled = false;
			gameStage.mouseEnabled = false;
		}
		
		public function unloadGameUI() : void
		{
			level.hidePlaceArea();
			level = null;
				
			menuUI.btnFireTower.removeEventListener(MouseEvent.CLICK, fireTowerClickHandler);
			menuUI.btnFireTower.removeEventListener(MouseEvent.ROLL_OVER, fireTowerRollOverHandler);
			menuUI.btnFireTower.removeEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler);
			
			menuUI.btnMoonTower.removeEventListener(MouseEvent.CLICK, moonTowerClickHandler);
			menuUI.btnMoonTower.removeEventListener(MouseEvent.ROLL_OVER, moonTowerRollOverHandler);
			menuUI.btnMoonTower.removeEventListener(MouseEvent.ROLL_OUT, towerRollOutHandler);
			
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
		
		public function setGameEventText(value:String) : void
		{
			menuUI.txtGameEvent.text = String(value);
		}
		
		private function mouseClickHandler(e:MouseEvent) : void
		{
			gameStage.stageR.stageFocusRect = false;
			gameStage.stageR.focus = gameStage;
			
			if (selectedTower == null)
			{
				return;
			}
			
			// Check if is an invalid point.
			if ( (mouseY < Const.MENU_UPPER_BAR_SIZE.y) || (mouseY >= Const.MENU_BOTTOM_BAR_POS.y) )
			{
				return;
			}
			
			// Check if the area is free. If true, occupy it.
			if (level.occupyArea(mouseX, mouseY) == false)
			{
				return;
			}
			
			placeTower();
			handleSelectedTower(null);
			level.hidePlaceArea();
		}
		
		private function placeTower() : void
		{
			var pos:Point = Calc.coorToTile(gameStage.mouseX, gameStage.mouseY,
											Const.TILE_W, Const.TILE_H);
			
			var towerNameUI:String = getQualifiedClassName(selectedTower);

			if (towerNameUI == "FireTowerImgUI")
			{
				score.gold = -Const.FIRE_TOWER_PRICE;
				towerFactory.createFireTower(pos.x, pos.y);
			}
			else if (towerNameUI == "MoonTowerImgUI")
			{
				score.gold = -Const.MOON_TOWER_PRICE;
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
					level.hidePlaceArea();
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
			// if there is no selected tower AND the tower parameter is not null.
			if ( (selectedTower == null) && (tower != null) )
			{
				selectedTower = tower;
				gameStage.addChildAt(selectedTower, gameStage.numChildren);
				Mouse.hide();
			}
			// if the tower parameter is null means that this is a stage change.
			else if (selectedTower != null)
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
			// Put gold verification here so we can easily show an fail message if there is no gold to buy the tower.
			if (score.gold < Const.FIRE_TOWER_PRICE)
			{
				menuUI.txtTowerDesc.text = Const.NO_ENOUGH_MONEY;
				return;
			}
			
			handleSelectedTower(new FireTowerImgUI);
			level.displayPlaceArea();
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
			if (score.gold < Const.MOON_TOWER_PRICE)
			{
				menuUI.txtTowerDesc.text = Const.NO_ENOUGH_MONEY;
				return;
			}
			
			handleSelectedTower(new MoonTowerImgUI);
			level.displayPlaceArea();
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