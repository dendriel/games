package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class ScoreHUD extends MovieClip
	{
		private var _gold:Number = 0;
		private var _missed:Number = 0;
		private var _wave:Number = 0;
		private var _level:Number = 0;
		private var _maxMissed = Const.MAX_MISSED_WAVE;
		
		private var _menuHandler:MenuUIHandler;
		
		public function reload() : void
		{
			resetWave();
			resetGold();
			resetMissed();
		}
		
		public function get level():Number 
		{
			return _level;
		}
		
		public function set level(value:Number):void 
		{
			_level = value;
			if (_menuHandler != null)
			{
				_menuHandler.setLevel(_level);
			}
		}
		
		public function get wave():Number 
		{
			return _wave;
		}
		
		public function resetWave() : void
		{
			_wave = 0;
			if (_menuHandler != null)
			{
				_menuHandler.setWave(_wave);
			}
		}
		
		public function set wave(value:Number):void 
		{
			_wave += value;
			if (_menuHandler != null)
			{
				_menuHandler.setWave(_wave);
			}
		}
		
		public function get missed():Number 
		{
			return _missed;
		}
		
		public function resetMissed() : void
		{
			_missed = 0;
			if (_menuHandler != null)
			{
				_menuHandler.setMissed(_missed);
			}
		}
		
		public function set missed(value:Number):void 
		{
			_missed += value;
			if (_menuHandler != null)
			{
				_menuHandler.setMissed(_missed);
			}
			
			// Check for game-over.
			if (_missed >= Const.MAX_MISSED_WAVE)
			{
				dispatchEvent(new Event(Const.EVT_GAME_OVER));
			}
		}
		
		public function get gold():Number 
		{
			return _gold;
		}
		
		public function resetGold() : void
		{
			_gold = 0;
			if (_menuHandler != null)
			{
				_menuHandler.setGold(_wave);
			}
		}
		
		public function set gold(value:Number):void 
		{			
			_gold += value;
			if (_menuHandler != null)
			{
				_menuHandler.setGold(_gold);
			}
		}
		
		public function set goldFromMonster(value:Number):void 
		{
			if (value > 0)
			{
				SoundLoader.playCoin();
			}
			
			_gold += value;
			if (_menuHandler != null)
			{
				_menuHandler.setGold(_gold);
			}
		}
		
		public function set menuHandler(value:MenuUIHandler):void 
		{
			_menuHandler = value;
		}
		
		
	}
	
}