package src.units
{
	import flash.display.MovieClip;
	import src.language.GameLanguage;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class KnightUnit extends GameUnit 
	{
		public function KnightUnit()
		{
			_topImg = new MovieClip();
			super();
			
			_id = ConstUnit.KNIGHT01_ID_ID;
			_name = GameLanguage.lang.knight01_name;
			_desc = GameLanguage.lang.knight01_desc;
			
			_soldiers_max = 30;
			_soldiers = 30;
			_soldiers_injuried = 0;
			_attack = 17;
			_defense = 15;
			_distance = 0;
			_move_time = Const.MOVE_TIME_1_DAY;
			_recruit_cost = 25;
			
		}
	}
	
}