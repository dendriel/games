package src.units
{
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class UnitBattleEvent extends Event 
	{
		public static const EVT_UNIT_BATTLE:String = "unit battle";
		
		// Event data.
		private var _attacker:GameUnit;
		private var _defender:GameUnit;

		public function UnitBattleEvent(attacker:GameUnit, defender:GameUnit, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(UnitBattleEvent.EVT_UNIT_BATTLE, bubbles, cancelable);
			_attacker = attacker;
			_defender = defender;
		}

		public override function clone() : Event
		{
			return new UnitBattleEvent(_attacker, _defender, bubbles, cancelable);
		}
		
		public function get attacker():GameUnit 
		{
			return _attacker;
		}
		
		public function get defender():GameUnit 
		{
			return _defender;
		}
	}
	
}