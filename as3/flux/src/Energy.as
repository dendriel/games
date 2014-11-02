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
		public static const BAD_ENERGY_COLOR:uint = 0xD127FF;
		public static const BAD_ENERGY_VALUE:Number = -3;
		private const colorDefault:uint = 0xF4FFD7;
		private const energyValueDefault:Number = 1;
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
			x = Calc.randomRange((drawRadius / 2), (stageRef.stageWidth - (drawRadius / 2)));
			
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
			
			gravityPull();
			
			if (y >= stageRef.stageHeight)
			{
				removeSelf();
			}
			
			if (Calc.hitRadialCheck(x, y, drawRadius, shipRef.x, shipRef.y, shipRef.getRadius()))
			{
				
				if (energyValue > 0)
				{
					SoundLoader.playEnergyUpSound();
				}
				else
				{
					SoundLoader.playEnergyDownSound();
				}
				
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
				// This will generate a REMOVED_FROM_STAGE
				stageRef.removeChild(this);
			}
			else
			{
				dispatchEvent(new Event(Event.REMOVED_FROM_STAGE));
			}
		}
		
		private function gravityPull(): void
		{
			var nX:Number = (shipRef.x - this.x);
			var nY:Number = (shipRef.y - this.y);
			 
			var angle:Number = Math.atan2(nY, nX);
				 
			var r:Number =  Math.sqrt(nX * nX + nY * nY);
				 
			if (r <= shipRef.getForceFieldRange())
			{
				//var f:Number = (4 * 50 * 10) / (r * r);
				/*
				 * From the original reference:
				 * As you can see, I've reduced the value of "G" to 0.8, and changed the force to depend simply on the distance between the objects, rather than the distance squared.
				 */
				var f:Number = (0.8 * 50 * 10) / r;
				
				var px:Number = f * Math.cos(angle);
				var py:Number = f * Math.sin(angle);
				
				this.x += (shipRef.getGravityPushing() == true)? px : ( -1 * px);
				this.y += (shipRef.getGravityPushing() == true)? py : ( -1 * py);
				
				this.x = Calc.clipGT(this.x, stageRef.stageWidth - drawRadius);
				this.x = Calc.clipLT(this.x, 0 + drawRadius);
			}
		}
	}

}