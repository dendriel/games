package src
{
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Const 
	{		
		// Frame labels.
		static const GAME_INTRO:String = "gameIntro";
		static const GAME_PLAY:String = "gamePlay";
		static const GAME_WIN:String = "gameWin";
		static const GAME_LEVEL_TRANSITION:String = "gameLevelTransition";
		
		// Game Event Texts.
		static const GAME_EVENT_DELAY:Number = 5000; // 3 seconds.
		static const LEVEL_START_TEXT:String = "Scan the level!";
		static const LEVEL_CLEARED_TEXT:String = "Level cleared!";
		
		// Values.
		static const TILE_W:Number = 64;	//!< Tile width in pixels.
		static const TILE_H:Number = 64;	//!< Tile heigth in pixels.
		static const TILE_R:Number = 32;	//!< Tile radius.
		
		// Levels.
		static const LEVEL1_MAP_NAME:String = "level1map";
		static const LEVEL1_START_GOLD:Number = 150;
		
		static const LEVEL2_MAP_NAME:String = "level2map";
		static const LEVEL2_START_GOLD:Number = 200;
		
		static const LEVEL3_MAP_NAME:String = "level3map";
		static const LEVEL3_START_GOLD:Number = 300;
		
		// Monsters.
		static const SLIME_NAME:String = "Slime";
		static const SLIME_GOLD:Number = 50;
		static const SLIME_SPEED:Number = 2;
		static const SLIME_LIFE:Number = 15;
		static const SLIME_COLOR:Number = 0xffff00; // green.
		
		static const WATER_SLIME_NAME:String = "Water Slime";
		static const WATER_SLIME_GOLD:Number = 25;
		static const WATER_SLIME_SPEED:Number = 1;
		static const WATER_SLIME_LIFE:Number = 20;
		static const WATER_SLIME_COLOR:Number = 0xff0000; // blue.
		
		// Placing area.
		static const EMPTY_AREA:Number = 0;
		static const OCCUPY_AREA:Number = 1;
		static const EMPTY_AREA_LABEL:String = "empty";
		static const OCCUPY_AREA_LABEL:String = "occupy";
		static const INVISIBLE_AREA_LABEL:String = "invisible";
		
		// Bounds.
		static const SCREEN_SIZE:Point = new Point(640, 640);
		static const MENU_UPPER_BAR_POS:Point = new Point(0, 0);
		static const MENU_UPPER_BAR_SIZE:Point = new Point(SCREEN_SIZE.x, TILE_H);
		static const MENU_BOTTOM_BAR_POS:Point = new Point(0, SCREEN_SIZE.y - TILE_W*1 );
		static const MENU_BOTTOM_BAR_SIZE:Point = new Point(SCREEN_SIZE.x, TILE_H);
		
		// Events.
		static const EVT_END_REACHED_STR:String = "end_reached";
		static const EVT_MONSTER_KILLED:String = "monster_killed";
		static const EVT_LEVEL_END:String = "end_level";
		static const EVT_TOWER_REMOVED:String = "tower_removed";
		static const EVT_BULLET_REMOVED:String = "bullet_removed";
		static const EVT_NEXT_WAVE:String = "next_wave";
		
		// Towers information.
		static const NO_ENOUGH_MONEY:String = "You don't have enough money to buy this tower.";
		static const MAX_COOLDOWN_MS:Number = 5000;
		
		static const FIRE_TOWER_NAME:String = "Fire Tower";
		static const FIRE_TOWER_DESC:String = "Deals fire damage in the enemy."
		static const FIRE_TOWER_PRICE:Number = 100;
		static const FIRE_TOWER_COOLDOWN_MS:Number = 1500;
		static const FIRE_TOWER_RANGE:Number =  Const.TILE_R * 2;
		
		static const FIRE_BULLET:String = "Fire Bullet";
		static const FIRE_BULLET_DMG:Number = 5;
		static const FIRE_BULLET_SPEED:Number = 10;
		
		static const MOON_TOWER_NAME:String = "Moon Tower";
		static const MOON_TOWER_DESC:String = "Deals light damage in the enemy.";
		static const MOON_TOWER_PRICE:Number = 150;
		static const MOON_TOWER_COOLDOWN_MS:Number = 1500;
		static const MOON_TOWER_RANGE:Number =  Const.TILE_R * 2;
		
		static const MOON_BULLET:String = "Moon Bullet";
		static const MOON_BULLET_DMG:Number = 8;
		static const MOON_BULLET_SPEED:Number = 10;
		
		// Sounds.
		static const FIRE_SOUND:Number = 0;
		static const FIRE2_SOUND:Number = 1;
	}
	
}