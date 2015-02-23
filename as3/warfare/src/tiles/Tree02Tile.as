package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tree02Tile extends GameTile 
	{		
		public function Tree02Tile()
		{			
			_id = ConstTile.TREE_02_ID;
			_def = ConstTile.TREE_01_DEF;
			_moveable = ConstTile.TREE_01_MOVEABLE;
			_moveEffort = ConstTile.TREE_01_MOVEEFFORT;
			_name = GameLanguage.lang.tree01_name;
			_desc = GameLanguage.lang.tree01_desc;
		}
		
	}
	
}