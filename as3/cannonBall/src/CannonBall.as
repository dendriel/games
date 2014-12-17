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
		private var elasticity:Number;
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
			
			// Set default angle.
			angle = angleV;
			
			// Set radius.
			radius = Const.CANNON_BALL_RADIUS_DEFAULT;
			
			// Set elasticity.
			elasticity = Const.CANNON_BALL_ELASTICITY_DEFAULT;
			
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
			
			checkHitTarget();
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
		 * @usage When lost all its speed, report that it's stopped.
		 */
		private function stopSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, updateSelf);
			dispatchEvent(new Event(Const.EVT_BALL_STOPPED));
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
			if (speed_vy != 0) {
				speed_vy -= Const.GRAVITY;
			}
			
			var wallHolderList:MovieClip = stageR.getWallHolderList();
			var vx = Calc.moveSpeedAngleHor(speed_vx, angle);
			var vy = Calc.moveSpeedAngleVer(speed_vy, angle);
			
			var wallCollision:Boolean = false;
			// Check collision against stage bounds (horizontal).
			if ( ( (x + vx) < stageR.fieldOriginX) || ( (x + vx) > stageR.fieldWidth) )	{
				speed_vx *= ( -1);
				wallCollision = true;
			}
			
			// Check collision against stage bounds (vertical).
			if ( ( (y + vy) < stageR.fieldOriginY) || ( (y + vy) > stageR.fieldHeight) ) {
				speed_vy *= ( -1);
				wallCollision = true;
			}
			
			if (wallCollision == true)
			{
				if (speed_vx > 0)
				{
					speed_vx -= (1 - elasticity)*speed_vx;
				}
				else
				{
					speed_vx += -1*(1 - elasticity)*speed_vx;
				}
				
				vx = Calc.moveSpeedAngleHor(speed_vx, angle);
				// If the speed is to low, stop the ball.
				if ( (vx > (-0.3) ) && (vx < 0.3) )
				{
					speed_vx = 0;
				}
				
				if (speed_vy > 0)
				{
					speed_vy -= (1 - elasticity)*speed_vy;
				}
				else
				{
					speed_vy += (1 - elasticity)*speed_vy;
				}
				
				vy = Calc.moveSpeedAngleVer(speed_vy, angle);
				
				if ( (y + vy) >= (stageR.fieldHeight - radius)) 
				{
					// If the speed is to low, stop the ball.
					if ( (vy > (-0.3) ) && (vy < 0.3) )
					{
						speed_vy = 0;
					}
				}
				
				if ( (speed_vy == 0) && (speed_vx == 0))
				{
					stopSelf();
					return;
				}
			}
			
			// Check collision against stage walls.
			for (var i = 0; i < wallHolderList.numChildren; i++)
			{
				var coll_ori = checkWallCollision(wallHolderList.getChildAt(i) as MovieClip, vx, vy);
				// Find out where the collision object came from.				
				switch(coll_ori)
				{
					case Calc.ORI_N:
					case Calc.ORI_S:
					case Calc.ORI_SEB:
					case Calc.ORI_NOA:
					case Calc.ORI_SOB:
					case Calc.ORI_NEB:
						speed_vy *= ( -1);
						vy = vy * ( -1);
						break;
						
					case Calc.ORI_E:
					case Calc.ORI_W:
					case Calc.ORI_SEA:
					case Calc.ORI_NEA:
					case Calc.ORI_NOB:
					case Calc.ORI_SOA:
						speed_vx *= ( -1);
						vx *=(-1);
						break;
						
					case Calc.ORI_C:
						speed_vy *= ( -1);
						vy = vy * ( -1);
						speed_vx *= ( -1);
						vx *= ( -1);
						break;
						
					case Calc.ORI_NONE:
						// Nothing to do.
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
			
			trace("speed x: " + speed_vx + "; speed y: " + speed_vy + "; vx: " + vx + "; vy: " + vy);
		}
		
		private function checkWallCollision(w:MovieClip, vx:Number, vy:Number) : Number
		{
			//var w_child:MovieClip = new MovieClip();
			//var hit = false;
			var dummy = getCollisionObject();
			
			dummy.x += vx;
			dummy.y += vy;
			
			if (w.hitTestObject(dummy) != true)
			{
				// None of the members of this wall is in collision.
				return Calc.ORI_NONE;
			}
			
			if (w.numChildren <= 1)
			{
				// In this wall there is only one member to check.
				return Calc.pointOrientationRect(new Point(x, y), w);
			}
			
			// The wall have more than one member. Check what member of this wall is in collision.
			for (var j = 0; j < w.numChildren; j++)
			{
				var w_aux = w.getChildAt(j) as MovieClip;
				var w_child = new MovieClip();
				
				// Add child position offset.
				w_child.graphics.clear();
				w_child.graphics.beginFill(0x000000);
				w_child.graphics.drawRect(0, 0, w_aux.width, w_aux.height);
				w_child.graphics.endFill();
				w_child.x = w_aux.x + w.x;
				w_child.y = w_aux.y + w.y;
				
				trace(w_child.x + "," + w_child.y + "; " + w_child.width + "," + w_child.height);
				var coll_ori = checkWallCollision(w_child, vx, vy);
				trace("coll_ori: " + coll_ori);
				
				if (coll_ori != Calc.ORI_NONE)
				{
					return coll_ori;
				}
			}
			
			return  Calc.ORI_NONE;
		}
		
		/**
		 * @usage Checks if hitted any of the targets.
		 */
		private function checkHitTarget() : void
		{
			var targetList:MovieClip = stageR.getTargetHolderList();
			var dummy = getCollisionObject();
			
			for (var i = 0; i < targetList.numChildren; i++)
			{
				var t = targetList.getChildAt(i);
				
				if (t.hitTestObject(dummy))
				{
					removeEventListener(Event.ENTER_FRAME, updateSelf);
					dispatchEvent(new Event(Const.EVT_HIT_TARGET));
				}
			}
		}
	}
	
}