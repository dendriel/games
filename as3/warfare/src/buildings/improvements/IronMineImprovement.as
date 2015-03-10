package src.buildings.improvements
{
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class IronMineImprovement extends ImprovementStatus 
	{
		public function IronMineImprovement()
		{
			_elemName = GameLanguage.lang.iron_mine_name;
			_elemDesc = GameLanguage.lang.iron_mine_desc;
			
			_growth = ConstImprovement.IRON_MINE_GROWTH;
			_income = ConstImprovement.IRON_MINE_INCOME;
			_military = ConstImprovement.IRON_MINE_MILITARY;
			_defense_bonus = ConstImprovement.IRON_MINE_DEFENSE_BONUS;
			
			_icon = new FarmIconImage();
			
			addChild(new FarmBuildingImage());
		}
	}
	
}