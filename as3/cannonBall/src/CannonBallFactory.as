package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.stage.MyStage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CannonBallFactory 
	{
		// Ball definitions.
		static const CANNONBALL_TYPE_DEFAULT:Number = 0;
		static const CANNONBALL_TYPE_NONE:Number = 1;
		
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
		 */
		public function createCannonBall(px:Number, py:Number, type:Number, angle:Number)
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
			
			gameStageR.addChild(ball);
		}
		
		/**
		 * @usage Remove ball reference when it is removed from the stage.
		 * @param	e
		 */
		private function handleRemovedFromStage(e:Event) : void
		{
			var ball = e.currentTarget as CannonBall;
			
			if (gameStageR.contains(ball))
			{
				gameStageR.removeChild(ball);
			}
			
			ball.removeEventListener(Event.REMOVED_FROM_STAGE, handleRemovedFromStage);
			
			// Remove ball reference from the ball list.
			cannonBallList.splice(cannonBallList.indexOf(ball), 1);
		}
	}
	
}