package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class TreeTile extends GameTile 
	{		
		public function TreeTile()
		{			
			_def = ConstTile.TREE_DEF;
			_moveable = ConstTile.TREE_MOVEABLE;
			_moveBonus = ConstTile.TREE_MOVEEFFORT;
			_name = GameLanguage.lang.tree_name;
			_desc = GameLanguage.lang.tree_desc;
		}
		
	}
	
}