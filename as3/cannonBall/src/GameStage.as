package src
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameStage extends MovieClip
	{
		private var _w:Number; // stage.width
		private var _h:Number; // stage.height
		
		public function set h(value:Number):void
		{
			_h = value;
		}
		
		public function get h():Number 
		{
			return _h;
		}
		
		public function get w():Number 
		{
			return _w;
		}
		
		public function set w(value:Number):void 
		{
			_w = value;
		}
	
	}

}