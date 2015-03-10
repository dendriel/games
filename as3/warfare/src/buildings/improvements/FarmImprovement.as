package src.buildings.improvements
{
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class FarmImprovement extends ImprovementStatus 
	{
		public function FarmImprovement()
		{
			_elemName = GameLanguage.lang.farm_name;
			_elemDesc = GameLanguage.lang.farm_desc;
			
			_growth = ConstImprovement.FARM_GROWTH;
			_income = ConstImprovement.FARM_INCOME;
			_military = ConstImprovement.FARM_MILITARY;
			_defense_bonus = ConstImprovement.FARM_DEFENSE_BONUS;
			
			_icon = new FarmIconImage();
			
			addChild(new FarmBuildingImage());
		}
	}
	
}