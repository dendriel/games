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
		public static const TILE_W = 32;
		public static const TILE_H = 32;
		
		// Move effort.
		static const MOVEEFFORT_NONE:int = 0;
		static const MOVEEFFORT_EASY:int = 1;
		static const MOVEEFFORT_NORMAL:int = 2;
		static const MOVEEFFORT_HARD:int = 3;
		
		// Defense value.
		static const DEF_VALUE_NONE:int = 0;
		static const DEF_VALUE_LOW:int = 1;
		static const DEF_VALUE_MEDIUM:int = 2;
		static const DEF_VALUE_HIGH:int = 3;
		
		// Tiles IDs.
		public static const GRASS_01_ID:int = 1;
		public static const TREE_01_ID:int = 2;
		public static const TREE_02_ID:int = 4;
		public static const TREE_03_ID:int = 3;
		public static const TREE_04_ID:int = 5;
		public static const TREE_05_ID:int = 6;
		public static const TREE_06_ID:int = 7;
		public static const MOUNTAIN_01_ID:int = 8;
		public static const MOUNTAIN_02_ID:int = 9;
		public static const MOUNTAIN_03_ID:int = 10;
		public static const MOUNTAIN_04_ID:int = 11;
		public static const MOUNTAIN_05_ID:int = 12;
		public static const MOUNTAIN_06_ID:int = 13;
		public static const RIVER_01_ID:int = 14;
		public static const RIVER_02_ID:int = 15;
		public static const RIVER_03_ID:int = 16;
		public static const RIVER_04_ID:int = 17;
		public static const RIVER_05_ID:int = 18;
		public static const RIVER_06_ID:int = 19;
		public static const RIVER_07_ID:int = 20;
		public static const RIVER_08_ID:int = 21;		
		
		// Grass 01 tile definitions.
		static const GRASS_01_DEF = ConstTile.DEF_VALUE_NONE;
		static const GRASS_01_MOVEABLE = true;
		static const GRASS_01_MOVEEFFORT = ConstTile.MOVEEFFORT_NORMAL;
		
		// Tree 01-06 tile definitions.
		static const TREE_01_DEF = ConstTile.DEF_VALUE_LOW;
		static const TREE_01_MOVEABLE = true;
		static const TREE_01_MOVEEFFORT = ConstTile.MOVEEFFORT_HARD;
		
		// Mountain 01-06 tile definitions.
		static const MOUNTAIN_01_DEF = ConstTile.DEF_VALUE_NONE;
		static const MOUNTAIN_01_MOVEABLE = false;
		static const MOUNTAIN_01_MOVEEFFORT = ConstTile.MOVEEFFORT_NONE;
		
		// River 01-08 tile definitions.
		static const RIVER_01_DEF = ConstTile.DEF_VALUE_NONE;
		static const RIVER_01_MOVEABLE = false;
		static const RIVER_01_MOVEEFFORT = ConstTile.MOVEEFFORT_NONE;
	}
	
}