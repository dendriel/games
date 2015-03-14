package src.buildings.improvements
{
	import src.buildings.ImprovementStatus;
	import src.language.GameLanguage;
	import src.tiles.*;
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
			
			_tileable = true;
			_placeable_tiles = new Vector.<int>(ConstTile.GRASS_TILE_ID);
			
			_growth = ConstImprovement.FARM_GROWTH;
			_income = ConstImprovement.FARM_INCOME;
			_military = ConstImprovement.FARM_MILITARY;
			_defense_bonus = ConstImprovement.FARM_DEFENSE_BONUS;
			
			_icon = new FarmImprovementIconImage();
			
			addChild(new FarmBuildingImage());
		}
	}
}