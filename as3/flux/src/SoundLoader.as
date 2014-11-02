package  
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
		
		// We should create a SoundObj class to hold the variables related to a sound.. but not
		// right now :)
		private static const ENERGY_DOWN_LOC:String = SOUND_LOC + "bad_energy.mp3";
		private static var isEnergyDownReady:Boolean;
		private static var energyDown:Sound;
		
		private static const ENERGY_UP_LOC:String = SOUND_LOC + "good_energy.mp3";
		private static var isEnergyUpReady:Boolean;
		private static var energyUp:Sound;
		
		private static const EXPLOSION_LOC:String = SOUND_LOC + "explosion.mp3";
		private static var isExmplosionReady:Boolean;
		private static var explosion:Sound;
		
		private static const OUT_OF_POWER_LOC:String = SOUND_LOC + "powerdown.mp3";
		private static var isOutOfPowerReady:Boolean;
		private static var outOfPower:Sound;
		
		public static function init() : void
		{
			energyDown = new Sound();
			isEnergyDownReady = false;		
			energyDown.addEventListener(Event.COMPLETE, onEnergyDownLoadCompleted, false, 0, true);
			energyDown.load(new URLRequest(ENERGY_DOWN_LOC));
			
			energyUp = new Sound();
			isEnergyUpReady = false;
			energyUp.addEventListener(Event.COMPLETE, onEnergyUpLoadCompleted, false, 0, true);
			energyUp.load(new URLRequest(ENERGY_UP_LOC));
			
			explosion = new Sound();
			isExmplosionReady = false;
			explosion.addEventListener(Event.COMPLETE, onExplosionCompleted, false, 0, true);
			explosion.load(new URLRequest(EXPLOSION_LOC));
			
			outOfPower = new Sound();
			isOutOfPowerReady = false;
			outOfPower.addEventListener(Event.COMPLETE, onOutOfPowerCompleted, false, 0, true);
			outOfPower.load(new URLRequest(OUT_OF_POWER_LOC));
		}
		
		public static function playEnergyDownSound() : void
		{
			if (isEnergyDownReady == true)
			{
				energyDown.play();
			}
		}
		
		public static function playEnergyUpSound() : void
		{
			if (isEnergyUpReady == true)
			{
				energyUp.play();
			}
		}
		
		public static function playExplosionSound() : void
		{
			if (isExmplosionReady == true)
			{
				explosion.play();
			}
		}
		
		public static function playOutOfPowerSound() : void
		{
			if (isOutOfPowerReady == true)
			{
				outOfPower.play();
			}
		}
		
		private static function onEnergyDownLoadCompleted(e:Event) : void
		{
			isEnergyDownReady = true;
		}
		
		private static function onEnergyUpLoadCompleted(e:Event) : void
		{
			isEnergyUpReady = true;
		}
		
		private static function onExplosionCompleted(e:Event) : void
		{
			isExmplosionReady = true;
		}
		
		private static function onOutOfPowerCompleted(e:Event) : void
		{
			isOutOfPowerReady = true;
		}
	}
}