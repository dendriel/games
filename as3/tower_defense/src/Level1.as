package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Level1 extends MovieClip implements ILevel 
	{
		private const mapName:String = "level1map";
		private var monsterFactory:MonsterFactory;
		private var waves:Vector.<MonsterWave>;
		private var currWave:MonsterWave;
		
		public function Level1(monsterFactory:MonsterFactory)
		{
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
			
			// Fill waves.
			waves = new Vector.<MonsterWave>;
			waves.push(new MonsterWave(10, startPoint, checkpoints),
					new MonsterWave(8, startPoint, checkpoints),
					new MonsterWave(4, startPoint, checkpoints),
					new MonsterWave(2, startPoint, checkpoints),
					new MonsterWave(1, startPoint, checkpoints));
		}
		
		public function getMapLabel() : String
		{
			return mapName;
		}
		
		public function getWaves() : Vector.<MonsterWave>
		{
			return waves;
		}
		
		
		public function playLevel() : void
		{
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
		}
		
		public function update(e:Event) : void
		{			
			if (monsterFactory.getMonsterListSize() == 0)
			{
				// More waves to trigger?
				if (waves.length > 0)
				{
					currWave = waves.pop();
					triggerWave();
				}
				// No more waves :-(
				else
				{
					removeEventListener(Event.ENTER_FRAME, update);
					dispatchEvent(new Event(Const.EVT_LEVEL_END));
				}
			}
		}
		
		private function triggerWave() : void
		{
			var startPoint:Point = currWave.getStartPoint();
			var startPointOffset:Point = currWave.getStartPointOffset();
			
			//trace("x: " + startPoint.x + " y: " + startPoint.y);
			for (var i:Number = 0; i < currWave.getMonstersNumber(); i++)
			{
				monsterFactory.createSlime(startPoint.x + (startPointOffset.x * i),
											startPoint.y + (startPointOffset.y * i),
											currWave.getCheckpoints());
			}
		}
	}
	
}