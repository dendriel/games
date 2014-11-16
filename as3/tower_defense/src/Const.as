package src
{
	import flash.events.Event;
	
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
		
		// Events.
		static const EVT_END_REACHED_STR:String = "end_reached";
		static const EVT_MONSTER_KILLED:String = "monster_killed";
		static const EVT_LEVEL_END:String = "end_level";
		static const EVT_TOWER_REMOVED:String = "tower_removed";
		static const EVT_BULLET_REMOVED:String = "bullet_removed";
	}
	
}