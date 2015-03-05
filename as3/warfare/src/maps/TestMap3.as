package src.maps
{
	import src.as3.math.Calc;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class TestMap3 extends GameMap 
	{
		private var building_layer_data:Array;
		private var unit_layer_data:Array;

		public function TestMap3() : void
		{
			tile_layer_map = new TestMap3Layer0().layer;
			_width_tiles = tile_layer_map[0].length;
			height_tiles = tile_layer_map.length;
			
			tile_layer_map = Calc.biToUniArray(tile_layer_map);
			trace(tile_layer_map);
			
			drawSelf();
		}
	}
	
}