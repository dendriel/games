package src
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * Keeps some properties of the working screen.
	 */
	public class GameStage extends MovieClip 
	{
		public var origin:Point;
		public var size:Point;
		public var stageR:Stage
		
		public function GameStage(stageRef:Stage)
		{
			origin = new Point;
			size = new Point;
			stageR = stageRef;
		}
	}
	
}