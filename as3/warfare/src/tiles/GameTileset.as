package src.tiles
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	
	import src.as3.math.Calc;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameTileset 
	{
		protected var imageData:BitmapData;
		protected var baseIndex:int;
		protected var tile_width:int;
		protected var tile_height:int;
		
		public function drawTile(destn:BitmapData, tile:int, destnIdx:int) : void
		{
			var tileOffset:int = tile - baseIndex - 1;
			var destnPos:Point = Calc.idx_to_pixel(destnIdx, (destn.width / tile_width), tile_width);
			var tilePos:Point = Calc.idx_to_pixel(tileOffset, (imageData.width / tile_width) , tile_width);
			
			var rect:Rectangle = new Rectangle(tilePos.x, tilePos.y, tile_width, tile_height);
			
			destn.copyPixels(imageData, rect, new Point(destnPos.x, destnPos.y));
		}
		
		public function getTileElement(type:int) : GameTile
		{
			switch (type)
			{
				default:
					trace("tile " + type + " not registered. This function must be overwritted.");
					return new GrassTile();
			}
		}
	}
	
}