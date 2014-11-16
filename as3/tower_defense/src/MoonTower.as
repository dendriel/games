package src
{
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MoonTower extends Tower 
	{
		private const myPrice:Number = Const.MOON_TOWER_PRICE;
		private const myColddownMs:Number = Const.MOON_TOWER_COOLDOWN_MS;
		private const myRange:Number = Const.MOON_TOWER_RANGE;
		private const myBullet:String = Const.MOON_BULLET;
		
		public function MoonTower(gameStageRef:GameStage, monsterFactoryRef:MonsterFactory, bulletFactoryRef:BulletFactory)
		{
			gameStage = gameStageRef;
			bulletFactory = bulletFactoryRef;
			price = myPrice;
			shootCooldown = myColddownMs;
			range = myRange;
			bullet = myBullet;
			
			gameStageRef = gameStageRef;
			monsterFactory = monsterFactoryRef;
			
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			var colorTrans:ColorTransform = new ColorTransform;
			colorTrans.blueOffset = 0xff0000;
			//colorTrans.blueOffset = 0xffff00; //yellow
			//colorTrans.alphaMultiplier = 0.5;
			transform.colorTransform = colorTrans;
		}
	}
	
}