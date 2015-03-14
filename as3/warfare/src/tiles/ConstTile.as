package src.tiles
{
	import src.MediaSource;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class ConstTile 
	{
		// Tiles identifiers.
		public static const GRASS_TILE_ID = 1;
		
		// Internal definitions.
		public static const TILE_W = 32;
		public static const TILE_H = 32;
		
		// Move effort.
		public static const MOVEEFFORT_NONE:int = 0;
		public static const MOVEEFFORT_EXCELENT:int = 50; // Maximum value.
		public static const MOVEEFFORT_EASY:int = 30;
		public static const MOVEEFFORT_NORMAL:int = 0;
		public static const MOVEEFFORT_UNFAVORABLE = -15;
		public static const MOVEEFFORT_HARD:int = -30;
		
		// Defense value.
		public static const DEF_VALUE_UNFAVORABLE = -10;
		public static const DEF_VALUE_NONE:int = 0;
		public static const DEF_VALUE_LOW:int = 10;
		public static const DEF_VALUE_MEDIUM:int = 20;
		public static const DEF_VALUE_HIGH:int = 30;
		
		// Tile definitions.
		static const GRASS_DEF = ConstTile.DEF_VALUE_NONE;
		static const GRASS_MOVEABLE = true;
		static const GRASS_MOVEEFFORT = ConstTile.MOVEEFFORT_NORMAL;
		static const TREE_DEF = ConstTile.DEF_VALUE_LOW;
		static const TREE_MOVEABLE = true;
		static const TREE_MOVEEFFORT = ConstTile.MOVEEFFORT_HARD;
		static const MOUNTAIN_DEF = ConstTile.DEF_VALUE_NONE;
		static const MOUNTAIN_MOVEABLE = false;
		static const MOUNTAIN_MOVEEFFORT = ConstTile.MOVEEFFORT_NONE;
		static const RIVER_DEF = ConstTile.DEF_VALUE_NONE;
		static const RIVER_MOVEABLE = false;
		static const RIVER_MOVEEFFORT = ConstTile.MOVEEFFORT_NONE;
		static const ROAD_DEF = ConstTile.DEF_VALUE_NONE;
		static const ROAD_MOVEABLE = true;
		static const ROAD_MOVEEFFORT = ConstTile.MOVEEFFORT_EXCELENT;
		static const LAKE_DEF = ConstTile.DEF_VALUE_NONE;
		static const LAKE_MOVEABLE = false;
		static const LAKE_MOVEEFFORT = ConstTile.MOVEEFFORT_NONE;
		static const SEA_DEF = ConstTile.DEF_VALUE_NONE;
		static const SEA_MOVEABLE = false;
		static const SEA_MOVEEFFORT = ConstTile.MOVEEFFORT_NONE;
		static const CLIFF_DEF = ConstTile.DEF_VALUE_NONE;
		static const CLIFF_MOVEABLE = false;
		static const CLIFF_MOVEEFFORT = ConstTile.MOVEEFFORT_NONE;
		static const COAST_DEF = ConstTile.MOVEEFFORT_UNFAVORABLE;
		static const COAST_MOVEABLE = true;
		static const COAST_MOVEEFFORT = ConstTile.MOVEEFFORT_UNFAVORABLE;
		
	}
	
}