package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Star extends MovieClip
	{
		private const drawColor:uint = 0xF4FFD7;
		private const drawRadius:Number = 1;
		private var verticalSpeed:Number = 5;
		private var backgroundRef:Background;
		
		public function Star(backgroundRef:Background)
		{
			this.backgroundRef = backgroundRef;
			
			setupSelf();
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
			backgroundRef.addChild(this);
		}
		
		private function setupSelf() : void
		{
			drawSelf();
			y  = Calculation.randomRange(0, backgroundRef.rect.height);
			x = Calculation.randomRange(0, backgroundRef.rect.width);
			verticalSpeed = Calculation.randomRange(4, 7);
		}
		
		private function drawSelf() : void
		{
			graphics.beginFill(drawColor);
            graphics.drawCircle(0, 0, drawRadius);
		}
		
		private function loop(e:Event) : void
		{
			y += verticalSpeed;
			rotationX += verticalSpeed;
			rotationY += verticalSpeed;
			
			if (y >= backgroundRef.rect.height)
			{
				setupSelf();
			}
		}
		
	}

}