package src.buildings.improvements
{
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class StonecutterImprovement extends ImprovementStatus 
	{
		public function StonecutterImprovement()
		{
			_elemName = GameLanguage.lang.stonecutter_name;
			_elemDesc = GameLanguage.lang.stonecutter_desc;
			
			_growth = ConstImprovement.STONECUTTER_GROWTH;
			_income = ConstImprovement.STONECUTTER_INCOME;
			_military = ConstImprovement.STONECUTTER_MILITARY;
			_defense_bonus = ConstImprovement.STONECUTTER_DEFENSE_BONUS;
			
			_icon = new FarmIconImage();
			
			addChild(new FarmBuildingImage());
		}
	}
	
}