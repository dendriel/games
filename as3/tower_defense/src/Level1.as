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
		private const myMapName:String = "level1map";
		
		public function Level1(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var checkpoints:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints.push(new Point(9, 20), // the end point is out of the screen.
							new Point(9, 16),
							new Point(13, 16),
							new Point(13, 11),
							new Point(5, 11),
							new Point(5, 6),
							new Point(9, 6),
							new Point(9, 2));
						
			var startPoint:Point = new Point( -2, 2);
			// offset to the left <----
			var offset = new Point(-2, 0);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(new MonsterWave(10, startPoint, checkpoints, offset),
					new MonsterWave(8, startPoint, checkpoints, offset),
					new MonsterWave(4, startPoint, checkpoints, offset),
					new MonsterWave(2, startPoint, checkpoints, offset),
					new MonsterWave(1, startPoint, checkpoints, offset));
		}
	}
	
}