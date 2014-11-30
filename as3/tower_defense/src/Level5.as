package src
{
	import flash.display.MovieClip;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Level5 extends Level 
	{
		private const myMapName:String = Const.LEVEL5_MAP_NAME;
		private const myStartGold:Number = Const.LEVEL5_START_GOLD;
		
		public function Level5(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			_startGold = myStartGold;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var checkpoints1:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints1.push(new Point(3, 10),
							new Point(3, 7),
							new Point(8, 7));

			var offset = new Point(0, -1);
			var startPoint:Point = new Point(8, -1);
							
							
			var checkpoints2:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints2.push(new Point(6, 10),
							new Point(6, 7),
							new Point(1, 7));

			var offset2 = new Point(0, -1);
			var startPoint2:Point = new Point(1, -1);
			
			var checkpoints3:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints3.push(new Point(3, 10),
							new Point(3, 7),
							new Point(4, 7));

			var offset3 = new Point(0, -1);
			var startPoint3:Point = new Point(4, -1);
			
			var checkpoints4:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints4.push(new Point(6, 10),
							new Point(6, 7),
							new Point(4, 7));

			var offset4 = new Point(0, -1);
			var startPoint4:Point = new Point(4, -1);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(
			new MonsterWave(6,  startPoint,  checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(4,  startPoint3, checkpoints3, offset3, Const.WATER_SLIME_NAME),
			new MonsterWave(2,  startPoint3, checkpoints3, offset3, Const.WATER_SLIME_NAME),
			new MonsterWave(4,  startPoint2, checkpoints2, offset2, Const.WATER_SLIME_NAME),
			new MonsterWave(2,  startPoint2, checkpoints2, offset2,  Const.WATER_SLIME_NAME),
			new MonsterWave(10, startPoint2, checkpoints2, offset3),
			new MonsterWave(3,  startPoint3, checkpoints3, offset3, Const.WATER_SLIME_NAME),
			new MonsterWave(8, startPoint3, checkpoints3, offset3),
			new MonsterWave(2,  startPoint,  checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(2,  startPoint,  checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(8,  startPoint3, checkpoints3, offset3),
			new MonsterWave(1,  startPoint,  checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(6,  startPoint,  checkpoints1, offset),
			new MonsterWave(6,  startPoint2, checkpoints2, offset2),
			new MonsterWave(2,  startPoint,  checkpoints1, offset, Const.WATER_SLIME_NAME),
			new MonsterWave(1,  startPoint3, checkpoints3, offset3, Const.WATER_SLIME_NAME),
			new MonsterWave(6,  startPoint2, checkpoints2, offset2),
			new MonsterWave(1,  startPoint,  checkpoints1, offset, Const.WATER_SLIME_NAME));
					
					
			initPlaceArea(new PlaceArea5);
		}
	}
	
}