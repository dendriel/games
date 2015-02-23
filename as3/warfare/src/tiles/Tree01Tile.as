package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tree01Tile extends GameTile 
	{		
		public function Tree01Tile()
		{			
			_id = ConstTile.TREE_01_ID;
			_def = ConstTile.GRASS_01_DEF;
			_moveable = ConstTile.GRASS_01_MOVEABLE;
			_moveEffort = ConstTile.GRASS_01_MOVEEFFORT;
			_name = GameLanguage.lang.grass01_name;
			_desc = GameLanguage.lang.grass01_desc;
		}
		
	}
	
}