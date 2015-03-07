package src.buildings
{
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CityStatus
	{
		// Population growth.
		protected var _growth:Number;
		// Semianual cash.
		protected var _income:int;
		// Amount of militar units that support without cost.
		protected var _military:int;
		// Defense bonus for garrisoned soldiers.
		protected var _defense_bonus:int;
		
		public function CityStatus(growth:Number = 0, income:int = 0, military:int = 0, defense_bonus:int = 0)
		{
			_growth = growth;
			_income = income;
			_military = military;
			_defense_bonus = defense_bonus;
		}
		
		public function get growth():Number { return _growth;}
		public function set growth(value:Number):void {	_growth = value;}
		
		public function get income():int { return _income;}
		public function set income(value:int):void { _income = value;}
		
		public function get military():int {return _military;}
		public function set military(value:int):void {_military = value;}
		
		public function get defense_bonus():int {return _defense_bonus;}
		public function set defense_bonus(value:int):void {	_defense_bonus = value;	}
	}
	
}