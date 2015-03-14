package src.buildings.improvements
{
	import flash.display.Bitmap;
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class WoodcutterImprovement extends ImprovementStatus 
	{
		public function WoodcutterImprovement()
		{
			_elemName = GameLanguage.lang.woodcutter_name;
			_elemDesc = GameLanguage.lang.woodcutter_desc;
			
			_tileable = false;
			
			_growth = ConstImprovement.WOODCUTTER_GROWTH;
			_income = ConstImprovement.WOODCUTTER_INCOME;
			_military = ConstImprovement.WOODCUTTER_MILITARY;
			_defense_bonus = ConstImprovement.WOODCUTTER_DEFENSE_BONUS;
			
			_icon = new WoodcutterImprovementIconImage();
			
			addChild(new Bitmap(new WoodcutterBuildingImage() ) );
		}
	}
	
}