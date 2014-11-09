package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	
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
		
		protected var gameStage:GameStage;
		protected var targetPos:Point;
		
		protected function activate() : void
		{	
			//spawn new bullet
			rotation = (180/Math.PI)* Math.atan2((targetPos.y - this.y), (targetPos.x - this.x));
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			
			gameStage.addChild(this);
		}
		
		private function update(e:Event) : void
		{
			//x += speed.x;
			//y += speed.y;
			
			
			//rotation = 90;
			//trace("rot: " + rotation);
			//trace ("x: " + speed.x * Math.cos(Math.PI * rotation / 180));
			//trace ("y: " + speed.y * Math.sin(Math.PI * rotation / 180));
			trace("(" + targetPos.x + "," + targetPos.y + ") rot: " + rotation + 
			" cosx: " + speed * Math.cos(Math.PI * rotation / 180) + " siny: " + speed * Math.sin(Math.PI * rotation / 180));
			x += speed * Math.cos(Math.PI * rotation/180);
			y += speed * Math.sin(Math.PI * rotation/180);
			
			
			
			
			if (Calc.checkOutsideBounds(x, y,
					gameStage.origin.x, gameStage.origin.y,
					gameStage.size.x, gameStage.size.y) == true)
			{
				removeSelf();
			}
		}
		
		private function removeSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, update);
			
			if (gameStage.contains(this))
			{
				gameStage.removeChild(this);
			}
			
			dispatchEvent(new Event(Const.EVET_BULLET_REMOVED));
		}
	}
	
}