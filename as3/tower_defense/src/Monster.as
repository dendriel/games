package src
{
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Monster extends MovieClip
	{
		private const defaultSpeed:Number = 2;
		private const defaultGold:Number = 50;
		
		protected var gold:Number = defaultGold;
		protected var speed:Number = defaultSpeed;
		
		/**
		 * @usage Move to a Horizontal and Vertical position.
		 * @param ph	Horizontal position.
		 * @param pv	Vertical position.
		 * @return true if reached the destination; false if not.
		 */
		protected function move(ph:Number, pv:Number) : Boolean
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
			
			// Still not in the destination.
			return false;
		}
	}
	
}