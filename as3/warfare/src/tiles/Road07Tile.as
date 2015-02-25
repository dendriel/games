package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Road07Tile extends GameTile 
	{
		public function Road07Tile()
		{
			_id = ConstTile.ROAD_07_ID;
			_def = ConstTile.ROAD_01_DEF;
			_moveable = ConstTile.ROAD_01_MOVEABLE;
			_moveEffort = ConstTile.ROAD_01_MOVEEFFORT;
			_name = GameLanguage.lang.road01_name;
			_desc = GameLanguage.lang.road01_desc;
			
		}
	}
	
}