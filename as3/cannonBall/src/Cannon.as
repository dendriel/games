package src
{
	import flash.display.Stage;
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.com.senocular.utils.KeyObject;
	import flash.ui.Keyboard;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Cannon extends MovieClip 
	{
		private var key:KeyObject;
		private var angle:Number;
		private var cannonBallType:Number;
		private var cannonBallFactoryR:CannonBallFactory;
		private var _canShoot:Boolean;
		
		/******************************************************************************************/
		/* Public methods */
		/******************************************************************************************/
		/**
		 * @usage Allow player to interact with the cannon.
		 * @param	keyRef
		 * @param   cannonBallFactoryRef
		 */
		public function load(keyRef:KeyObject, cannonBallFactoryRef:CannonBallFactory)
		{
			// Store keyobject reference.
			key = keyRef;
			
			// Store cannon ball factory reference.
			cannonBallFactoryR = cannonBallFactoryRef;
			
			// Starter cannon ball.
			cannonBallType = CannonBallFactory.CANNONBALL_TYPE_DEFAULT;
			
			// Cannon starter angle (set by the cannon image).
			angle = 270;
			
			// Stage is clear for firing.
			_canShoot = true;
			
			// Start updateSelf.
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
		}
		
		/**
		 * @usage Stop interaction and free resources.
		 */
		public function unload() : void
		{
			key = null;
			cannonBallFactoryR = null;
			cannonBallType = CannonBallFactory.CANNONBALL_TYPE_NONE;
			_canShoot = false;
			
			removeEventListener(Event.ENTER_FRAME, updateSelf);
		}
		
		/**
		 * @usage Use to enable/disable cannon shooting.
		 */
		public function set canShoot(value:Boolean):void 
		{
			_canShoot = value;
		}
		
		/******************************************************************************************/
		/* Private methods */
		/******************************************************************************************/
		/**
		 * @usage Update self.
		 * @param	e
		 */
		private function updateSelf(e:Event) : void
		{
			var rot = Const.CANNON_ROTATION_SPEED;
			var shift_pressed:Boolean = false;
			
			// If shift is down, rotate cannon faster.
			if (key.isDown(Keyboard.SHIFT))
			{
				shift_pressed = true;
				rot *= 3;
			}
			
			// Rotate left.
			if (key.isDown(Keyboard.LEFT) || key.isDown(Keyboard.A))
			{
				decrease_angle(rot);
			}
			// Or rotate right.
			else if (key.isDown(Keyboard.RIGHT) || key.isDown(Keyboard.D))
			{
				increase_angle(rot);
			}
			
			if (key.isDown(Keyboard.UP) || key.isDown(Keyboard.W))
			{
				trace("up");
			}
			else if (key.isDown(Keyboard.DOWN) || key.isDown(Keyboard.S))
			{
				trace("down");
			}
			
			// Shoot!
			if (key.isDown(Keyboard.SPACE))
			{
				if (shift_pressed)
				{
					cannonBallFactoryR.showPath(x, y, cannonBallType, angle);
				}
				else
				{
					shoot();
				}
			}
		}
		
		/**
		 * @usage Decrease the cannon angle.
		 */
		private function increase_angle(rot:Number) : void
		{
			if (angle >= Const.CANNON_MAX_ANGLE)
			{
				// Minimum angle reached.
				return;
			}
			
			rotation += rot;
			angle += rot;
			trace("angle: " + angle);
		}
		
		/**
		 * @usage Increase the cannon angle.
		 */
		private function decrease_angle(rot:Number) : void
		{
			if (angle <= Const.CANNON_MIN_ANGLE)
			{
				// Maximum angle reached.
				return;
			}
			
			rotation -= rot;
			angle -= rot;
			trace("angle: " + angle);
		}
		
		/**
		 * @usage Shoot a cannon ball.
		 */
		private function shoot() : void
		{
			if (_canShoot == false)
			{
				return;
			}
			
			// Disallow shooting. (until Stage enable shooting again).
			_canShoot = false;
			
			// Create a cannon ball on the stage.
			cannonBallFactoryR.createCannonBall(x, y, cannonBallType, angle);
			
			// Tell stage that a cannon ball was created.
			dispatchEvent(new Event(Const.EVT_CANNON_SHOOTING));
		}
	}
	
}