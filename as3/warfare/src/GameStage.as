package src
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * Keeps some properties of the working screen.
	 */
	public class GameStage extends MovieClip 
	{
		private static var _stageR:Stage;
		
		public static function set stageR(value:Stage) : void
		{
			_stageR = value;
		}
		
		public static function get stageR() : Stage
		{
			return _stageR;
		}
	}
	
}