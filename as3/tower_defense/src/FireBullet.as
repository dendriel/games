package src
{
	import flash.geom.Point;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class FireBullet extends Bullet
	{
		private const myDamage:Number = 5;
		private const mySpeed:Number = 10;
		
		public function FireBullet(gameStageRef:GameStage, monsterFactoryRef:MonsterFactory, targetRef:Monster, px:Number, py:Number)
		{
			targetPos = new Point();
			
			x = px;
			y = py;
			
			// We want the current position of the target.
			targetPos.x = targetRef.getCenterX();
			targetPos.y = targetRef.getCenterY();
			
			gameStage = gameStageRef;
			monsterFactory = monsterFactoryRef;
			damage = myDamage;
			speed = mySpeed;
			
			activate();
		}
	}
	
}