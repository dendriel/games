package src.units
{
	import src.language.GameLanguage;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class LightInfantryUnit extends GameUnit
	{
		public function LightInfantryUnit()
		{
			addChild(new LightInfantry01_bottomImg);
			_topImg = new LightInfantry01_topImg;
			super();
			
			_id = ConstUnit.LIGHT_INFANTRY01_ID;
			_name = GameLanguage.lang.light_infantry01_name;
			_desc = GameLanguage.lang.light_infantry01_desc;
			
			_soldiers_max = 50;
			_soldiers = 50;
			_soldiers_injuried = 0;
			_health_max = 15;
			_health = 20;
			_attack = 15;
			_defense = 14;
			_distance = 0;
			_move_time = Const.MOVE_TIME_2_DAYS;
			_recruit_cost = 7;
		}
	}
	
}