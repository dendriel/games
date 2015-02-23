package src.units
{
	import flash.geom.Point;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameUnitHolder
	{
		private var pos_pixels:Point;
		private var _units:Vector.<GameUnit>;
		
		public function GameUnitHolder(px:int, py:int)
		{
			_units = new Vector.<GameUnit>;
			pos_pixels = new Point(px, py);
		}
		
		public function get units():Vector.<GameUnit> 
		{
			return _units;
		}
		
		public function set units(value:Vector.<GameUnit>):void 
		{
			_units = value;
		}
		
		public function addUnit(unit:GameUnit) : void
		{
			unit.x = pos_pixels.x;
			unit.y = pos_pixels.y;
			_units.push(unit);
		}
	}
}