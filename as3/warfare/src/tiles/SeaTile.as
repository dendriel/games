package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class SeaTile extends GameTile 
	{		
		public function SeaTile()
		{
			_def = ConstTile.SEA_DEF;
			_moveable = ConstTile.SEA_MOVEABLE;
			_moveBonus = ConstTile.SEA_MOVEEFFORT;
			_name = GameLanguage.lang.sea_name;
			_desc = GameLanguage.lang.sea_desc;
		}
	}
}