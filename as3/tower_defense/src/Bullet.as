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
		private const defaultInternalName:String = "Default Bullet";
		private const defaultDamage:Number = 2;
		private const defaultSpeed:Number = 4;
		
		private var radius:Number;
		
		protected var internalName:String = defaultInternalName;
		protected var speed:Number = defaultSpeed;
		protected var damage:Number = defaultDamage;
		
		protected var gameStage:GameStage;
		protected var monsterFactory:MonsterFactory;
		protected var targetPos:Point;
		
		protected function activate() : void
		{				
			radius = width / 8;
			rotation = (180 / Math.PI) * Math.atan2((targetPos.y - this.y), (targetPos.x - this.x));
			
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
		}
		
		/*******************************************************************************************
		 * Public functions.
		 */
		 
		/*******************************************************************************************
		 * Private functions.
		 */
		private function update(e:Event) : void
		{
			//trace("(" + targetPos.x + "," + targetPos.y + ") rot: " + rotation + " cosx: " + speed * Math.cos(Math.PI * rotation / 180) + " siny: " + speed * Math.sin(Math.PI * rotation / 180));
			x += speed * Math.cos(Math.PI * rotation/180);
			y += speed * Math.sin(Math.PI * rotation/180);
			
			if (Calc.checkOutsideBounds(x, y,
					gameStage.origin.x, gameStage.origin.y,
					gameStage.size.x, gameStage.size.y) == true)
			{
				removeSelf();
			}
			
			checkCollision();
		}
		
		private function checkCollision() : void
		{
			var mList:Vector.<Monster> = monsterFactory.getMonsterListCopy();
			var m:Monster;
			
			while (mList.length > 0)
			{
				m = mList.pop();
				
				if (Calc.hitRadialCheck(x, y, radius, m.getCenterX(), m.getCenterY(), m.getRadius()) == true)
				{
					m.takeHit(damage);
					removeSelf();
				}
			}
		}
		
		private function removeSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, update);			
			dispatchEvent(new Event(Const.EVT_BULLET_REMOVED));
		}
	}
	
}