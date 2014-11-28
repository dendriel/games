package src
{
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class FireTower extends Tower 
	{
		private const myPrice:Number = Const.FIRE_TOWER_PRICE;
		private const myCooldownMs:Number = Const.FIRE_TOWER_COOLDOWN_MS;
		private const myRange:Number = Const.FIRE_TOWER_RANGE;
		private const myBullet:String = Const.FIRE_BULLET;
		private const mySoundType:Number = Const.FIRE_SOUND;
		
		public function FireTower(monsterFactoryRef:MonsterFactory, bulletFactoryRef:BulletFactory)
		{
			bulletFactory = bulletFactoryRef;
			price = myPrice;
			shootCooldown = myCooldownMs;
			range = myRange;
			bullet = myBullet;
			soundType = mySoundType;
			
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