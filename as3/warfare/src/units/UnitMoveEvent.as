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
		private var _fromIdx:int;
		private var _toIdx:int;

		public function UnitMoveEvent(unit:GameUnit, fromIdx:int, toIdx:int, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(UnitMoveEvent.EVT_UNIT_MOVE, bubbles, cancelable);
			_unit = unit;
			_fromIdx = fromIdx;
			_toIdx = toIdx;
		}

		public override function clone() : Event
		{
			return new UnitMoveEvent(_unit, _fromIdx, _toIdx, bubbles, cancelable);
		}
		
		public function get unit():GameUnit 
		{
			return _unit;
		}
		
		public function get fromIdx():int 
		{
			return _fromIdx;
		}
		
		public function get toIdx():int 
		{
			return _toIdx;
		}
	}
	
}