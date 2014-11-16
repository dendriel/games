package src
{
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MoonBullet extends Bullet 
	{
		private const myDamage:Number = Const.MOON_BULLET_DMG;
		private const mySpeed:Number = Const.MOON_BULLET_SPEED;
		
		public function MoonBullet(gameStageRef:GameStage, monsterFactoryRef:MonsterFactory, targetRef:Monster, px:Number, py:Number)
		{
			targetPos = new Point();
			
			x = px;
			y = py;
			
			// We want the current position of the target.
			targetPos.x = targetRef.getCenterX();
			targetPos.y = targetRef.getCenterY();
			
			internalName = Const.MOON_BULLET;
			gameStage = gameStageRef;
			monsterFactory = monsterFactoryRef;
			damage = myDamage;
			speed = mySpeed;
			
			activate();
		}		
	}
	
}