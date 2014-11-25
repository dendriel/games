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
		
		private var _menu:MenuUIHandler;
		
		public function GameStage(stageRef:Stage)
		{
			origin = new Point;
			size = new Point;
			stageR = stageRef;
		}
		
		/**
		 * @usage Add a movie clip bellow the menuUI.
		 * @param	m the movie clip to be added.
		 */
		public function addChildBellowMenu(m:MovieClip) : void
		{
			var idx:Number = this.getChildIndex(_menu);
			this.addChildAt(m, idx);
		}
		
		public function set menu(value:MenuUIHandler):void 
		{
			_menu = value;
			this.addChild(_menu);
		}
	}
	
}