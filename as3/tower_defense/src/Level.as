package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Level extends MovieClip
	{
		// Initialize this with the frame label from the level map.
		protected var mapName:String;
		// Monster factory to create monsters.
		protected var monsterFactory:MonsterFactory;
		// Fill with monster waves.
		protected var waves:Vector.<MonsterWave>;
		// Internal variable to hold current wave.
		private var currWave:MonsterWave;
		
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
					dispatchEvent(new Event(Const.EVT_NEXT_WAVE));
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