package src.units
{
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameUnitHolder
	{
		private var _units:Vector.<GameUnit>;
		
		public function GameUnitHolder()
		{
			_units = new Vector.<GameUnit>;
		}
		
		public function get units():Vector.<GameUnit> 
		{
			return _units;
		}
		
		public function set units(value:Vector.<GameUnit>):void 
		{
			_units = value;
		}
	}
}