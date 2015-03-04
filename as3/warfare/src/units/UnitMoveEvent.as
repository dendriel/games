package src.units
{
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class UnitMoveEvent extends Event 
	{
		public static const EVT_UNIT_MOVE:String = "unit move";
		
		// Event data.
		private var _unit:GameUnit;
		private var _toIdx:int;

		public function UnitMoveEvent(unit:GameUnit, toIdx:int, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(UnitMoveEvent.EVT_UNIT_MOVE, bubbles, cancelable);
			_unit = unit;
			_toIdx = toIdx;
		}

		public override function clone() : Event
		{
			return new UnitMoveEvent(_unit, _toIdx, bubbles, cancelable);
		}
		
		public function get unit():GameUnit 
		{
			return _unit;
		}
		
		public function get toIdx():int 
		{
			return _toIdx;
		}
	}
	
}