package src.tiles
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Mountain05Tile extends MovieClip 
	{
		private var attr:TileAttr;
		
		public function Mountain05Tile()
		{
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			attr = new TileAttr();
			
			attr.id = ConstTile.MOUNTAIN_05_ID;
			attr.def = ConstTile.MOUNTAIN_01_DEF;
			attr.moveable = ConstTile.MOUNTAIN_01_MOVEABLE;
			attr.moveEffort = ConstTile.MOUNTAIN_01_MOVEEFFORT;
			
			this.addChild(attr.image);
		}
		
	}
	
}