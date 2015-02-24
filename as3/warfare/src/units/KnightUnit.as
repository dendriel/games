package src.units
{
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class KnightUnit extends GameUnit 
	{
		public function KnightUnit()
		{
			_id = ConstUnit.KNIGHT01_ID_ID;
			_name = GameLanguage.lang.knight01_name;
			_desc = GameLanguage.lang.knight01_desc;
			
			_soldiers_max = 30;
			_soldiers = 30;
			_soldiers_injuried = 0;
			_health_max = 20;
			_health = 20;
			_attack = 17;
			_defense = 15;
			_distance = 0;
			_move_time = 1;
			_recruit_cost = 25;
		}
	}
	
}