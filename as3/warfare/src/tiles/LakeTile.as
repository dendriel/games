package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class LakeTile extends GameTile 
	{		
		public function LakeTile()
		{
			_def = ConstTile.LAKE_DEF;
			_moveable = ConstTile.LAKE_MOVEABLE;
			_moveEffort = ConstTile.LAKE_MOVEEFFORT;
			_name = GameLanguage.lang.lake_name;
			_desc = GameLanguage.lang.lake_desc;
		}
	}
}