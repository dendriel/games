package src
{
	import flash.display.MovieClip;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Level2 extends Level
	{
		private const myMapName:String = Const.LEVEL2_MAP_NAME;
		private const myStartGold:Number = Const.LEVEL2_START_GOLD;
		
		public function Level2(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			_startGold = myStartGold;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var checkpoints1:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints1.push(new Point(4, 10),
							new Point(4, 7),
							new Point(1, 7),
							new Point(1, 4),
							new Point(5, 4));
							
			var checkpoints2:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints2.push(new Point(4, 10),
							new Point(4, 7),
							new Point(8, 7),
							new Point(8, 4),
							new Point(5, 4));
						
			var startPoint:Point = new Point(5, -1);
			
			// offset to the top
			var offset = new Point(0, -1);
			var offset2 = new Point(0, -2);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(new MonsterWave(8, startPoint, checkpoints1, offset2),
					new MonsterWave(6, startPoint, checkpoints1, offset2),
					new MonsterWave(4, startPoint, checkpoints2, offset),
					new MonsterWave(2, startPoint, checkpoints2, offset),
					new MonsterWave(2, startPoint, checkpoints1, offset));
					
					
			initPlaceArea(new PlaceArea2);
		}
	}
	
}