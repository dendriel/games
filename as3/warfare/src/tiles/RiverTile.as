package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class RiverTile extends GameTile 
	{		
		public function RiverTile()
		{
			_def = ConstTile.RIVER_DEF;
			_moveable = ConstTile.RIVER_MOVEABLE;
			_moveEffort = ConstTile.RIVER_MOVEEFFORT;
			_name = GameLanguage.lang.river_name;
			_desc = GameLanguage.lang.river_desc;
		}
	}
}