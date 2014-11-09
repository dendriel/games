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
		private const myMapName:String = "level2map";
		
		public function Level2(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var checkpoints1:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints1.push(new Point(4, 18),
							new Point(4, 16),
							new Point(10, 16),
							new Point(10, 12),
							new Point(6, 12),
							new Point(6, 7),
							new Point(9, 7));
							
			var checkpoints2:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			checkpoints2.push(new Point(4, 18),
							new Point(4, 16),
							new Point(10, 16),
							new Point(10, 12),
							new Point(14, 12),
							new Point(14, 7),
							new Point(9, 7));
						
			var startPoint:Point = new Point(9, 0);
			
			// offset to the top
			var offset = new Point(0, -2);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(new MonsterWave(10, startPoint, checkpoints2, offset),
					//new MonsterWave(8, startPoint, checkpoints2, offset),
					//new MonsterWave(6, startPoint, checkpoints1, offset),
					//new MonsterWave(4, startPoint, checkpoints2, offset),
					//new MonsterWave(2, startPoint, checkpoints1, offset));
					new MonsterWave(1, startPoint, checkpoints1, offset));
		}
	}
	
}