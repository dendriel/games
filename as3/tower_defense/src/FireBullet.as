package src
{
	import flash.geom.Point;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class FireBullet extends Bullet
	{
		private const myDamage:Number = 2;
		private const mySpeed:Number = 6;
		
		public function FireBullet(gameStageRef:GameStage, targetRef:Monster)
		{
			targetPos = new Point();
			// We want the current position of the target.
			targetPos.x = targetRef.x;
			targetPos.y = targetRef.y;
			
			gameStage = gameStageRef;
			damage = myDamage;
			speed = mySpeed;
			
			activate();
		}
	}
	
}