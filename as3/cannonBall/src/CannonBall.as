package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
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
		
		protected var radius:Number;
		
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
			
			angle = angleV;
			
			// Set radius.
			radius = Const.CANNON_BALL_RADIUS_DEFAULT;
			
			// Set default speeds.
			speed_vx = Const.CANNON_BALL_SPEED_DEFAULT;
			speed_vy = Const.CANNON_BALL_SPEED_DEFAULT;
			
			drawSelf();
			
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
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
			moveSelf();
		}
		
		/**
		 * @usage Draw itself.
		 */
		private function drawSelf() : void
		{
			graphics.beginFill(0x000000);
            graphics.drawCircle(0, 0, radius);
			graphics.endFill();
		}
		
		/**
		 * @usage Create the object that will be tested for collision instead of the ball raw graphics.
		 * (this allow a smooth ball collision effect).
		 * @return a movieClip to be used to check against collision.
		 */
		private function getCollisionObject() : MovieClip
		{
			var dummy = new MovieClip();
			
			dummy.graphics.beginFill(0x000000);
            dummy.graphics.drawCircle(0, 0, (radius/2) );
			dummy.graphics.endFill();
			
			dummy.x = this.x;
			dummy.y = this.y;
			
			return dummy;
		}
		
		/**
		 * @usage Recursive function.
		 * @return true if the collided, false if not.
		 */
		private function moveSelf() : void
		{
			var wallHolderList = stageR.getWallHolderList();
			var vx = Calc.moveSpeedAngleHor(speed_vx, angle);
			var vy = Calc.moveSpeedAngleVer(speed_vy, angle);
			
			var dummy = getCollisionObject();
			
			dummy.x += vx;
			dummy.y += vy;
			
			// Check collision against stage bounds (horizontal).
			if ( ( (x + vx) < stageR.fieldOriginX) ||
					( (x + vx) > stageR.fieldWidth) )
			{
				// Collided with field origin. Reverse speed.
				speed_vx *= ( -1);
				vx  *= (-1);
			}
			
			// Check collision against stage bounds (vertical).
			if ( ( (y + vy) < stageR.fieldOriginY) ||
					( (y + vy) > stageR.fieldHeight) )
			{
				// Collided with field origin. Reverse speed.
				speed_vy *= ( -1);
				vy = vy * (-1);
			}
			
			// Check collision against stage walls.
			for (var i = 0; i < wallHolderList.numChildren; i++)
			{
				var w = wallHolderList.getChildAt(i);
				
				if (w.hitTestObject(dummy) != true)
				{
					continue;
				}
				
				// Find out where the collision object came from.				
				switch(Calc.pointOrientationRect(new Point(x, y), w))
				{
					case Calc.ORI_N:
					case Calc.ORI_S:
						speed_vy *= ( -1);
						vy = vy * (-1);
						break;
						
					case Calc.ORI_E:
					case Calc.ORI_W:
						speed_vx *= ( -1);
						vx *=(-1);
						break;
						
					case Calc.ORI_NE:
					case Calc.ORI_SE:
					case Calc.ORI_NO:
					case Calc.ORI_SO:
					case Calc.ORI_C:
						speed_vy *= ( -1);
						vy = vy * (-1);
						speed_vx *= ( -1);
						vx *=(-1);
						break;
						
					default:
						trace("Detected Invalid collision.");
						break;
				}
				
				// **Don't stop checking. The ball can collid with more than one wall at the same time.
				// If we check for more collisions, the ball movement looks better and 'natural'.
				//break;
			}
			
			// Update position.
			x += vx;
			y += vy;
		}
	}
	
}