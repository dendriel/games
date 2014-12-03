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
		private static var fire:Sound;
		private static var fire2:Sound;
		private static var coin:Sound;
		private static var victory:Sound;
		private static var victory1:Sound;
		private static var nextLevel:Sound;
		private static var gameOver:Sound;
		
		// Load sounds.
		public static function init() : void
		{
			fire = new FireS();
			fire2 = new Fire2S();
			coin = new CoinS();
			victory = new VictoryS();
			nextLevel = new NextLevelS();
			gameOver = new GameOverS();
			victory1 = new Victory1S();
		}
		
		public static function play(s:Number) : void
		{
			switch (s)
			{
				case Const.FIRE_SOUND:
					fire.play();
					break;
				case Const.FIRE2_SOUND:
					fire2.play();
					break;
				default:
					trace("Invalid sound!");
					break;
			}
		}
		
		public static function playFire() : void
		{
			fire.play();
		}
		
		public static function playFire2() : void
		{
			fire2.play();
		}
		
		public static function playCoin() : void
		{
			coin.play();
		}
		
		public static function playVictory() : void
		{
			victory.play();
		}
		
		public static function playNextLevel() : void
		{
			nextLevel.play();
		}
		
		public static function playGameOver() : void
		{
			gameOver.play();
		}
		
		public static function playVictory1() : void
		{
			victory1.play();
		}
	}
	
}