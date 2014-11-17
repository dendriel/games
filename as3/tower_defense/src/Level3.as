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
		private const myMapName:String = "level3map";
		
		public function Level3(monsterFactory:MonsterFactory)
		{
			mapName = myMapName;
			
			this.monsterFactory = monsterFactory;
			
			// Fill checkpoints.
			var chkp:Vector.<Point> = new Vector.<Point>;
			// Push the last point first, and so on.
			chkp.push(new Point(10, 4),
					new Point(6, 4),
					new Point(6, 7),
					new Point(3, 7),
					new Point(3, 2));
					
					
			var startPoint:Point = new Point(-3, 3);
			
			var offset = new Point(-1, 0);
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(//new MonsterWave(8, startPoint, chkp, offset),
					//new MonsterWave(4, startPoint, chkp, offset),
					new MonsterWave(2, startPoint, chkp, offset),
					new MonsterWave(1, startPoint, chkp, offset));
		}
	}
	
}