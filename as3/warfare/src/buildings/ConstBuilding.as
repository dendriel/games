package src.buildings
{
	import src.tiles.ConstTile;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class ConstBuilding 
	{
		// Internal definitions.
		public static const TILE_W = 32;
		public static const TILE_H = 32;
		
		// Building IDs.
		public static const BRIDGE_01_ID:int = 22;
		public static const BRIDGE_02_ID:int = 23;
		
		// Bridge 01-02 definitions.
		static const BRIDGE_01_DEF = ConstTile.DEF_VALUE_UNFAVORABLE;
		static const BRIDGE_01_MOVEABLE = true;
		static const BRIDGE_01_MOVEEFFORT = ConstTile.MOVEEFFORT_UNFAVORABLE;
	}
	
}