package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	import flash.geom.ColorTransform;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Monster extends MovieClip
	{
		private const defaultSpeed:Number = 2;
		private const defaultGold:Number = 50;
		private const defaultLife:Number = 10;
		
		protected var gold:Number = defaultGold;
		protected var speed:Number = defaultSpeed;
		protected var life:Number = defaultLife;
		protected var radius:Number = 1 * (Const.TILE_R / 2); // less radius so the missile enter the monster.
		
		protected var gameStage:GameStage;
		protected var checkpoints:Vector.<Point>;
		protected var currCheckpoint:Point;
		
		private var centeredPoint:Point;
		
		/*******************************************************************************************
		 * Public functions.
		 */
		public function activate() : void
		{
			centeredPoint = new Point();
			
			updateCenteredPoint();
			
			// Set initial checkpoint.
			currCheckpoint = checkpoints.pop();
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			
			gameStage.addChild(this);
		}
		
		/**
		 * @return The monster's radius for collision detection.
		 */
		public function getRadius() : Number
		{
			return radius;
		}
		
		/**
		 * @return Centered point x.
		 */
		public function getCenterX() : Number
		{
			return centeredPoint.x;
		}
		
		/**
		 * @return Centered point y.
		 */
		public function getCenterY() : Number
		{
			return centeredPoint.y;
		}
		
		/**
		 * @usage Decrease the monster life by the specified value.
		 * @param	value The value to be decreased from life (must be positive).
		 */
		public function takeHit(value:Number) : void
		{
			value = (value < 0)? (value * -1) : value;
			life -= value;
			
			if (life <= 0)
			{
				dispatchEvent(new Event(Const.EVT_MONSTER_KILLED));
				removeSelf();
			}
		}
			
		/*******************************************************************************************
		 * Private functions.
		 */
			
		private function update(e:Event) : void
		{
			moveSelf();
		}
		
		/**
		 * @usage Moves the monster through checkpoints.
		 */
		private function moveSelf() : void
		{
			// Move and get another checkpoint if needed.
			if (move(currCheckpoint.x, currCheckpoint.y) == true)
			{
				// If there is no more checkpoints. stop moving.
				if (checkpoints.length > 0)
				{
					currCheckpoint = checkpoints.pop();
				}
				else
				{
					dispatchEvent(new Event(Const.EVT_END_REACHED_STR));
					removeSelf();
				}
			}
		}
		
		/**
		 * @usage Remove event listeners and the monster from stage.
		 */
		private function removeSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, update);
			if (gameStage.contains(this))
			{
				gameStage.removeChild(this);
			}
		}
		
		/**
		 * @usage Move to a Horizontal and Vertical position.
		 * @param ph	Horizontal position.
		 * @param pv	Vertical position.
		 * @return true if reached the destination; false if not.
		 */
		private function move(ph:Number, pv:Number) : Boolean
		{
			var chkpt_x:Number = ph * Const.TILE_W;
			var chkpt_y:Number = pv * Const.TILE_H;
			var finalSpeed:Number = speed;
			
			//move in the direction of the checkpoint
			if (this.x < chkpt_x)
			{
				// Walk the value of speed or the remaining distance until target
				// if (this.x - chkpt_x) is less than finalSpeed, then sum up this value.
				this.x += Math.min(finalSpeed, Math.abs(this.x - chkpt_x));
			}
			else if (this.x > chkpt_x)
			{
				// Walk the value of speed or the remaining distance until target
				// if (this.x - chkpt_x) is less than finalSpeed, then sum up this value.
				this.x -= Math.min(finalSpeed, Math.abs(this.x - chkpt_x));
			}
				
			if (this.y < chkpt_y)
			{
				this.y += Math.min(finalSpeed, Math.abs(this.y - chkpt_y));
			}
			else if (this.y > chkpt_y)
			{
				this.y -= Math.min(finalSpeed, Math.abs(this.y - chkpt_y));
			}
			
			// Check if is in the destination.
			if ((this.x == chkpt_x) && (this.y == chkpt_y))
			{
				return true;
			}
			
			updateCenteredPoint();
			
			// Still not in the destination.
			return false;
		}
		
		
		private function updateCenteredPoint() : void
		{
			centeredPoint.x = int(x + (width / 2) );
			centeredPoint.y = int(y + (height / 2) );
		}
	}
	
}