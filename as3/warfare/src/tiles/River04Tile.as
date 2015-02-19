package src.tiles
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class River04Tile extends MovieClip 
	{
		private var attr:TileAttr;
		
		public function River04Tile()
		{
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			attr = new TileAttr();
			
			attr.id = ConstTile.RIVER_04_ID;
			attr.def = ConstTile.RIVER_01_DEF;
			attr.moveable = ConstTile.RIVER_01_MOVEABLE;
			attr.moveEffort = ConstTile.RIVER_01_MOVEEFFORT;
			
			this.addChild(attr.image);
		}
		
	}
	
}