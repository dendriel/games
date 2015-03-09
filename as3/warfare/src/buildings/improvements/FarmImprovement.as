package src.buildings.improvements
{
	import src.buildings.ImprovementStatus;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class FarmImprovement extends ImprovementStatus 
	{
		public function FarmImprovement()
		{
			_growth = ConstImprovement.FARM_GROWTH;
			_income = ConstImprovement.FARM_INCOME;
			_military = ConstImprovement.FARM_MILITARY;
			_defense_bonus = ConstImprovement.FARM_DEFENSE_BONUS;
			
			addChild(new FarmBuildingImage());
		}
	}
	
}