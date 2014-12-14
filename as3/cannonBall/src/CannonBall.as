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
			speed_vx = 4;
			speed_vy = 4;
			
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
            graphics.drawCircle(0, 0, 8);
			graphics.endFill();
		}
		
		/**
		 * @usage Recursive function.
		 * @return true if the collided, false if not.
		 */
		private function moveSelf() : void
		{
			var wallHolderList = stageR.getWallHolderList();
			var vx = speed_vx * Math.cos(angle * (Math.PI/180) );
			var vy = speed_vy * Math.sin(angle * (Math.PI/180) );
			
			var temp_x = vx;
			var temp_y = vy;
			var nextPos = new MovieClip();
			nextPos.graphics.copyFrom(this.graphics);
			nextPos.x = this.x + temp_x;
			nextPos.y = this.y + temp_y;
			
			nextPos.x += temp_x;
			nextPos.y += temp_y;
			
			// Check collision against stage bounds (horizontal).
			if ( ( (x + temp_x) < stageR.fieldOriginX) ||
					( (x + temp_x) > stageR.fieldWidth) )
			{
				// Collided with field origin. Reverse speed.
				speed_vx = speed_vx * ( -1);
				temp_x = vx * ( -1);
			}
			
			// Check collision against stage bounds (vertical).
			if ( ( (y + temp_y) < stageR.fieldOriginY) ||
					( (y + temp_y) > stageR.fieldHeight) )
			{
				// Collided with field origin. Reverse speed.
				speed_vy = speed_vy * ( -1);
				temp_y = vy * ( -1);
			}
			
			// Check collision against stage walls.
			for (var i = 0; i < wallHolderList.numChildren; i++)
			{
				var w:MovieClip = wallHolderList.getChildAt(i);
				
				// This can be expensive.. making the as3 hit check, then checking it again to see
				// where is rectangle face in with the collision occurs.
				if (w.hitTestObject(nextPos) != true)
				{
					continue;
				}
				
				// Find the collision direction.
				var ori = Calc.pointOrientationRect(new Point(x, y), w);
				
				switch(ori)
				{
					case Calc.ORI_N:
					case Calc.ORI_S:
						speed_vy = speed_vy * ( -1);
						temp_y = vy * ( -1);
						trace("N or S");
						break;
						
					case Calc.ORI_E:
					case Calc.ORI_W:
						speed_vx = speed_vx * ( -1);
						temp_x = vx * ( -1);
						trace("E or W");
						break;
						
						
					case Calc.ORI_NE:
						speed_vy = speed_vy * ( -1);
						temp_y = vy * ( -1);
						speed_vx = speed_vx * ( -1);
						temp_x = vx * ( -1);
						trace("NE");
						break;
					case Calc.ORI_SE:
						speed_vy = speed_vy * ( -1);
						temp_y = vy * ( -1);
						speed_vx = speed_vx * ( -1);
						temp_x = vx * ( -1);
						trace("SE");
						break;
					case Calc.ORI_NO:
						speed_vy = speed_vy * ( -1);
						temp_y = vy * ( -1);
						speed_vx = speed_vx * ( -1);
						temp_x = vx * ( -1);
						trace("NO");
						break;
					case Calc.ORI_SO:
						speed_vy = speed_vy * ( -1);
						temp_y = vy * ( -1);
						speed_vx = speed_vx * ( -1);
						temp_x = vx * ( -1);
						trace("SO");
						break;
						
					case Calc.ORI_C:
						trace("THE POINT IS INSIDE THE BOX!!");
						speed_vy = speed_vy * ( -1);
						temp_y = vy * ( -1);
						speed_vx = speed_vx * ( -1);
						temp_x = vx * ( -1);
						break;
						
					default:
						trace("Detected Invalid collision.");
						break;
				}
			}
			
			// Update position.
			x += temp_x;
			y += temp_y;
		}
	}
	
}