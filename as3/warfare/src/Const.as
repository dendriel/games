package src
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Const 
	{
		// Misc.
		public static const SCREEN_SIZE_W = 800;
		public static const SCREEN_SIZE_H = 600;
		public static const MAIN_MENU_BUTTON_OFFSET = 35;
		public static const MAIN_MENU_TITLE = "WARFARE";
		public static const TITLE_VERTICAL_OFFSET = 100;
		
		// Main Menu.
		public static const SINGLE_PLAYER_S = "Single Player";
		public static const MULTI_PLAYER_S = "Multiplayer";
		public static const CREDITS_S = "Credits";
		
		// GamePlay definitions.
		public static const MENU_AREA_W = (800 - 32); // 32 bits for the frame area.
		public static const MENU_AREA_H = (120 - 16);
		
		public static const MAP_AREA_W = (SCREEN_SIZE_W - 32); // 32 bits for the frame area.
		public static const MAP_AREA_H = (SCREEN_SIZE_H - MENU_AREA_H - 16);
		public static const MAP_AREA_POS_X = 16;
		public static const MAP_AREA_POS_Y = 16;
		
		// Game Events.
		public static const EVT_SINGLE_PLAYER_CLICK = "single player click";
		public static const EVT_MULTIPLAYER_CLICK = "multiplayer click";
		public static const EVT_CREDITS_CLICK = "credits click";
	}
	
}