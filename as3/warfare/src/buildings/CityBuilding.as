package src.buildings
{
	import flash.display.MovieClip;
	import src.language.GameLanguage;
	import src.buildings.improvements.ConstImprovement;
	import src.tiles.ConstTile;
	import src.as3.math.Calc;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CityBuilding extends GameBuilding 
	{
//##################################################################################################
// Static definitions.
		// Constants.
		public static const LEVEL_0:int = 1; // Village.
		public static const LEVEL_1:int = 2; // Small City.
		public static const LEVEL_2:int = 3; // Medium City.
		public static const LEVEL_3:int = 4; // Big City.
		
		// Base status.
		// Village status.
		static const VILLAGE_GROWTH:Number     = 2;
		static const VILLAGE_INCOME:int        = 5;
		static const VILLAGE_MILITARY:int      = 3;
		static const VILLAGE_ATTACK_BONUS:int  = 1;
		static const VILLAGE_DEFENSE_BONUS:int = 20;
		static const VILLAGE_POPULATION:int = 300;
		// Small city status.
		static const SMALL_CITY_GROWTH:Number     = 2;
		static const SMALL_CITY_INCOME:int        = 10;
		static const SMALL_CITY_MILITARY:int      = 5;
		static const SMALL_CITY_ATTACK_BONUS:int  = 3;
		static const SMALL_CITY_DEFENSE_BONUS:int = 25;
		static const SMALL_CITY_POPULATION:int = 2000;
		
		// Base buildings.
		public static const base_buildings:Array = new Array(
		// Improvement      , Needed city level.
		[ConstImprovement.FARM_ID, CityBuilding.LEVEL_0],
		[ConstImprovement.WOODCUTTER_ID, CityBuilding.LEVEL_0]
		);
		// Militar buildings.
		
//##################################################################################################

		// Attributes.
		private var _level:int;
		private var base_status:ImprovementStatus;
		private var view:MovieClip;
		private var improvements_list:Vector.<ImprovementStatus>;
		private var population:int;
		
		public function CityBuilding(level:int) : void
		{
			_level = level;
			
			_id = GameBuilding.CITY_ID;
			_name = CityBuilding.getName(_level);
			_desc = CityBuilding.getName(_level);
			
			_def = ConstTile.DEF_VALUE_NONE;
			_moveable =  true;
			_moveEffort = ConstTile.MOVEEFFORT_UNFAVORABLE;
			
			base_status = CityBuilding.getStatus(_level);
			view = CityBuilding.getView(_level);
			improvements_list = new Vector.<ImprovementStatus>;
			population = CityBuilding.getPopulation(_level);
			
			addChild(view);
		}
		
		/**
		 * Sum all improvements status in the city and return the final status for this city.
		 * @return
		 */
		public function getStatus() : ImprovementStatus
		{
			var final_status:ImprovementStatus = base_status.clone();
			
			for each (var improvement:ImprovementStatus in improvements_list)
			{
				final_status.merge(improvement);
			}
			
			return final_status;
		}
		
		/**
		 * Process city new state according with its base status and improvement status.
		 */
		public function updateStatus() : void
		{
			var curr_status:ImprovementStatus = getStatus();
			population += Calc.percentage(population, curr_status.growth);
		}
//##################################################################################################
// Static functions. Get default values for cities.
		public static function getName(level:int) : String
		{
			switch(level)
			{
				case CityBuilding.LEVEL_0:	return GameLanguage.lang.village_name;
				case CityBuilding.LEVEL_1:	return GameLanguage.lang.small_city_name;
				case CityBuilding.LEVEL_2:	return GameLanguage.lang.medium_city_name;
				case CityBuilding.LEVEL_3:	return GameLanguage.lang.big_city_name;
				default:
					trace("Invalid city level received. Returning default name.");
					return GameLanguage.lang.village_name;
			}
		}
		
		public static function getDesc(level:int) : String
		{
			switch(level)
			{
				case CityBuilding.LEVEL_0:	return GameLanguage.lang.village_desc;
				case CityBuilding.LEVEL_1:	return GameLanguage.lang.small_city_desc;
				case CityBuilding.LEVEL_2:	return GameLanguage.lang.medium_city_desc;
				case CityBuilding.LEVEL_3:	return GameLanguage.lang.big_city_desc;
				default:
					trace("Invalid city level received. Returning default description.");
					return GameLanguage.lang.village_desc;
			}
		}
		
		public static function getStatus(level:int) : ImprovementStatus
		{
			switch(level)
			{
				case CityBuilding.LEVEL_0:
					return new ImprovementStatus(
						CityBuilding.VILLAGE_GROWTH,
						CityBuilding.VILLAGE_INCOME,
						CityBuilding.VILLAGE_MILITARY,
						CityBuilding.VILLAGE_DEFENSE_BONUS);
						
				case CityBuilding.LEVEL_1:
					return new ImprovementStatus(
						CityBuilding.SMALL_CITY_GROWTH,
						CityBuilding.SMALL_CITY_INCOME,
						CityBuilding.SMALL_CITY_MILITARY,
						CityBuilding.SMALL_CITY_DEFENSE_BONUS);
						
				case CityBuilding.LEVEL_2:
				case CityBuilding.LEVEL_3:
				default:
					trace("Invalid city level received. Returning default status.");
					return new ImprovementStatus(
						CityBuilding.VILLAGE_GROWTH,
						CityBuilding.VILLAGE_INCOME,
						CityBuilding.VILLAGE_MILITARY,
						CityBuilding.VILLAGE_DEFENSE_BONUS);
			}
		}
		
		public static function getView(level:int) : MovieClip
		{
			var view:MovieClip = new CityBuildingImage();
			
			switch(level)
			{
				case CityBuilding.LEVEL_0:	view.gotoAndPlay("village");	break;
				case CityBuilding.LEVEL_1:	view.gotoAndPlay("small city");	break;
				case CityBuilding.LEVEL_2:	view.gotoAndPlay("medium city");break;
				case CityBuilding.LEVEL_3:	view.gotoAndPlay("big city");	break;
				default:
					trace("Invalid city level received. Returning default view.");
					view.gotoAndPlay("village");
					break;
				
			}
			return view;
		}
		
		public static function getPopulation(level:int) : int
		{
			switch (level)
			{
				case CityBuilding.LEVEL_0: return CityBuilding.VILLAGE_POPULATION;
				case CityBuilding.LEVEL_1: return CityBuilding.SMALL_CITY_POPULATION;
				case CityBuilding.LEVEL_2:
				case CityBuilding.LEVEL_3:
				default:
					trace("Invalid city level received. Returning default pupulation value.");
					return CityBuilding.VILLAGE_POPULATION;
			}
		}
	}
	
}