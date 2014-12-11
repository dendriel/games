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
		private var speed_vx:Number;
		private var speed_vy:Number;
		
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
			speed_vx = Const.CANNON_BALL_SPEED_DEFAULT;
			speed_vy = Const.CANNON_BALL_SPEED_DEFAULT;
			
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
			var vx = speed_vx * Math.cos(angle * (Math.PI/180) );
			var vy = speed_vy * Math.sin(angle * (Math.PI/180) );
			
			var temp_x = vx;
			var temp_y = vy;
			
			// Calculate Horizontal movement.
			if ( ( (x + temp_x) < stageR.fieldOriginX) ||
					( (x + temp_x) > stageR.fieldWidth) )
			{
				// Collided with field origin. Reverse speed.
				speed_vx = speed_vx * ( -1);
				temp_x = vx * ( -1);
			}
			
			// Calculate Vertical movement.
			if ( ( (y + temp_y) < stageR.fieldOriginY) ||
					( (y + temp_y) > stageR.fieldHeight) )
			{
				// Collided with field origin. Reverse speed.
				speed_vy = speed_vy * ( -1);
				temp_y = vy * ( -1);
			}
			
			// Update position.
			x += temp_x;
			y += temp_y;
		}
	}
	
}