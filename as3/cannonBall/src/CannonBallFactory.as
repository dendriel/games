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
		private var pathBall:MovieClip;
		

		/******************************************************************************************/
		/* Public functions. */
		/******************************************************************************************/
		 /**
		  * @usage Class constructor.
		  * @param	gameStageRef
		  */
		 public function CannonBallFactory(gameStageRef:MyStage)
		{
			pathBall = null;
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
			var b:CannonBall = newCannonBallType(type, gameStageR, angle);
			
			if (b == null)
			{
				trace("Invalid cannon ball type.");
				return;
			}
			
			addCannonBallType(px, py, b);
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
			if ( (pathBall != null) && gameStageR.contains(pathBall) )
			{
				pathBall.stopSelf();
				gameStageR.removeChild(pathBall);
				pathBall = null;
			}
			
			var b:CannonBall = newCannonBallType(type, gameStageR, angle);
			b.x = px;
			b.y = py;
			
			pathBall = new PathBall(gameStageR, angle, b);
			
			gameStageR.addChild(pathBall);
		}
		
		/******************************************************************************************/
		/* Private functions. */
		/******************************************************************************************/
		private function newCannonBallType(type:Number, gameStageR:MyStage, angle:Number) : CannonBall
		{
			switch(type)
			{
				case CANNONBALL_TYPE_DEFAULT:
					return (new CannonBall(gameStageR, angle));
					
				default:
					trace("Invalid cannon ball type: " + type);
					return null;
			}
		}
		
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