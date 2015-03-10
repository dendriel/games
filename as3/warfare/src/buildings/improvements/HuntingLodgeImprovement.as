package src.buildings.improvements
{
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class HuntingLodgeImprovement extends ImprovementStatus 
	{
		public function HuntingLodgeImprovement()
		{
			_elemName = GameLanguage.lang.hunting_lodge_name;
			_elemDesc = GameLanguage.lang.hunting_lodge_desc;
			
			_growth = ConstImprovement.HUNTING_LODGE_GROWTH;
			_income = ConstImprovement.HUNTING_LODGE_INCOME;
			_military = ConstImprovement.HUNTING_LODGE_MILITARY;
			_defense_bonus = ConstImprovement.HUNTING_LODGE_DEFENSE_BONUS;
			
			_icon = new FarmIconImage();
			
			addChild(new FarmBuildingImage());
		}
	}
	
}