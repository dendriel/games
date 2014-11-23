package src
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class ScoreHUD 
	{
		private var _gold:Number = 0;
		private var _missed:Number = 0;
		private var _wave:Number = 0;
		private var _level:Number = 0;
		
		private var menuHandler:MenuUIHandler;
		
		public function ScoreHUD() : void
		{
			menuHandler = null;
		}
		
		public function load(menuRef:MenuUIHandler) : void
		{
			menuHandler = menuRef;
			
			menuHandler.setLevel(_level);
			menuHandler.setWave(_wave);
			menuHandler.setMissed(_missed);
			menuHandler.setGold(_gold);
		}
		
		public function get level():Number 
		{
			return _level;
		}
		
		public function set level(value:Number):void 
		{
			_level = value;
			if (menuHandler != null)
			{
				menuHandler.setLevel(_level);
			}
		}
		
		public function get wave():Number 
		{
			return _wave;
		}
		
		public function resetWave() : void
		{
			_wave = 0;
			if (menuHandler != null)
			{
				menuHandler.setWave(_wave);
			}
		}
		
		public function set wave(value:Number):void 
		{
			_wave += value;
			if (menuHandler != null)
			{
				menuHandler.setWave(_wave);
			}
		}
		
		public function get missed():Number 
		{
			return _missed;
		}
		
		public function set missed(value:Number):void 
		{
			_missed = value;
			if (menuHandler != null)
			{
				menuHandler.setMissed(_missed);
			}
		}
		
		public function get gold():Number 
		{
			return _gold;
		}
		
		public function resetGold() : void
		{
			_gold = 0;
			if (menuHandler != null)
			{
				menuHandler.setGold(_wave);
			}
		}
		
		public function set gold(value:Number):void 
		{
			if (value > 0)
			{
				SoundLoader.playCoin();
			}
			
			_gold += value;
			if (menuHandler != null)
			{
				menuHandler.setGold(_gold);
			}
		}
		
		
	}
	
}