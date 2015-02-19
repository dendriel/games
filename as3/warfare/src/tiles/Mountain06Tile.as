package src.tiles
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Mountain06Tile extends MovieClip 
	{
		private var attr:TileAttr;
		
		public function Mountain06Tile()
		{
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			attr = new TileAttr();
			
			attr.id = ConstTile.MOUNTAIN_06_ID;
			attr.def = ConstTile.MOUNTAIN_01_DEF;
			attr.moveable = ConstTile.MOUNTAIN_01_MOVEABLE;
			attr.moveEffort = ConstTile.MOUNTAIN_01_MOVEEFFORT;
			
			this.addChild(attr.image);
		}
		
	}
	
}