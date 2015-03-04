package src.units
{
	import flash.display.MovieClip;
	import src.language.GameLanguage;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class LevyInfantryUnit extends GameUnit 
	{
		public function LevyInfantryUnit()
		{
			_topImg = new MovieClip();
			super();
			
			_id = ConstUnit.LEVY_INFANTRY01_ID;
			_name = GameLanguage.lang.levy_infantry01_name;
			_desc = GameLanguage.lang.levy_infantry01_desc;
			
			_soldiers_max = 40;
			_soldiers = _soldiers_max;
			_soldiers_injuried = 0;
			_attack = 5;
			_defense = 0;
			_distance = 0;
			_move_time = Const.MOVE_TIME_3_DAYS;
			_recruit_cost = 1;
		}
	}
	
}

/*
			_id = ConstUnit.
			_name = GameLanguage.lang.
			_desc = GameLanguage.lang.
			
			_soldiers_max = ;
			_soldiers = ;
			_soldiers_injuried = ;
			_health_max = ;
			_health = ;
			_attack = ;
			_defense = ;
			_distance = ;
			_move_time = ;
			_recruit_cost = ;
			*/