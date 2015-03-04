package src.units
{
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class UnitRemoveEvent extends Event 
	{
		public static const EVT_UNIT_REMOVE:String = "unit remove";
		
		// Event data.
		private var _unit:GameUnit;

		public function UnitRemoveEvent(unit:GameUnit, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(UnitRemoveEvent.EVT_UNIT_REMOVE, bubbles, cancelable);
			_unit = unit;
		}

		public override function clone() : Event
		{
			return new UnitRemoveEvent(_unit, bubbles, cancelable);
		}
		
		public function get unit():GameUnit 
		{
			return _unit;
		}
	}
	
}