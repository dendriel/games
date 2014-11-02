package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Asteroid extends MovieClip
	{
		private const asteroidWidth:Number = 32;
		private const asteroidHeight:Number = 32;
		private const verticalSpeed:Number = 8;
		private var image:Image;
		private var stageRef:Stage;
		private var shipRef:Ship;
		
		public function Asteroid(stageRef:Stage, shipRef:Ship) 
		{
			this.stageRef = stageRef;
			this.shipRef = shipRef;
			image = new Image (ImageLocation.ASTEROID, asteroidWidth, asteroidHeight);
			Calc.setRegistrationPoint(image, asteroidWidth/2, asteroidHeight/2);
			this.addChild(image);
			
			y = 0;
			x = Calc.randomRange((asteroidWidth / 2), (stageRef.stageWidth - (asteroidWidth / 2)));
			
			stageRef.addChild(this);
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
		}
		
		private function loop(e:Event) : void
		{
			y += verticalSpeed;
			
			rotation += verticalSpeed;
			
			if (y >= stageRef.stageHeight)
			{
				removeSelf();
			}
			
			if (Calc.hitRadialCheck(x, y, asteroidHeight / 2, shipRef.x, shipRef.y, shipRef.getRadius())) {
				SoundLoader.playExplosionSound();
				dispatchEvent(new Event("collided"));
			}
		}
		
		public function removeSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, loop);
			removeChild(image);
			
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