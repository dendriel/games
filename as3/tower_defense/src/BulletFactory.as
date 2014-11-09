package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class BulletFactory 
	{
		private var gameStage:GameStage;
		private var bulletList:Vector.<Bullet>;
		private var monsterFactory:MonsterFactory;
		
		public function BulletFactory (gameStageRef:GameStage, monsterFactoryRef:MonsterFactory)
		{
			gameStage = gameStageRef;
			bulletList = new Vector.<Bullet>;
			monsterFactory = monsterFactoryRef;
		}
		
		/*******************************************************************************************
		 * Public functions.
		 */
		 
		 /**
		  * @usage Create a bullet at the given position (in pixels).
		  * @param	x Horizontal position (in pixels).
		  * @param	y Vertical position (in pixels).
		  */
		public function createFireBulletP(x:Number, y:Number, monsterRef:Monster) : void
		{
			var bullet:FireBullet = new FireBullet(gameStage, monsterRef);
			
			bullet.addEventListener(Const.EVET_BULLET_REMOVED, removeBulletHandler, false, 0, true);
			
			bullet.x = x;
			bullet.y = y;
			
			bulletList.push(bullet);
		}
		
		/**
		 * @usage Take care of the bullet when it is removed.
		 */
		public function removeBulletHandler(e:Event) : void
		{
			e.currentTarget.removeEventListener(Const.EVET_BULLET_REMOVED, removeBulletHandler);
			bulletList.splice(bulletList.indexOf(e.currentTarget), 1);
			trace("Bullet removed! size: " + bulletList.length);
		}
		
	}
	
}