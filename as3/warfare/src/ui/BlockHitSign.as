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
		public function BlockHitSign()
		{
			addEventListener(Event.ENTER_FRAME, handleEnterFrame, false, 0, true);
		}
		
		private function handleEnterFrame(e:Event) : void
		{
			if (currentLabel == "ended")
			{
				dispatchEvent(new Event(Const.EVT_ANIMATION_BLOCK_HIT_ENDED));
				removeEventListener(Event.ENTER_FRAME, handleEnterFrame);
			}
		}
	}
	
}