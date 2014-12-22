package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.stage.MyStage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CannonBallFactory extends MovieClip
	{
		// Ball definitions.
		static const CANNONBALL_TYPE_NONE:Number = 0;
		static const CANNONBALL_TYPE_DEFAULT:Number = 1;
		static const CANNONBALL_TYPE_PATHBALL:Number = 2;
		
		// Internal objects.
		private var gameStageR:MyStage;
		private var cannonBallList:Vector.<CannonBall>;
		

		/******************************************************************************************/
		/* Public functions. */
		/******************************************************************************************/
		 /**
		  * @usage Class constructor.
		  * @param	gameStageRef
		  */
		 public function CannonBallFactory(gameStageRef:MyStage)
		{
			gameStageR = gameStageRef;
			cannonBallList = new Vector.<CannonBall>;
		}
		
		/**
		 * @usage Create a cannon by at px,py and from the given type.
		 * @param	px Horizontal position of the cannon ball.
		 * @param	py Vertical position of the cannon ball.
		 * @param	type Type of the ball.
		 * @param	angle The angle of the cannon.
		 */
		public function createCannonBall(px:Number, py:Number, type:Number, angle:Number) : void
		{
			switch(type)
			{
				case CANNONBALL_TYPE_DEFAULT:
					addCannonBallType(px, py, new CannonBall(gameStageR, angle));
					break;
					
				default:
					trace("Invalid cannon ball type: " + type);
					break;
			}
		}
		
		/**
		 * @usage Show the ball path for the given position, ball type and cannon angle.
		 * @param	px Horizontal position of the cannon ball.
		 * @param	py Vertical position of the cannon ball.
		 * @param	type Type of the ball.
		 * @param	angle The angle of the cannon.
		 */
		public function showPath(px:Number, py:Number, type:Number, angle:Number) : void
		{
			addCannonBallType(px, py, new PathBall(gameStageR, angle, type));
		}
		
		/******************************************************************************************/
		/* Private functions. */
		/******************************************************************************************/
		/**
		 * @usage Add a new cannon ball in the stage.
		 * @param	px
		 * @param	py
		 * @param	ball
		 */
		private function addCannonBallType(px:Number, py:Number, ball:CannonBall)
		{
			// Store new cannon ball reference.
			cannonBallList.push(ball);
			
			// Configure new ball.
			ball.x = px;
			ball.y = py;
			
			// Configure event listeners.
			ball.addEventListener(Event.REMOVED_FROM_STAGE, handleRemovedFromStage, false, 0, true);
			ball.addEventListener(Const.EVT_HIT_TARGET, handleHitTarget, false, 0, true);
			ball.addEventListener(Const.EVT_BALL_STOPPED, handleBallStopped, false, 0, true);
			
			gameStageR.addChild(ball);
		}
		
		/**
		 * @usage Remove cannon ball from stage.
		 * @param	ball
		 */
		private function removeCannonBall(ball:CannonBall) : void
		{			
			ball.removeEventListener(Event.REMOVED_FROM_STAGE, handleRemovedFromStage);
			ball.removeEventListener(Const.EVT_HIT_TARGET, handleHitTarget);
			ball.removeEventListener(Const.EVT_BALL_STOPPED, handleBallStopped);
			
			if (gameStageR.contains(ball))
			{
				gameStageR.removeChild(ball);
			}
			
			// Remove ball reference from the ball list.
			cannonBallList.splice(cannonBallList.indexOf(ball), 1);
		}
		
		/**
		 * @usage Remove ball reference when it is removed from the stage.
		 * @param	e
		 */
		private function handleRemovedFromStage(e:Event) : void
		{
			removeCannonBall(e.currentTarget as CannonBall);
		}
		
		/**
		 * @usage Handle when the ball hit a target in the stage.
		 * @param	e
		 */
		private function handleHitTarget(e:Event) : void
		{
			removeCannonBall(e.currentTarget as CannonBall);
			// tell stage!
			dispatchEvent(new Event(Const.EVT_HIT_TARGET));
		}
		
		private function handleBallStopped(e:Event) : void
		{
			// tell stage!
			dispatchEvent(new Event(Const.EVT_BALL_STOPPED));
		}
	}
	
}