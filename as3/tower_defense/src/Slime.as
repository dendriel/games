package src
{
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Slime extends Monster
	{
		private const myGold:Number = Const.SLIME_GOLD;
		private const mySpeed:Number = Const.SLIME_SPEED;
		private const myLife:Number = Const.SLIME_LIFE;
		
		public function Slime (checkpointsRef:Vector.<Point>)
		{
			checkpoints = checkpointsRef.concat();
			speed = mySpeed;
			gold = myGold;
			life = myLife;
			
			drawSelf();
			
			activate();
		}
		
		/**
		 * @usage Draws a green slime.
		 */
		private function drawSelf() : void
		{
			var colorTrans:ColorTransform = new ColorTransform;
			colorTrans.blueOffset = 0xffff00;
			//colorTrans.alphaMultiplier = 0.5;
			transform.colorTransform = colorTrans;
		}

	}
	
}