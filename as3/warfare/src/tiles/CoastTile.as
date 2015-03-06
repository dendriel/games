package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CoastTile extends GameTile 
	{		
		public function CoastTile()
		{
			_def = ConstTile.COAST_DEF;
			_moveable = ConstTile.COAST_MOVEABLE;
			_moveEffort = ConstTile.COAST_MOVEEFFORT;
			_name = GameLanguage.lang.coast_name;
			_desc = GameLanguage.lang.coast_desc;
		}
	}
}