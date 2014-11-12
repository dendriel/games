package src
{
	import flash.events.Event;
	import flash.media.Sound;
	import flash.net.URLRequest;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class SoundLoader 
	{
		private static const SOUND_LOC:String = "../sounds/";
		
		
		private static const FIRE_LOC:String = SOUND_LOC + "fire.mp3";
		private static var isFireReady:Boolean;
		private static var fire:Sound;
		
		// Load sounds.
		public static function init() : void
		{
			fire = new Sound();
			isFireReady = false;		
			fire.addEventListener(Event.COMPLETE, onfireLoadCompleted, false, 0, true);
			fire.load(new URLRequest(FIRE_LOC));
		}
		
		public static function playFire() : void
		{
			if (isFireReady == true)
			{
				fire.play();
			}
		}
		
		private static function onfireLoadCompleted(e:Event) : void
		{
			isFireReady = true;
		}
	}
	
}