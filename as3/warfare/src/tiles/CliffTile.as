package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CliffTile extends GameTile 
	{
		public function CliffTile()
		{
			_def = ConstTile.CLIFF_DEF;
			_moveable = ConstTile.CLIFF_MOVEABLE;
			_moveBonus = ConstTile.CLIFF_MOVEEFFORT;
			_name = GameLanguage.lang.cliff_name;
			_desc = GameLanguage.lang.cliff_desc;
		}
	}
}