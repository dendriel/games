package src
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class  Const
	{
		// UI Events.
		public static const START_GAME_CLICK_EVT:String = "start_game_click";
		
		// Cannon Defaults.
		public static const CANNON_MIN_ANGLE:Number = 180;
		public static const CANNON_MAX_ANGLE:Number = 360;
		public static const CANNON_ROTATION_SPEED:Number = 1;	// 2 degrees per iteration.
		public static const CANNON_BALL_RADIUS_DEFAULT:Number = 10
		public static const CANNON_BALL_SPEED_DEFAULT:Number = 12;
		public static const CANNON_BALL_MASS_DEFAULT:Number = 2;
		public static const CANNON_BALL_ELASTICITY_DEFAULT:Number = 0.3; // 100%
		public static const CANNON_BALL_MINIMUM_SPEED:Number = 0.3; // speed limit before stopping completely.
		
		// Game Play Events.
		public static const EVT_CANNON_SHOOTING:String = "cannon_shooting";
		public static const EVT_HIT_TARGET:String = "hit_target";
		public static const EVT_BALL_STOPPED:String = "ball_stopped";
		
		// Stage Defaults.
		public static const STAGE_WIDTH_STR = "480";
		public static const STAGE_HEIGHT_STR = "320";
		public static const STAGE_WIDTH = 480;
		public static const STAGE_HEIGHT = 320;
		public static const STAGE_DEFAULT_ORIGIN_X = 0;
		public static const STAGE_DEFAULT_ORIGIN_Y = 0;
		public static const STAGE_DEFAULT_WIDTH = 480;
		public static const STAGE_DEFAULT_HEIGHT = 320;
		public static const GRAVITY = 0.1;
		
	}
	
}