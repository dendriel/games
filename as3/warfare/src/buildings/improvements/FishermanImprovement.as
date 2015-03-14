package src.buildings.improvements
{
	import flash.display.Bitmap;
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class FishermanImprovement extends ImprovementStatus 
	{
		public function FishermanImprovement()
		{
			_elemName = GameLanguage.lang.fisherman_name;
			_elemDesc = GameLanguage.lang.fisherman_desc;
			
			_tileable = false;
			
			_growth = ConstImprovement.FISHERMAN_GROWTH;
			_income = ConstImprovement.FISHERMAN_INCOME;
			_military = ConstImprovement.FISHERMAN_MILITARY;
			_defense_bonus = ConstImprovement.FISHERMAN_DEFENSE_BONUS;
			
			_icon = new FishermanImprovementIconImage();
			
			addChild(new Bitmap(new FishermanBuildingImage()));
		}
	}
	
}