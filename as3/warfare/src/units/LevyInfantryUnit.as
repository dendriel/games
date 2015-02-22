package src.units
{
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class LevyInfantryUnit extends GameUnit 
	{
		public function LevyInfantryUnit()
		{
			_id = ConstUnit.LEVY_INFANTRY01_ID;
			_name = GameLanguage.levy_infantry01_name;
			_desc = GameLanguage.levy_infantry01_desc;
			
			_soldiers_max = 20;
			_soldiers = 20;
			_soldiers_injuried = 0;
			_health_max = 10;
			_health = 10;
			_attack = 5;
			_defense = 0;
			_distance = 0;
			_move_time = 3;
			_recruit_cost = 1;
		}
	}
	
}

/*
			_soldiers_max = ;
			_soldiers_ready = ;
			_soldiers_injuried = ;
			_health_max = ;
			_health = ;
			_attack = ;
			_defense = ;
			_distance = ;
			_move_time = ;
			_recruit_cost = ;
			*/