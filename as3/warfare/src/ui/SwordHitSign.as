package src.ui
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class SwordHitSign extends MovieClip 
	{
		public function SwordHitSign()
		{
			addEventListener(Event.ENTER_FRAME, handleEnterFrame, false, 0, true);
		}
		
		private function handleEnterFrame(e:Event) : void
		{
			if (currentLabel == "ended")
			{
				dispatchEvent(new Event(Const.EVT_ANIMATION_SWORD_HIT_ENDED));
				removeEventListener(Event.ENTER_FRAME, handleEnterFrame);
			}
		}
	}
	
}