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
		private var _unitUID:int;
		private var _fromIdx:int;
		private var _toIdx:int;

		public function UnitMoveEvent(unitUID:int, fromIdx:int, toIdx:int, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(UnitMoveEvent.EVT_UNIT_MOVE, bubbles, cancelable);
			_unitUID = unitUID;
			_fromIdx = fromIdx;
			_toIdx = toIdx;
		}

		public override function clone() : Event
		{
			return new UnitMoveEvent(_unitUID, _fromIdx, _toIdx, bubbles, cancelable);
		}
		
		public function get unitUID():int 
		{
			return _unitUID;
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