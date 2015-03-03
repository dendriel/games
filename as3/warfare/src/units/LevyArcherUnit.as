package src.units
{
	import src.language.GameLanguage;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class LevyArcherUnit extends GameUnit 
	{
		public function LevyArcherUnit()
		{
			addChild(new LevyArcher01_bottomImg);
			_topImg = new LevyArcher01_topImg;
			super();
			
			_id = ConstUnit.LEVY_ARCHER01_ID;
			_name = GameLanguage.lang.levy_archer01_name;
			_desc = GameLanguage.lang.levy_archer01_desc;
			
			_soldiers_max = 40;
			_soldiers = _soldiers_max;
			_soldiers_injuried = 0;
			_health_max = 10;
			_health = 10;
			_attack = 3;
			_defense = 0;
			_distance = 2;
			_move_time = Const.MOVE_TIME_2_DAYS;
			_recruit_cost = 1;
		}
		
	}
	
}