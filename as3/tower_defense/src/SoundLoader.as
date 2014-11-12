package src
{
	import flash.errors.IOError;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.media.Sound;
	import flash.net.URLRequest;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class SoundLoader 
	{
		private static const SOUND_LOC:String = "sounds/";
		
		
		private static const FIRE_LOC:String = SOUND_LOC + "fire.mp3";
		private static var isFireReady:Boolean;
		private static var fire:Sound;
		
		// Load sounds.
		public static function init() : void
		{
			try
			{
				fire = new Sound();
				isFireReady = false;
				fire.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler, false, 0, true);
				fire.addEventListener(Event.COMPLETE, onFireLoadCompleted, false, 0, true);
				fire.load(new URLRequest(FIRE_LOC));
			}
			catch (e:Error)
			{
				trace("Sound loading failed. " + e);
			}
		}
		
		public static function playFire() : void
		{
			if (isFireReady == true)
			{
				fire.play();
			}
		}
		
		private static function onFireLoadCompleted(e:Event) : void
		{
			isFireReady = true;
			fire.removeEventListener(Event.COMPLETE, onFireLoadCompleted);
		}
		
		private static function ioErrorHandler(e:IOErrorEvent) : void
		{
			trace("Failed to load sound! " + e);
		}
	}
	
}