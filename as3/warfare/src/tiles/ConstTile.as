package src.tiles
{
	import src.MediaSource;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class ConstTile 
	{
		// Internal definitions.
		static const TILE_W = 32;
		static const TILE_H = 32;
		
		static const MOVEEFFORT_EASY:int = 1;
		static const MOVEEFFORT_NORMAL:int = 2;
		static const MOVEEFFORT_HARD:int = 2;
		
		// Tiles IDs.
		static const GRASS01_ID:int = 0;
		
		
		// Grass 01 tile definitions.
		static const GRASS01_LOC = MediaSource.IMG_PATH + "grass01.png";
		static const GRASS01_DEF = 0;
		static const GRASS01_MOVEABLE = true;
		static const GRASS01_MOVEEFFORT = ConstTile.MOVEEFFORT_EASY;
	}
	
}