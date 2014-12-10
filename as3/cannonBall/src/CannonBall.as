package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.stage.MyStage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CannonBall extends MovieClip 
	{
		private var speed:Number;
		private var angle:Number; // Angle in degrees.
		
		private var stageR:MyStage;	// Stage reference, so the ball can interact with the stage.
		
		/******************************************************************************************/
		/* Public methods */
		/******************************************************************************************/
		/**
		 * @usage Class constructor.
		 * @param stageRef
		 * @param angle Cannon angle in degrees.
		 */
		public function CannonBall(stageRef:MyStage, angleV:Number)
		{
			// Store stage reference.
			stageR = stageRef;
			
			//angle = (angleV * 2); // Double angle so conversion to radians and movement is reversed.
			angle = angleV;
			
			// Set default speeds.
			speed = Const.CANNON_BALL_SPEED_DEFAULT;
			
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
		}
		
		/******************************************************************************************/
		/* Private methods */
		/******************************************************************************************/
		/**
		 * @usage Update self.
		 * @param	e
		 */
		public function updateSelf(e:Event) : void
		{
			var vx = speed * Math.cos(angle * (Math.PI/180) );
			var vy = speed * Math.sin(angle * (Math.PI/180) );
			
			var temp_x = x + vx;
			var temp_y = y + vy;
			
			
			// Calculate Horizontal movement.
			if ( (temp_x < stageR.fieldOriginX) || (temp_x > stageR.fieldWidth) )
			{
				// Collided with field origin. Reverse speed.
				speed = speed * ( -1);
				x += vx * (-1);
			}
			else {
				x = temp_x;
			}
			
			// Calculate Vertical movement.
			if ( (temp_y < stageR.fieldOriginY) || (temp_y > stageR.fieldHeight) )
			{
				// Collided with field origin. Reverse speed.
				speed = speed * ( -1);
				y += vy * (-1);
			}
			else {
				y = temp_y;
			}
		}
	}
	
}