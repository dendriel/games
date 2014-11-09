package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Bullet extends MovieClip
	{
		private const defaultDamage:Number = 2;
		private const defaultSpeed:Number = 4;
		
		protected var speed:Number = defaultSpeed;
		protected var damage:Number = defaultDamage;
		
		protected var gameStage:MovieClip;

		
		public function Bullet(gameStageRef:MovieClip, x:Number, y:Number)
		{
			gameStage = gameStageRef;
			
			this.x = x;
			this.y = y;
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			
			gameStage.addChild(this);
		}
		
		private function update() : void
		{
			x += speed;
			y += speed;
		}
	}
	
}