package src
{
	import src.stage.MyStage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class PathBall extends CannonBall 
	{
		private var ballType:Number;
		
		public function PathBall(stageRef:MyStage, angleV:Number, type:Number)
		{
			// Store stage reference.
			stageR = stageRef;
			
			// Set default angle.
			angle = angleV;
			
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			clearDrawSelf();
			ballSprite = null;
			
			graphics.beginFill(0x000000);
			
            graphics.drawCircle(0, 0, 2);
			graphics.endFill();
			//this.addChild(ballSprite);
		}
		
	}
	
}