package src.maps
{
	import src.as3.math.Calc;
	import src.tiles.tileset1000.Tileset1000;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class TestMap4 extends GameMap 
	{
		public function TestMap4() : void
		{
			tileset = new Tileset1000();
			tile_layer_map = new TestMap4Layer0().layer;
			_width_tiles = tile_layer_map[0].length;
			height_tiles = tile_layer_map.length;
			
			tile_layer_map = Calc.biToUniArray(tile_layer_map);
			unit_layer_map = Calc.biToUniArray(new TestMap4Layer2().layer);
			
			drawSelf();
		}
	}
	
}