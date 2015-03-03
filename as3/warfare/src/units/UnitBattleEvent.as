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
		private var _nextRole:Number;

		public function UnitBattleEvent(attacker:GameUnit, defender:GameUnit, nextRole:Number, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(UnitBattleEvent.EVT_UNIT_BATTLE, bubbles, cancelable);
			_attacker = attacker;
			_defender = defender;
			_nextRole = nextRole;
		}

		public override function clone() : Event
		{
			return new UnitBattleEvent(_attacker, _defender, _nextRole, bubbles, cancelable);
		}
		
		public function get attacker():GameUnit 
		{
			return _attacker;
		}
		
		public function get defender():GameUnit 
		{
			return _defender;
		}
		
		public function get nextRole():Number
		{
			return _nextRole;
		}
	}
	
}