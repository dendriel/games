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
		private const myGold:Number = 100;
		private const mySpeed:Number = 2;
		private const myLife:Number = 15;
		
		public function Slime (gameStageRef:GameStage, checkpointsRef:Vector.<Point>)
		{
			gameStage = gameStageRef;
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