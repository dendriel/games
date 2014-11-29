package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Level1 extends Level
	{
		private const myMapName:String = Const.LEVEL1_MAP_NAME;
		private const myStartGold:Number = Const.LEVEL1_START_GOLD;
		
		public function Level1(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			_startGold = myStartGold;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var checkpoints:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints.push(new Point(10, 6), // the end point is out of the screen.
							new Point(8, 6),
							new Point(8, 3),
							new Point(5, 3),
							new Point(5, 7),
							new Point(2, 7),
							new Point(2, 2));
						
			var startPoint:Point = new Point( -2, 2);
			// offset to the left <----
			var offset = new Point(-1, 0);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(new MonsterWave(1, startPoint, checkpoints, offset, Const.WATER_SLIME_NAME),
					new MonsterWave(6, startPoint, checkpoints, offset),
					new MonsterWave(4, startPoint, checkpoints, offset),
					new MonsterWave(2, startPoint, checkpoints, offset),
					new MonsterWave(1, startPoint, checkpoints, offset));
					
					
					
			//placeArea = new PlaceArea1;
			initPlaceArea(new PlaceArea1);
		}
	}
	
}