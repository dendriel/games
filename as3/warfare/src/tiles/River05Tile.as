package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class River05Tile extends GameTile 
	{		
		public function River05Tile()
		{			
			_id = ConstTile.RIVER_05_ID;
			_def = ConstTile.RIVER_01_DEF;
			_moveable = ConstTile.RIVER_01_MOVEABLE;
			_moveEffort = ConstTile.RIVER_01_MOVEEFFORT;
			_name = GameLanguage.lang.river01_name;
			_desc = GameLanguage.lang.river01_desc;
		}
		
	}
	
}