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
		
		// Values.
		static const TILE_W:Number = 64;	//!< Tile width in pixels.
		static const TILE_H:Number = 64;	//!< Tile heigth in pixels.
		static const TILE_R:Number = 32;	//!< Tile radius.
		static const DEF_GOLD:Number = 1000;
		
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
		static const MOON_BULLET_DMG:Number = 7;
		static const MOON_BULLET_SPEED:Number = 10;
		
		// Sounds.
		static const FIRE_SOUND:Number = 0;
		static const FIRE2_SOUND:Number = 1;
	}
	
}