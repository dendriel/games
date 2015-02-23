package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class River03Tile extends GameTile 
	{		
		public function River03Tile()
		{
			_id = ConstTile.RIVER_03_ID;
			_def = ConstTile.RIVER_01_DEF;
			_moveable = ConstTile.RIVER_01_MOVEABLE;
			_moveEffort = ConstTile.RIVER_01_MOVEEFFORT;
			_name = GameLanguage.lang.river01_name;
			_desc = GameLanguage.lang.river01_desc;
		}
	}
}