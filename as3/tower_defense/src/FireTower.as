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
		private const myDamage:Number = 2;
		private const myPrice:Number = 100;
		private const myColddownMs:Number = 500;
		private const myRange:Number = Const.TILE_R * 3;
		
		
		public function FireTower(gameStageRef:MovieClip, monsterFactoryRef:MonsterFactory)
		{
			gameStage = gameStageRef;
			damage = myDamage;
			price = myPrice;
			coolDownMs = myColddownMs;
			range = myRange;
			
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