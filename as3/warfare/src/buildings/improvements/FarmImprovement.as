package src.buildings.improvements
{
	import src.buildings.CityStatus;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class FarmImprovement extends CityStatus 
	{
		public function FarmImprovement()
		{
			_growth = ConstImprovement.FARM_GROWTH;
			_income = ConstImprovement.FARM_INCOME;
			_military = ConstImprovement.FARM_MILITARY;
			_attack_bonus = ConstImprovement.FARM_ATTACK_BONUS;
			_defense_bonus = ConstImprovement.FARM_DEFENSE_BONUS;
		}
	}
	
}