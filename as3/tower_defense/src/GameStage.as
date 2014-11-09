package src
{
	import flash.display.MovieClip;
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
		
		public function GameStage()
		{
			origin = new Point;
			size = new Point;
		}
	}
	
}