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
		public static const MAIN_MENU_BUTTON_OFFSET = 35;
		public static const MAIN_MENU_TITLE = "WARFARE";
		public static const TITLE_VERTICAL_OFFSET = 100;
		public static const MAX_MAP_MOVE_OFFSET = 64;
		public static const DEFAULT_WEIGHT = 100;
		public static const NODE_DISCONNECTED = -1;
		public static const COOR_TXT_POS_X = SCREEN_SIZE_W / 2 - 32;
		public static const COOR_TXT_POS_Y = 20;
		public static const UNIT_WEIGHT = 1000000;
		
		// Status menus.
		public static const PLAYER_STATUS_POS_X = 16;
		public static const PLAYER_STATUS_POS_Y = 16;
		static const BUILDING_GROWTH_LABEL = "growth label";
		static const BUILDING_POPULATION_LABEL = "population label";
		static const BUILDING_INCOME_LABEL = "income label";
		static const MILITARY_LABEL = "military label";
		static const DEFENSE_LABEL = "defense label";
		static const ATTACK_LABEL = "attack label";
		static const SHIELD_LABEL = "shield label";
		static const DISTANCE_LABEL = "distance label";
		static const COST_LABEL = "cost label";
		static const MOVE_BONUS_LABEL = "move bonus label";
		static const MOVE_PATH_LABEL = "move path label";
		
		// Time definitions.
		public static const DAY_TIME_MS = 2000;
		public static const HALF_DAY_MS:Number = DAY_TIME_MS / 2;
		public static const MOVE_TIME_1_DAY:Number = 1;
		public static const MOVE_TIME_2_DAYS:Number = MOVE_TIME_1_DAY / 2;
		public static const MOVE_TIME_3_DAYS:Number = MOVE_TIME_1_DAY / 3;
		
		// Main Menu.
		public static const SINGLE_PLAYER_S = "Single Player";
		public static const MULTI_PLAYER_S = "Multiplayer";
		public static const CREDITS_S = "Credits";
		
		// GamePlay definitions.
		public static const MENU_AREA_W = (800 - 32);
		public static const MENU_AREA_H = (120 - 16);
		public static const MAP_AREA_W = (SCREEN_SIZE_W - 32);
		public static const MAP_AREA_H = (SCREEN_SIZE_H - MENU_AREA_H - 16); // with '-16', the menubar is placed over the big frame.
		public static const STATUS_DISPLAY_POS_X = 8;
		public static const STATUS_DISPLAY_POS_Y = 8;
		
		public static const MAP_AREA_POS_X = 16;
		public static const MAP_AREA_POS_Y = 16;
		public static const MENU_AREA_POS_X = 16;
		public static const MENU_AREA_POS_Y = (MAP_AREA_H + MAP_AREA_POS_Y);
		
		public static const CHAT_WIDTH = 300;
		public static const CHAT_HEIGHT = 110;	
		public static const CHAT_POX_X = SCREEN_SIZE_W - CHAT_WIDTH - 16;
		public static const CHAT_POX_Y = MENU_AREA_POS_Y - CHAT_HEIGHT;
		
		// Game Events.
		public static const EVT_SINGLE_PLAYER_CLICK = "single player click";
		public static const EVT_MULTIPLAYER_CLICK = "multiplayer click";
		public static const EVT_CREDITS_CLICK = "credits click";
		public static const EVT_ANIMATION_SWORD_HIT_ENDED = "animation sword hit ended";
		public static const EVT_ANIMATION_DAMAGE_ENDED = "animation damage ended";
		public static const EVT_ANIMATION_BLOCK_HIT_ENDED = "animation block hit ended";
		
		// Animation states.
		public static const ANIMATION_IDLE = "idle";
		public static const ANIMATION_PLAYING = "animating";
		public static const ANIMATION_ENDED = "ended";
	}
	
}