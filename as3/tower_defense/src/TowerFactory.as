package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class TowerFactory 
	{
		private var gameStage:GameStage;
		private var monsterFactory:MonsterFactory;
		private var towerList:Vector.<Tower>;
		private var bulletFactory:BulletFactory;
		
		public function TowerFactory(gameStageRef:GameStage, monsterFactoryRef:MonsterFactory)
		{
			gameStage = gameStageRef;
			monsterFactory = monsterFactoryRef;
			bulletFactory = new BulletFactory(gameStage, monsterFactory);
			towerList = new Vector.<Tower>;
		}
		
		/*******************************************************************************************
		 * Public functions.
		 */
			
		 /**
		  * @usage Creates a fire tower in the map.
		 * @param	pw Horizontal position (in tiles).
		 * @param	ph Vertical position (in tiles).
		  */
		public function createFireTower(pw:Number = 0, ph:Number = 0) : void
		{
			createFireTowerP(pw * Const.TILE_W, ph * Const.TILE_H);
		}
		
		 /**
		  * @usage Creates a moon tower in the map.
		  * @param	pw Horizontal position (in tiles).
		  * @param	ph Vertical position (in tiles).
		  */
		public function createMoonTower(pw:Number = 0, ph:Number = 0) : void
		{
			createMoonTowerP(pw * Const.TILE_W, ph * Const.TILE_H);
		}
		
		/**
		 * @usage Remove all towers from the screen.
		 */
		public function removeAllTowers() : void
		{
			var list:Vector.<Tower> = towerList.concat();
			var tower:Tower;
			
			while ( list.length > 0) {
				tower = list.pop();
				tower.deactivate();
			}
		}
		
		
		/*******************************************************************************************
		 * Private functions.
		 */
		
		/**
		 * @usage Create a fire tower at the given position (in pixels).
		 * @param	x Horizontal position (in pixels).
		 * @param	y Vertical position (in pixels).
		 */
		private function createFireTowerP(x:Number = 0, y:Number = 0) : void
		{
			var tower:FireTower = new FireTower(monsterFactory, bulletFactory);
			
			addTower(tower, x, y);
		}
		
		/**
		 * @usage Create a moon tower at the given position (in pixels).
		 * @param	x Horizontal position (in pixels).
		 * @param	y Vertical position (in pixels).
		 */
		private function createMoonTowerP(x:Number = 0, y:Number = 0) : void
		{
			var tower:MoonTower = new MoonTower(monsterFactory, bulletFactory);
			
			addTower(tower, x, y);
		}
		
		private function addTower(tower:Tower, x:Number, y:Number) : void
		{
			tower.x = x;
			tower.y = y;
			tower.activate();
			tower.addEventListener(Const.EVT_TOWER_REMOVED, removeTower, false, 0, true);
			
			gameStage.addTower(tower);
			
			towerList.push(tower);
		}
		
		private function removeTower(e:Event) : void
		{
			var tower:Tower = e.currentTarget as Tower;
			
			if (gameStage.contains(tower))
			{
				gameStage.removeChild(tower);
			}
			tower.removeEventListener(Const.EVT_TOWER_REMOVED, removeTower);
			towerList.splice(towerList.indexOf(tower), 1);
		}
	}
	
}