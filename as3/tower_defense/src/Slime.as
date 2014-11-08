package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.ColorTransform;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Slime extends Monster
	{
		private const myGold:Number = 100;
		private const mySpeed:Number = 12;
		private var gameStage:MovieClip;
		private var checkpoints:Vector.<Point>;
		private var currCheckpoint:Point;
		private var reachedEnd:Boolean;
		
		public function Slime (gameStageRef:MovieClip, checkpointsRef:Vector.<Point>)
		{
			gameStage = gameStageRef;
			speed = mySpeed;
			gold = myGold;
			
			checkpoints = checkpointsRef.concat();
			reachedEnd = false;
			
			// Set initial checkpoint.
			currCheckpoint = checkpoints.pop();
			
			drawSelf();
			gameStage.addChild(this);
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			
			trace("Green Slime created");
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
		
		private function update(e:Event) : void
		{
			moveSelf();
		}
		
		/**
		 * @usage Moves the monster through checkpoints.
		 */
		private function moveSelf() : void
		{
			// Does nothing if there is no more moves.
			if (reachedEnd == true)
			{
				dispatchEvent(new Event(Const.EVT_END_REACHED_STR));
				removeSelf();
				return;
			}
			
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
					reachedEnd = true;
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
	}
	
}