package src
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.geom.Point;
	import src.stage.MyStage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CannonBall extends MovieClip 
	{
		protected var speed:Number;
		protected var angle:Number; // Angle in degrees.
		protected var elasticity:Number;
		protected var _speed_vx:Number;
		protected var _speed_vy:Number;
		protected var mass:Number;
		
		protected var stageR:MyStage;	// Stage reference, so the ball can interact with the stage.
		
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
		public function CannonBall(stageRef:MyStage = null, angleV:Number = 0)
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
			_speed_vx = Const.CANNON_BALL_SPEED_DEFAULT;
			_speed_vy = Const.CANNON_BALL_SPEED_DEFAULT;
			
			// Set default ball image.
			ballSprite = new CannonBallDefaultSprite;
			
			drawSelf();
			
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
		}
		
		/**
		 * @usage Remove ball sprite.
		 */
		protected function clearDrawSelf() : void
		{
			if (this.contains(ballSprite))
			{
				removeChild(ballSprite);
			}
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
			moveSelf(this, stageR);
			
			checkHitTarget();
		}
		
		/**
		 * @usage Draw itself.
		 */
		private function drawSelf() : void
		{	
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
		public function reverseSpeedX() : void
		{
			_speed_vx *= ( -1);
		}
		
		/**
		 * @usage Reverse vertical speed.
		 * Keep intelligence in only one place.
		 * @return The new vertical movement value.
		 */
		public function reverseSpeedY() : void
		{
			_speed_vy *= ( -1);
		}
		
		/**
		 * @usage Apply elasticity effect if speed is different than 0.
		 */
		private static function applyElasticity(b:CannonBall) : void
		{
			// Horizontal.
			if (b._speed_vx != 0)
			{
				b._speed_vx -= (1 - b.elasticity) * b._speed_vx;
			}
			
			// Vertical.
			if (b._speed_vy != 0)
			{
				b._speed_vy -= (1 - b.elasticity) * b._speed_vy;
			}
		}
		
		/**
		 * @usage Calculate the horizontal movement and check if speed if higher than minimum.
		 * @return a value corresponding to the total horizontal movement.
		 */
		private function calcHorMovement(b:CannonBall, checkStuck:Boolean = false) : Number
		{
			var vx = Calc.moveSpeedAngleHor(b._speed_vx, b.angle);
			
			// If the speed is to low, stop the ball.
			if ( (vx > (-1*Const.CANNON_BALL_MINIMUM_SPEED) ) && (vx < Const.CANNON_BALL_MINIMUM_SPEED) )
			{
				b._speed_vx = 0;
			}
			
			return vx;
		}
		
		private function calcVerMovement(b:CannonBall, stageR:MyStage, checkStuck:Boolean = false) : Number
		{
			var vy = Calc.moveSpeedAngleVer(b._speed_vy, b.angle);
			
			var temp = (b.y + vy);
			
			trace("new ball pos[0]: " + (b.y + vy) + " vy: " + vy + "(stageR.fieldHeight - b.radius): " + (stageR.fieldHeight - b.radius));
			// If the ball is close to the ground or flag is set
			if ( temp >= (stageR.fieldHeight - b.radius) || (checkStuck == true) )  
			{
				trace("new ball pos[1]: " + (b.y + vy) + " vy: " + vy);
				// If the speed is to low, stop the ball.
				if ( (vy > (-1*Const.CANNON_BALL_MINIMUM_SPEED) ) && (vy < Const.CANNON_BALL_MINIMUM_SPEED) )
				{
					b._speed_vy = 0;
				}
			}
			
			trace("new ball pos[2]: " + (b.y + vy) + " vy: " + vy);
			return vy;
		}
		
		/**
		 * @usage Recursive function.
		 * @return true if the collided, false if not.
		 */
		public function moveSelf(b:CannonBall, stageR:MyStage) : void
		{
			b._speed_vy -= (Const.GRAVITY * Const.CANNON_BALL_MASS_DEFAULT);
			
			// Ball mass matter.
			var speed_by_mass = 0.01*Const.CANNON_BALL_MASS_DEFAULT;
			b._speed_vx += (b._speed_vx > 0)? speed_by_mass : -1 * speed_by_mass;
			
			// If the ball is close to the ground, add friction effect.
			/*if ( (y + vy) >= (stageR.fieldHeight - radius) || (checkStuck == true) )  
			{
				var friction = (1 - Const.CANNON_BALL_FRICTION_DEFAULT) * Const.CANNON_BALL_MASS_DEFAULT;
				vx += (vx > 0)? friction : -1 * friction;
			}*/
			
			var wallHolderList:MovieClip = stageR.getWallHolderList();
			
			// Update angle.
			var ang_offset = 0;
			if ( (b.speed_vx > 0) && (b.speed_vy > 0) )
			{
				ang_offset = 270;
				trace("1");
			}
			else if ( (b.speed_vx < 0) && (b.speed_vy > 0) )
			{
				ang_offset = 180;
				trace("2");
			}
			else if ( (b.speed_vx > 0) && (b.speed_vy < 0) )
			{
				ang_offset = 90;
				trace("3");
			}
			else if ( (b.speed_vx < 0) && (b.speed_vy < 0) )
			{
				ang_offset = 0;
				trace("4");
			}
			
			//angle = Math.atan(speed_vy / speed_vx);
			trace("new angle: " + angle);
			
			var vx = calcHorMovement(b);
			var vy = calcVerMovement(b, stageR);
			trace("vy out[0]: " + vy);
			
			var wallCollision = checkStageBorderCollision(b, vx, vy);			
			if (wallCollision == true)
			{
				applyElasticity(b);				
				vx = calcHorMovement(b);
				vy = calcVerMovement(b, stageR);
				trace("vy out: " + vy);
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
						applyElasticity(b);
						b.reverseSpeedY();
						vx = calcHorMovement(b);
						vy = calcVerMovement(b, stageR, true);
						break;
					case Calc.ORI_S:
					case Calc.ORI_SEB:
					case Calc.ORI_SOB:
						applyElasticity(b);
						b.reverseSpeedY();
						vx = calcHorMovement(b);
						vy = calcVerMovement(b, stageR);
						break;
						
					case Calc.ORI_NEA:
					case Calc.ORI_NOB:
						applyElasticity(b);
						b.reverseSpeedX();
						vx = calcHorMovement(b);
						vy = calcVerMovement(b, stageR, true);
						break;
					case Calc.ORI_E:
					case Calc.ORI_W:
					case Calc.ORI_SEA:
					case Calc.ORI_SOA:
						applyElasticity(b);
						b.reverseSpeedX();
						vx = calcHorMovement(b);
						vy = calcVerMovement(b, stageR);
						break;
						
					case Calc.ORI_C:
						b.reverseSpeedX();
						b.reverseSpeedY();
						vx = calcHorMovement(b);
						vy = calcVerMovement(b, stageR);
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
			
			if ( (b._speed_vy == 0) && (b._speed_vx == 0) )
			{
				b.stopSelf();
				return;
			}
			
			// Update position.
			b.x += vx;
			b.y += vy;
			
			trace("speed x: " + b._speed_vx + "; speed y: " + b._speed_vy + "; vx: " + vx + "; vy: " + vy);
		}
		
		/**
		 * @usage Check and process stage borders collision.
		 * @return true if collided with a stage wall; false if not collided.
		 */
		private function checkStageBorderCollision(b:CannonBall, vx:Number, vy:Number) : Boolean
		{
			var collision = false;
			var new_x = (b.x + vx);
			var new_y = (b.y + vy);
			
			// Check collision against stage bounds (horizontal).
			if ( ( new_x < stageR.fieldOriginX) || ( new_x > stageR.fieldWidth) )	{
				b.reverseSpeedX();
				collision = true;
			}
			
			// Check collision against stage bounds (vertical).
			if ( ( new_y < stageR.fieldOriginY) || ( new_y > (stageR.fieldHeight - radius) ) ) {
				b.reverseSpeedY();
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
				
				//trace(w_child.x + "," + w_child.y + "; " + w_child.width + "," + w_child.height);
				var coll_ori = checkWallCollision(w_child, vx, vy);
				
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
		
		public function set speed_vx(value:Number):void 
		{
			_speed_vx = value;
		}
		
		public function set speed_vy(value:Number):void 
		{
			_speed_vy = value;
		}
		
		public function get speed_vx():Number 
		{
			return _speed_vx;
		}
		
		public function get speed_vy():Number 
		{
			return _speed_vy;
		}
	}
	
}