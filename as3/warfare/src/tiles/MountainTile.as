package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MountainTile extends GameTile 
	{
		public function MountainTile()
		{
			_def = ConstTile.MOUNTAIN_DEF;
			_moveable = ConstTile.MOUNTAIN_MOVEABLE;
			_moveBonus = ConstTile.MOUNTAIN_MOVEEFFORT;
			_name = GameLanguage.lang.mountain_name;
			_desc = GameLanguage.lang.mountain_desc;
		}
	}
}