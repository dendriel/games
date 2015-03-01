package src.units
{
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class LightInfantryUnit extends GameUnit
	{
		public function LightInfantryUnit()
		{
			_id = ConstUnit.LIGHT_INFANTRY01_ID;
			_name = GameLanguage.lang.light_infantry01_name;
			_desc = GameLanguage.lang.light_infantry01_desc;
			
			_soldiers_max = 50;
			_soldiers = 50;
			_soldiers_injuried = 0;
			_health_max = 15;
			_health = 15;
			_attack = 15;
			_defense = 10;
			_distance = 0;
			_move_time = 2;
			_recruit_cost = 7;
			
			addChild(new LightInfantry01_bottomImg);
			_topImg = new LightInfantry01_topImg;
		}
	}
	
}