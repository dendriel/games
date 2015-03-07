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
		protected var _baseIndex:int;
		protected var tile_width:int;
		protected var tile_height:int;
		protected var randomTiles:Array; // [tile index, callback : Point]
		
		public function drawTile(destn:BitmapData, tile:int, destnIdx:int) : void
		{
			var destnPos:Point = Calc.idx_to_pixel(destnIdx, (destn.width / tile_width), tile_width);
			var tilePos:Point = findTileDataPos(tile);
			
			var rect:Rectangle = new Rectangle(tilePos.x, tilePos.y, tile_width, tile_height);
			destn.copyPixels(imageData, rect, new Point(destnPos.x, destnPos.y));
		}
		
		private function findTileDataPos(index:int) : Point
		{
			if (randomTiles != null)
			{
				for (var i in randomTiles)
				{
					var randomTileIndex:int = randomTiles[i][0];
					var randomTileCallback:Function = randomTiles[i][1];
					if (randomTileIndex == index)
					{
						return randomTileCallback();
					}
				}
			}
			// There is no callback registered for this tile.
			var tileOffset:int = index - _baseIndex - 1;
			return Calc.idx_to_pixel(tileOffset, (imageData.width / tile_width) , tile_width);
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
		
		public function get baseIndex():int 
		{
			return _baseIndex;
		}
	}
	
}