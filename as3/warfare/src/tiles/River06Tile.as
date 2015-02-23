package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class River06Tile extends GameTile 
	{		
		public function River06Tile()
		{			
			_id = ConstTile.RIVER_06_ID;
			_def = ConstTile.RIVER_01_DEF;
			_moveable = ConstTile.RIVER_01_MOVEABLE;
			_moveEffort = ConstTile.RIVER_01_MOVEEFFORT;
			_name = GameLanguage.lang.river01_name;
			_desc = GameLanguage.lang.river01_desc;
		}
		
	}
	
}