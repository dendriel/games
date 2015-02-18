package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.stage.MyStage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class PathBall extends MovieClip 
	{
		private var pathFrame:MovieClip;
		private var stageR:MyStage;
		
		private var angle:Number;
		
		private var ball:CannonBall;
		
		public function PathBall(stageRef:MyStage, angleV:Number, ballTypeR:CannonBall)
		{						
			// Store stage reference.
			stageR = stageRef;
			
			// Set default angle.
			angle = angleV;
			
			// Create a ball of the given type.
			ball = ballTypeR;
			
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
		}
		
		private function drawPoint(px:Number, py:Number) : void
		{
			graphics.beginFill(0x000000);
            graphics.drawCircle(px, py, 1);
			graphics.endFill();
		}
		
		private function updateSelf(e:Event) : void
		{
			ball.moveSelf(ball, stageR);
			
			drawPoint(ball.x, ball.y);
			
			if ( (ball.speed_vx == 0) && (ball.speed_vy == 0) )
			{
				stopSelf();
			}
		}
		
		public function stopSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, updateSelf);
		}
	}
	
}