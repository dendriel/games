package src.tiles
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tree01Tile extends MovieClip 
	{
		private var attr:TileAttr;
		
		public function TREE_01Tile()
		{
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			attr = new TileAttr();
			
			attr.id = ConstTile.TREE_01_ID;
			attr.def = ConstTile.TREE_01_DEF;
			attr.moveable = ConstTile.TREE_01_MOVEABLE;
			attr.moveEffort = ConstTile.TREE_01_MOVEEFFORT;
			
			this.addChild(attr.image);
		}
		
	}
	
}