package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.utils.Timer;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tower extends MovieClip
	{
		private const defaultDamage:Number = 2;
		private const defaultPrice:Number = 100;
		private const defaultShootCooldownMs:Number = 1000; // 1 sec.
		private const defaultRange:Number = Const.TILE_R * 4; // more less 2 tiles away from itself.
		
		protected var damage:Number = defaultDamage;
		protected var price:Number = defaultPrice;
		protected var range:Number = defaultRange;
		protected var centeredPoint:Point;
		
		protected var gameStage:GameStage;
		protected var monsterFactory:MonsterFactory;
		protected var bulletFactory:BulletFactory;
		
		// Shooting cooldown.
		protected var shootCooldown:Number = defaultShootCooldownMs;
		private var canShoot:Boolean;
		private var shootCooldownTimer:Timer;
		
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
			
			shootCooldownTimer = new Timer(shootCooldown, 1);
			shootCooldownTimer.addEventListener(TimerEvent.TIMER, shootCooldownTimerHandler, false, 0, true);
			canShoot = false;
			// Let the tower wait its cooldown before its first shoot.
			shootCooldownTimer.start();
			
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
		
		private function shootCooldownTimerHandler(e:TimerEvent) : void
		{
			canShoot = true;
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
					m.getCenterX(), m.getCenterY(), m.getRadius()) == true)
				{
					fire(m);
				}
			}
		}
		
		private function fire(m:Monster) : void
		{
			if (canShoot == true)
			{
				bulletFactory.createFireBulletP(centeredPoint.x, centeredPoint.y, m);
				canShoot = false;
				shootCooldownTimer.start();
			}
		}
	}
	
}