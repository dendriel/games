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
		
		protected var placeArea:MovieClip;
		
		private var placeAreaStage:Vector.<Number>;
		
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
			placeAreaStage = new Vector.<Number>;
			initPlaceArea();
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
		}
		
		public function getPlaceAreaRef() : MovieClip
		{
			return placeArea;
		}
		
		public function initPlaceArea() : void
		{
			for (var i = 0;  i < placeArea.numChildren; i++)
			{
				var p = placeArea.getChildAt(i);
				p.gotoAndStop(Const.INVISIBLE_AREA_LABEL);
				placeAreaStage.push(Const.EMPTY_AREA);
			}
		}
		
		public function displayPlaceArea() : void
		{
			for (var i = 0;  i < placeArea.numChildren; i++)
			{
				var p = placeArea.getChildAt(i);
				if (placeAreaStage[i] == Const.EMPTY_AREA)
				{
					p.gotoAndStop(Const.EMPTY_AREA_LABEL);
				}
				else {
					p.gotoAndStop(Const.OCCUPY_AREA_LABEL);
				}
			}
		}
		
		public function hidePlaceArea() : void
		{
			for (var i = 0;  i < placeArea.numChildren; i++)
			{
				var p = placeArea.getChildAt(i);
				p.gotoAndStop(Const.INVISIBLE_AREA_LABEL);
			}
		}
		
		/**
		 * @usage Try to occupy the given area.
		 * @return true if the area cold be occuped; false if the area is already taken or is invalid.
		 */
		public function occupyArea(x:Number, y:Number) : Boolean
		{
			var areaFound:Boolean = false;
			
			for (var i = 0;  i < placeArea.numChildren; i++)
			{
				// Find what is the area we are trying to occupy.
				var p = placeArea.getChildAt(i);
				
				if (Calc.checkInsideBounds(x, y, p.x, p.y, p.width, p.height) == true)
				{
					if (placeAreaStage[i] == Const.OCCUPY_AREA)
					{
						// The area was already occupied.
						return false;
					}
					
					placeAreaStage[i] = Const.OCCUPY_AREA;
					areaFound = true;
				}
				
			}
			
			
			return areaFound;
		}
		
		private function update(e:Event) : void
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