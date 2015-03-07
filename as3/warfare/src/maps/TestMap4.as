package src.maps
{
	import src.as3.math.Calc;
	import src.tiles.tileset1000.Tileset1000;
	import src.GamePlayer;
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
			
			players_list = new Vector.<GamePlayer>;
			
			var player1:GamePlayer = GamePlayer.newPlayer("Player 1", 10);
			player1.units_map = Calc.biToUniArray(new TestMap4UnitsPlayer1().layer);
			player1.buildings_map = Calc.biToUniArray(new TestMap4BuildingsPlayer1().layer);
			player1.indexOffset = 0;// tileset.baseIndex;
			
			players_list.push(player1);
			
			drawSelf();
		}
	}
	
}