package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Mountain06Tile extends GameTile 
	{
		public function Mountain06Tile()
		{
			_id = ConstTile.MOUNTAIN_06_ID;
			_def = ConstTile.MOUNTAIN_01_DEF;
			_moveable = ConstTile.MOUNTAIN_01_MOVEABLE;
			_moveEffort = ConstTile.MOUNTAIN_01_MOVEEFFORT;
			_name = GameLanguage.lang.mountain01_name;
			_desc = GameLanguage.lang.mountain01_desc;
		}
	}
}