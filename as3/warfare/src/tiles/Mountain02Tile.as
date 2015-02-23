package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Mountain02Tile extends GameTile 
	{		
		public function Mountain02Tile()
		{
			_id = ConstTile.MOUNTAIN_02_ID;
			_def = ConstTile.MOUNTAIN_01_DEF;
			_moveable = ConstTile.MOUNTAIN_01_MOVEABLE;
			_moveEffort = ConstTile.MOUNTAIN_01_MOVEEFFORT;
			_name = GameLanguage.lang.mountain01_name;
			_desc = GameLanguage.lang.mountain01_desc;
		}
	}
}