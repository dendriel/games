package src.tiles
{
	import flash.display.MovieClip;
	import src.as3.media.Image;
	
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
			
			attr.id = ConstTile.GRASS01_ID;
			attr.def = ConstTile.GRASS01_DEF;
			attr.moveable = ConstTile.GRASS01_MOVEABLE;
			attr.moveEffort = ConstTile.GRASS01_MOVEEFFORT;
			
			this.addChild(attr.image);
		}
	}
	
}