package src
{
	import flash.display.MovieClip;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Level4 extends Level 
	{
		private const myMapName:String = Const.LEVEL4_MAP_NAME;
		private const myStartGold:Number = Const.LEVEL4_START_GOLD;
		
		public function Level4(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			_startGold = myStartGold;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var checkpoints1:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints1.push(new Point(8, 10),
							new Point(8, 4),
							new Point(1, 4),
							new Point(1, 2));

			var offset = new Point(-1, 0);
			var startPoint:Point = new Point(-1, 2);
							
							
							
			var checkpoints2:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints2.push(
			new Point(1, 10),
			new Point(1, 4),
			new Point(8, 4),
			new Point(8, 2));
			
			var startPoint2:Point = new Point(10, 2);
			var offset2 = new Point(1, 0);
			
			var checkpoints3:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints3.push(
			new Point(1, 10),
			new Point(1, 7),
			new Point(8, 7),
			new Point(8, 2));
			
			var startPoint3:Point = new Point(10, 2);
			var offset3 = new Point(1, 0);
			
			var checkpoints4:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints4.push(new Point(8, 10),
							new Point(8, 7),
							new Point(1, 7),
							new Point(1, 4),
							new Point(1, 2));

			var offset4 = new Point(-1, 0);
			var startPoint4:Point = new Point(-1, 2);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(
			new MonsterWave(6, startPoint, checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(6, startPoint4, checkpoints4, offset4, Const.WATER_SLIME_NAME),
			new MonsterWave(4, startPoint3, checkpoints3, offset3, Const.WATER_SLIME_NAME),
			new MonsterWave(4, startPoint2, checkpoints2, offset2, Const.WATER_SLIME_NAME),
			new MonsterWave(8, startPoint, checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(8, startPoint, checkpoints1, offset),
			new MonsterWave(1, startPoint4, checkpoints4, offset4, Const.WATER_SLIME_NAME),
			new MonsterWave(8, startPoint4, checkpoints4, offset4),
			new MonsterWave(1, startPoint, checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(8, startPoint, checkpoints1, offset),
			new MonsterWave(1, startPoint2, checkpoints2, offset2, Const.WATER_SLIME_NAME),
			new MonsterWave(8, startPoint2, checkpoints2, offset2),
			new MonsterWave(1, startPoint4, checkpoints4, offset4, Const.WATER_SLIME_NAME),
			new MonsterWave(1, startPoint3, checkpoints3, offset3, Const.WATER_SLIME_NAME),
			new MonsterWave(6, startPoint2, checkpoints2, offset2),
			new MonsterWave(4, startPoint, checkpoints1, offset));
					
					
			initPlaceArea(new PlaceArea4);
		}
		
	}
	
}