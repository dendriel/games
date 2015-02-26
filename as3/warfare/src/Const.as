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
		public static const TIMER_POS_X = 585;
		public static const TIMER_POS_Y = 68;
		public static const DAY_TIME_MS = 2000;
		public static const MAIN_MENU_BUTTON_OFFSET = 35;
		public static const MAIN_MENU_TITLE = "WARFARE";
		public static const TITLE_VERTICAL_OFFSET = 100;
		public static const MAX_MAP_MOVE_OFFSET = 64;
		public static const DEFAULT_WEIGHT = 10;
		public static const NODE_DISCONNECTED = -1;
		
		
		// Main Menu.
		public static const SINGLE_PLAYER_S = "Single Player";
		public static const MULTI_PLAYER_S = "Multiplayer";
		public static const CREDITS_S = "Credits";
		
		// GamePlay definitions.
		public static const MENU_AREA_W = (800 - 32);
		public static const MENU_AREA_H = (120 - 16);
		public static const MAP_AREA_W = (SCREEN_SIZE_W - 32);
		public static const MAP_AREA_H = (SCREEN_SIZE_H - MENU_AREA_H - 16); // with '-16', the menubar is placed over the big frame.
		
		public static const MAP_AREA_POS_X = 16;
		public static const MAP_AREA_POS_Y = 16;
		public static const MENU_AREA_POS_X = 16;
		public static const MENU_AREA_POS_Y = (MAP_AREA_H + MAP_AREA_POS_Y);
		
		// Game Events.
		public static const EVT_SINGLE_PLAYER_CLICK = "single player click";
		public static const EVT_MULTIPLAYER_CLICK = "multiplayer click";
		public static const EVT_CREDITS_CLICK = "credits click";
	}
	
}