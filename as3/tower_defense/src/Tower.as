package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.utils.Timer;
	import flash.display.Shape;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tower extends MovieClip
	{		
		protected var bullet:String = Const.FIRE_BULLET;
		protected var price:Number = 100;
		protected var range:Number = Const.TILE_R * 2; // more less 2 tiles away from itself.
		protected var soundType:Number = Const.FIRE_SOUND;
		protected var centeredPoint:Point;
		
		protected var monsterFactory:MonsterFactory;
		protected var bulletFactory:BulletFactory;
		// Will acquire a target and shoot at it until it is out of range.
		protected var target:Monster;
		
		// Shooting cooldown.
		protected var shootCooldown:Number = 1000; // 1 sec.
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
			target = null;
			centeredPoint = new Point();
			centeredPoint.x = int(x + (width / 2) );
			centeredPoint.y = int(y + (height / 2) );
			
			shootCooldownTimer = new Timer(shootCooldown, 1);
			shootCooldownTimer.addEventListener(TimerEvent.TIMER, shootCooldownTimerHandler, false, 0, true);
			canShoot = true;
			// Let the tower wait its cooldown before its first shoot.
			//shootCooldownTimer.start();
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
		}
		
		/**
		 * @usage Deactivate the tower.
		 */
		public function deactivate() : void
		{
			removeEventListener(Event.ENTER_FRAME, update);
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
			
			// Check if tower already locked in a target.
			if (target != null)
			{
				// Check if target still exist and is inside range.
				if ( (list.indexOf(target) != -1) &&
						( Calc.hitRadialCheck(centeredPoint.x, centeredPoint.y, range,
						  target.getCenterX(), target.getCenterY(), target.getRadius()) == true) )
					{
						fire(target);
					}
				// If target left the range or doesn't exist anymore.
				else
				{
					target = null;
				}
				
				return;
			}
			
			while (list.length > 0)
			{
				m = list.pop();
				
				if (Calc.hitRadialCheck(centeredPoint.x, centeredPoint.y, range,
					m.getCenterX(), m.getCenterY(), m.getRadius()) == true)
				{
					target = m;
					fire(m);
				}
			}
		}
		
		private function fire(m:Monster) : void
		{
			if (canShoot == true)
			{
				SoundLoader.play(soundType);
				if (bullet == Const.FIRE_BULLET)
				{
					bulletFactory.createFireBulletP(centeredPoint.x, centeredPoint.y, m);
				}
				// moon bullet.
				else
				{
					bulletFactory.createMoonBulletP(centeredPoint.x, centeredPoint.y, m);
				}
				canShoot = false;
				shootCooldownTimer.start();
			}
		}
	}
	
}