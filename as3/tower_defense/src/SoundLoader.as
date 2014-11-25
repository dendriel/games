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
		
		private static const FIRE2_LOC:String = SOUND_LOC + "223611__ctcollab__fire-ball-release.mp3";
		private static var isFire2Ready:Boolean;
		private static var fire2:Sound;
		
		private static const COIN_LOC:String = SOUND_LOC + "coin3.mp3";
		private static var isCoinReady:Boolean;
		private static var coin:Sound;
		
		private static const VICTORY_LOC:String = SOUND_LOC + "victory2.mp3";
		private static var isVictoryReady:Boolean;
		private static var victory:Sound;
		
		private static const NEXT_LEVEL_LOC:String = SOUND_LOC + "203522__jack-master__drum-1_modified.mp3";
		private static var isNextLevelReady:Boolean;
		private static var nextLevel:Sound;
		
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
				
				fire2 = new Sound();
				isFire2Ready = false;
				fire2.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler, false, 0, true);
				fire2.addEventListener(Event.COMPLETE, onFire2LoadCompleted, false, 0, true);
				fire2.load(new URLRequest(FIRE2_LOC));
				
				coin = new Sound();
				isCoinReady = false;
				coin.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler, false, 0, true);
				coin.addEventListener(Event.COMPLETE, onCoinLoadCompleted, false, 0, true);
				coin.load(new URLRequest(COIN_LOC));
				
				victory = new Sound();
				isVictoryReady = false;
				victory.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler, false, 0, true);
				victory.addEventListener(Event.COMPLETE, onVictoryLoadCompleted, false, 0, true);
				victory.load(new URLRequest(VICTORY_LOC));
				
				nextLevel = new Sound();
				isNextLevelReady = false;
				nextLevel.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler, false, 0, true);
				nextLevel.addEventListener(Event.COMPLETE, onNextLevelLoadCompleted, false, 0, true);
				nextLevel.load(new URLRequest(NEXT_LEVEL_LOC));
				
			}
			catch (e:Error)
			{
				trace("Sound loading failed. " + e);
			}
		}
		
		public static function play(s:Number) : void
		{
			switch (s)
			{
				case Const.FIRE_SOUND:
					playFire();
					break;
				case Const.FIRE2_SOUND:
					playFire2();
					break;
				default:
					trace("Invalid sound!");
					break;
			}
		}
		
		public static function playFire() : void
		{
			if (isFireReady == true)
			{
				fire.play();
			}
		}
		
		public static function playFire2() : void
		{
			if (isFire2Ready == true)
			{
				fire2.play();
			}
		}
		
		public static function playCoin() : void
		{
			if (isCoinReady == true)
			{
				coin.play();
			}
		}
		
		public static function playVictory() : void
		{
			if (isCoinReady == true)
			{
				victory.play();
			}
		}
		
		public static function playNextLevel() : void
		{
			if (isNextLevelReady == true)
			{
				nextLevel.play();
			}
		}
		
		private static function onFireLoadCompleted(e:Event) : void
		{
			isFireReady = true;
			fire.removeEventListener(Event.COMPLETE, onFireLoadCompleted);
		}
		
		private static function onFire2LoadCompleted(e:Event) : void
		{
			isFire2Ready = true;
			fire2.removeEventListener(Event.COMPLETE, onFire2LoadCompleted);
		}
		
		private static function onCoinLoadCompleted(e:Event) : void
		{
			isCoinReady = true;
			coin.removeEventListener(Event.COMPLETE, onCoinLoadCompleted);
		}
		
		private static function onVictoryLoadCompleted(e:Event) : void
		{
			isVictoryReady = true;
			victory.removeEventListener(Event.COMPLETE, onVictoryLoadCompleted);
		}
		
		private static function onNextLevelLoadCompleted(e:Event) : void
		{
			isNextLevelReady = true;
			nextLevel.removeEventListener(Event.COMPLETE, onNextLevelLoadCompleted);
		}
		
		private static function ioErrorHandler(e:IOErrorEvent) : void
		{
			trace("Failed to load sound! " + e);
		}
	}
	
}