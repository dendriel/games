package src.buildings.improvements
{
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class DocksImprovement extends ImprovementStatus 
	{
		public function DocksImprovement()
		{
			_elemName = GameLanguage.lang.docks_name;
			_elemDesc = GameLanguage.lang.docks_desc;
			
			_growth = ConstImprovement.DOCKS_LODGE_GROWTH;
			_income = ConstImprovement.DOCKS_LODGE_INCOME;
			_military = ConstImprovement.DOCKS_LODGE_MILITARY;
			_defense_bonus = ConstImprovement.DOCKS_LODGE_DEFENSE_BONUS;
			
			_icon = new FarmIconImage();
			
			addChild(new FarmBuildingImage());
		}
	}
	
}