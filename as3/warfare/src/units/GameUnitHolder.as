package src.units
{
	import flash.geom.Point;
	import src.tiles.ConstTile;
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
			// Move unit.
			unit.x = pos_pixels.x;
			unit.y = pos_pixels.y;
			
			// Move unit top image.
			if (unit.topImg != null)
			{
				unit.topImg.x = unit.x;
				unit.topImg.y = unit.y - ConstTile.TILE_H;
			}
			
			_units.push(unit);
		}
	}
}