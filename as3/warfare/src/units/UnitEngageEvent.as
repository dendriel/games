package src.units
{
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class UnitEngageEvent extends Event 
	{
		public static const EVT_UNIT_ENGAGE:String = "unit engage";
		
		// Event data.
		private var _attacker:GameUnit;
		private var _defender:GameUnit;
		private var _defenderExpectedPos:int; // Check if the enemy still in the expected position.

		public function UnitEngageEvent(attacker:GameUnit, defender:GameUnit, defenderPos:int, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(UnitEngageEvent.EVT_UNIT_ENGAGE, bubbles, cancelable);
			_attacker = attacker;
			_defender = defender;
			_defenderExpectedPos = defenderPos;
		}

		public override function clone() : Event
		{
			return new UnitEngageEvent(_attacker, _defender, _defenderExpectedPos, bubbles, cancelable);
		}
		
		public function get attacker():GameUnit 
		{
			return _attacker;
		}
		
		public function get defender():GameUnit 
		{
			return _defender;
		}
		
		public function get defenderExpectedPos():int
		{
			return _defenderExpectedPos;
		}
	}
	
}