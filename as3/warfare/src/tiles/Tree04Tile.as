package src.tiles
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tree04Tile extends MovieClip 
	{
		private var attr:TileAttr;
		
		public function Tree04Tile()
		{
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			attr = new TileAttr();
			
			attr.id = ConstTile.TREE_04_ID;
			attr.def = ConstTile.TREE_01_DEF;
			attr.moveable = ConstTile.TREE_01_MOVEABLE;
			attr.moveEffort = ConstTile.TREE_01_MOVEEFFORT;
			
			this.addChild(attr.image);
		}
		
	}
	
}