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
		private const defaultPrice:Number = 100;
		private const defaultShootCooldownMs:Number = 1000; // 1 sec.
		private const defaultRange:Number = Const.TILE_R * 4; // more less 2 tiles away from itself.
		private const defaultSoundType:Number = Const.FIRE_SOUND;
		
		protected var bullet:String = Const.FIRE_BULLET;
		protected var price:Number = defaultPrice;
		protected var range:Number = defaultRange;
		protected var soundType:Number = defaultSoundType;
		protected var centeredPoint:Point;
		
		protected var gameStage:GameStage;
		protected var monsterFactory:MonsterFactory;
		protected var bulletFactory:BulletFactory;
		// Will acquire a target and shoot at it until it is out of range.
		protected var target:Monster;
		
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
			target = null;
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
			
			
			// Check if target already locked in a target.
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