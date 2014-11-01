package
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Energy extends MovieClip
	{
		static const BAD_ENERGY_COLOR:uint = 0xD127FF;
		static const BAD_ENERGY_VALUE:Number = -5;
		static const BAD_ENERGY_SCORE_VALUE:Number = -10;
		private const colorDefault:uint = 0xF4FFD7;
		private const energyValueDefault:Number = 5;
		private const drawRadius:Number = 6;
		private const verticalSpeed:Number = 5;
		private const scoreValueDefault:Number = 10;
		private var stageRef:Stage;
		private var shipRef:Ship;
		private var energyValue:Number;
		private var color:uint;
		public var scoreValue:Number;
		
		public function Energy (stageRef:Stage, shipRef:Ship, color:uint = colorDefault, energyValue:Number = energyValueDefault, scoreValue:Number = scoreValueDefault) 
		{
			this.stageRef = stageRef;
			this.shipRef = shipRef;
			this.color = color;
			this.energyValue = energyValue;
			this.scoreValue = scoreValue;
			drawSelf();
			
			y = 0;
			x = Calculation.randomRange((drawRadius / 2), (stageRef.stageWidth - (drawRadius / 2)));
			
			stageRef.addChild(this);
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
		}
		
		private function drawSelf() : void
		{
			graphics.beginFill(color);
            graphics.drawCircle(0, 0, drawRadius);
		}
		
		private function loop(e:Event) : void
		{
			y += verticalSpeed;
			rotationX += verticalSpeed;
			rotationY += verticalSpeed;
			
			if (y >= stageRef.stageHeight)
			{
				removeSelf();
			}
			
			if (Calculation.hitRadialCheck(x, y, drawRadius, shipRef.x, shipRef.y, shipRef.drawRadius)) {
				shipRef.addEnergy(energyValue);
				dispatchEvent(new Event("updateScore"));
				removeSelf();
			}
		}
		
		public function removeSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, loop);
			if (stageRef.contains(this))
			{
				stageRef.removeChild(this);
			}
			else
			{
				dispatchEvent(new Event(Event.REMOVED_FROM_STAGE));
			}
		}
	}

}