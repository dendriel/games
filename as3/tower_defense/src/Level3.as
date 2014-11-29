package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class  Level3 extends Level
	{
		private const myMapName:String = Const.LEVEL3_MAP_NAME;
		private const myStartGold:Number = Const.LEVEL3_START_GOLD;
		
		public function Level3(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			_startGold = myStartGold;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var chkp:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			chkp.push(new Point(5, 10),
					new Point(5, 5),
					new Point(4, 5),
					new Point(4, 2));
					
			var chkp2:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			chkp2.push(new Point(10, 4),
					new Point(5, 4),
					new Point(5, 5));
					
					
			var startPoint:Point = new Point(4, -3);
			var startPoint2:Point = new Point(-3, 5);
			
			var offset = new Point(0, -1);
			var offset2 = new Point(-1, 0);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(new MonsterWave(2, startPoint, chkp, offset, Const.WATER_SLIME_NAME),
					new MonsterWave(8, startPoint, chkp, offset, Const.SLIME_NAME),
					new MonsterWave(8, startPoint2, chkp2, offset2, Const.SLIME_NAME),
					new MonsterWave(6, startPoint2, chkp2, offset2, Const.SLIME_NAME),
					new MonsterWave(1, startPoint, chkp, offset, Const.WATER_SLIME_NAME),
					new MonsterWave(4, startPoint, chkp, offset, Const.SLIME_NAME),
					new MonsterWave(2, startPoint2, chkp2, offset2, Const.SLIME_NAME),
					new MonsterWave(2, startPoint, chkp, offset, Const.SLIME_NAME));
					
			initPlaceArea(new PlaceArea3);
		}
	}
	
}