package src
{
	import flash.events.Event;
	import flash.media.Sound;	
	import flash.media.SoundChannel;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class SoundLoader 
	{
		private static var _enable:Boolean = false;
		private static var intro:Sound;
		private static var introChannel:SoundChannel;
		
		private static var swordHit01:SwordHit01;
		
		// Load sounds.
		public static function init(enabled:Boolean=true) : void
		{
			intro = new IntroMusic();
			
			swordHit01 = new SwordHit01();
			
			_enable = enabled;
		}
		
		static public function enable() : void 
		{
			_enable = true;
		}
		
		static public function disable() : void 
		{
			_enable = false;
		}

//##################################################################################################
// Sounds.
		public static function playSwordHit01() : void
		{
			if (_enable != true)
			{
				return;
			}
			swordHit01.play();
		}
		
//##################################################################################################
// Intro music. TODO: could hide all this code in a "GameSound" class.
		public static function playIntro() : void
		{
			// If sound is disabled or already being played.
			if ( (_enable != true) || (introChannel != null) )
			{
				return;
			}
			
			introChannel = intro.play();
			introChannel.addEventListener(Event.SOUND_COMPLETE, handleSoundComplete_intro);
		}
		public static function stopIntro() : void
		{
			introChannel.stop();
			introChannel.removeEventListener(Event.SOUND_COMPLETE, handleSoundComplete_intro);
			introChannel = null;
		}
		
		// Loop music.
		public static function handleSoundComplete_intro(event:Event):void
		{
			SoundChannel(event.target).removeEventListener(Event.SOUND_COMPLETE, handleSoundComplete_intro);
			introChannel = null;
			playIntro();
		}
//##################################################################################################
//
	}
	
}