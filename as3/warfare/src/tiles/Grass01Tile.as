package src.tiles
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Grass01Tile extends MovieClip
	{
		private var attr:TileAttr;
		
		public function Grass01Tile()
		{
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			attr = new TileAttr();
			
			attr.id = ConstTile.GRASS_01_ID;
			attr.def = ConstTile.GRASS_01_DEF;
			attr.moveable = ConstTile.GRASS_01_MOVEABLE;
			attr.moveEffort = ConstTile.GRASS_01_MOVEEFFORT;
			
			this.addChild(attr.image);
		}
	}
	
}