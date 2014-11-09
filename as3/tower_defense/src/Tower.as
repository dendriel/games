package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tower extends MovieClip
	{
		private const defaultDamage:Number = 2;
		private const defaultPrice:Number = 100;
		private const defaultCoolDownMs:Number = 1000;
		private const defaultRange:Number = Const.TILE_R * 4; // more less 2 tiles away from itself.
		
		protected var damage:Number = defaultDamage;
		protected var price:Number = defaultPrice;
		protected var coolDownMs:Number = defaultCoolDownMs;
		protected var range:Number = defaultRange;
		protected var centeredPoint:Point;
		
		protected var gameStage:MovieClip;
		protected var monsterFactory:MonsterFactory;
		
		/*******************************************************************************************
		 * Public functions.
		 */
		
		/**
		 * @usage Active the tower.
		 */
		public function activate() : void
		{
			centeredPoint = new Point();
			centeredPoint.x = int(x + (width / 2) );
			centeredPoint.y = int(y + (height / 2) );
			
			gameStage.addChild(this);
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
		}
		
		/**
		 * @usage Deactivate the tower.
		 */
		public function deactivate() : void
		{
			removeEventListener(Event.ENTER_FRAME, update);

			if (gameStage.contains(this))
			{
				gameStage.removeChild(this);
			}
			
			dispatchEvent(new Event(Const.EVT_TOWER_REMOVED));
		}
		
		/*******************************************************************************************
		 * Private functions.
		 */
			
		private function update(e:Event) : void
		{
			checkRange();
		}
		
		/**
		 * Check if there is a monster in range. If positivo, shoot!
		 */
		private function checkRange() : void
		{
			var list:Vector.<Monster> = monsterFactory.getMonsterListCopy();
			var m:Monster;
			
			while (list.length > 0)
			{
				m = list.pop();
				
				if (Calc.hitRadialCheck(centeredPoint.x, centeredPoint.y, range,
					m.centeredPoint.x, m.centeredPoint.y, m.getRadius()) == true)
				{
					fire(m);
				}
			}
		}
		
		private function fire(m:Monster) : void
		{
			//gameStage.addChild(new Bullet(gameStage, x, y));
		}
	}
	
}