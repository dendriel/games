package src
{
	import flash.media.Sound;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class SoundHandler 
	{
		static var fire:Sound;
		
		// Load sounds.
		static function init() : void
		{
			fire = new Fire;
		}
		
		static function playFire() : void
		{
			fire.play();
		}
	}
	
}