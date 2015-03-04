package src.ui
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class BlockHitSign extends MovieClip 
	{		
		public function get ended() : Boolean
		{
			return (currentLabel == Const.ANIMATION_ENDED);
		}
		
		public function get playing() : Boolean
		{
			return (currentLabel == Const.ANIMATION_PLAYING);
		}
	}
	
}