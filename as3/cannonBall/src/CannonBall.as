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
		private var mass:Number;
		
		private var stageR:MyStage;	// Stage reference, so the ball can interact with the stage.
		
		protected var radius:Number;
		protected var ballSprite:MovieClip;
		
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
			
			// Set mass.
			mass = Const.CANNON_BALL_MASS_DEFAULT;
			
			// Set default speeds.
			speed_vx = Const.CANNON_BALL_SPEED_DEFAULT;
			speed_vy = Const.CANNON_BALL_SPEED_DEFAULT;
			
			// Set default ball image.
			ballSprite = new CannonBallDefaultSprite;
			
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
			//graphics.beginFill(0x000000);
            //graphics.drawCircle(0, 0, radius);
			//graphics.endFill();
			this.addChild(ballSprite);
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
		 * @usage Reverse horizontal speed.
		 * Keep intelligence in only one place.
		 * @return The new horizontal movement value.
		 */
		private function reverseSpeedX() : void
		{
			speed_vx *= ( -1);
		}
		
		/**
		 * @usage Reverse vertical speed.
		 * Keep intelligence in only one place.
		 * @return The new vertical movement value.
		 */
		private function reverseSpeedY() : void
		{
			speed_vy *= ( -1);
		}
		
		/**
		 * @usage Apply elasticity effect if speed is different than 0.
		 */
		private function applyElasticity() : void
		{
			// Horizontal.
			if (speed_vx != 0)
			{
				speed_vx -= (1 - elasticity)*speed_vx;
			}
			
			// Vertical.
			if (speed_vy != 0)
			{
				speed_vy -= (1 - elasticity)*speed_vy;
			}
		}
		
		/**
		 * @usage Calculate the horizontal movement and check if speed if higher than minimum.
		 * @return a value corresponding to the total horizontal movement.
		 */
		private function calcHorMovement() : Number
		{
			 var vx = Calc.moveSpeedAngleHor(speed_vx, angle);
				
			// If the speed is to low, stop the ball.
			if ( (vx > (-1*Const.CANNON_BALL_MINIMUM_SPEED) ) && (vx < Const.CANNON_BALL_MINIMUM_SPEED) )
			{
				speed_vx = 0;
			}
			
			return vx;
		}
		
		private function calcVerMovement(checkStuck:Boolean = false) : Number
		{
			var vy = Calc.moveSpeedAngleVer(speed_vy, angle);
			
			// If the ball is close to the ground or flag is set
			if ( (y + vy) >= (stageR.fieldHeight - radius) || (checkStuck == true) )  
			{
				// If the speed is to low, stop the ball.
				if ( (vy > (-1*Const.CANNON_BALL_MINIMUM_SPEED) ) && (vy < Const.CANNON_BALL_MINIMUM_SPEED) )
				{
					speed_vy = 0;
				}
			}
			
			return vy;
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
			
			var vx = calcHorMovement();
			var vy = calcVerMovement();
			
			var wallCollision = checkStageBorderCollision((x + vx), (y + vy));			
			if (wallCollision == true)
			{
				applyElasticity();				
				vx = calcHorMovement();
				vy = calcVerMovement();
			}
			
			// Check collision against stage walls.
			for (var i = 0; i < wallHolderList.numChildren; i++)
			{
				var coll_ori = checkWallCollision(wallHolderList.getChildAt(i) as MovieClip, vx, vy);
				// Find out where the collision object came from.				
				switch(coll_ori)
				{
					// If collision by top, check if the ball was stuck in the wall.
					case Calc.ORI_N:
					case Calc.ORI_NOA:
					case Calc.ORI_NEB:
						applyElasticity();
						reverseSpeedY();
						vx = calcHorMovement();
						vy = calcVerMovement(true);
						break;
					case Calc.ORI_S:
					case Calc.ORI_SEB:
					case Calc.ORI_SOB:
						applyElasticity();
						reverseSpeedY();
						vx = calcHorMovement();
						vy = calcVerMovement();
						break;
						
					case Calc.ORI_NEA:
					case Calc.ORI_NOB:
						applyElasticity();
						reverseSpeedX();
						vx = calcHorMovement();
						vy = calcVerMovement(true);
						break;
					case Calc.ORI_E:
					case Calc.ORI_W:
					case Calc.ORI_SEA:
					case Calc.ORI_SOA:
						applyElasticity();
						reverseSpeedX();
						vx = calcHorMovement();
						vy = calcVerMovement();
						break;
						
					case Calc.ORI_C:
						reverseSpeedX();
						reverseSpeedY();
						vx = calcHorMovement();
						vy = calcVerMovement();
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
			
			if ( (speed_vy == 0) && (speed_vx == 0) )
			{
				stopSelf();
				return;
			}
			
			// Update position.
			x += vx;
			y += vy;
			
			//trace("speed x: " + speed_vx + "; speed y: " + speed_vy + "; vx: " + vx + "; vy: " + vy);
		}
		
		/**
		 * @usage Check and process stage borders collision.
		 * @param	new_x Horizontal position plus new horizontal movement (x + vx);
		 * @param	new_y Vertical position plus new vertical movement (y + vy);
		 * @return true if collided with a stage wall; false if not collided.
		 */
		private function checkStageBorderCollision(new_x:Number, new_y:Number) : Boolean
		{
			var collision = false;
			
			// Check collision against stage bounds (horizontal).
			if ( ( new_x < stageR.fieldOriginX) || ( new_x > stageR.fieldWidth) )	{
				reverseSpeedX();
				collision = true;
			}
			
			// Check collision against stage bounds (vertical).
			if ( ( new_y < stageR.fieldOriginY) || ( new_y > (stageR.fieldHeight - radius) ) ) {
				reverseSpeedY();
				collision = true;
			}
			
			return collision;
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