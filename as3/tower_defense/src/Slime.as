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
		public function Slime (checkpointsRef:Vector.<Point>, goldR:Number=Const.SLIME_GOLD, speedR:Number=Const.SLIME_SPEED, lifeR:Number = Const.SLIME_LIFE)
		{
			checkpoints = checkpointsRef.concat();
			speed = speedR;
			gold = goldR;
			life = lifeR;
			
			drawSelf();
			
			activate();
		}
		
		/**
		 * @usage Draws a green slime.
		 */
		protected function drawSelf(color:Number=Const.SLIME_COLOR) : void
		{
			var colorTrans:ColorTransform = new ColorTransform;
			colorTrans.blueOffset = color;
			//colorTrans.alphaMultiplier = 0.5;
			transform.colorTransform = colorTrans;
		}

	}
	
}