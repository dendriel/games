package src.buildings
{
	import flash.display.MovieClip;
	import src.language.GameLanguage;
	import src.buildings.improvements.ConstImprovement;
	import src.tiles.ConstTile;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class CityBuilding extends GameBuilding 
	{
		// Constants.
		public static const LEVEL_0:int = 1; // Village.
		public static const LEVEL_1:int = 2; // Small City.
		public static const LEVEL_2:int = 3; // Medium City.
		public static const LEVEL_3:int = 4; // Big City.
		
		// Village status.
		static const VILLAGE_GROWTH:Number     = 2;
		static const VILLAGE_INCOME:int        = 5;
		static const VILLAGE_MILITARY:int      = 3;
		static const VILLAGE_ATTACK_BONUS:int  = 1;
		static const VILLAGE_DEFENSE_BONUS:int = 20;
		// Small city status.
		static const SMALL_CITY_GROWTH:Number     = 2;
		static const SMALL_CITY_INCOME:int        = 10;
		static const SMALL_CITY_MILITARY:int      = 5;
		static const SMALL_CITY_ATTACK_BONUS:int  = 3;
		static const SMALL_CITY_DEFENSE_BONUS:int = 25;
		
		// Base buildings.
		public static const base_buildings:Array = new Array(
		// Improvement      , Needed city level.
		[ConstImprovement.FARM_ID, CityBuilding.LEVEL_0]
		
		);
		// Militar buildings.
		
		// Attributes.
		private var _level:int;
		private var status:CityStatus;
		private var view:MovieClip;
		
		public function CityBuilding(level:int) : void
		{
			_level = level;
			
			_id = GameBuilding.CITY_ID;
			_name = CityBuilding.getName(_level);
			_desc = CityBuilding.getName(_level);
			
			_def = ConstTile.DEF_VALUE_NONE;
			_moveable =  true;
			_moveEffort = ConstTile.MOVEEFFORT_UNFAVORABLE;
			
			status = CityBuilding.getStatus(_level);
			view = CityBuilding.getView(_level);
			addChild(view);
		}
		
//##################################################################################################
// Static functions.
		public static function getName(level:int) : String
		{
			switch(level)
			{
				case CityBuilding.LEVEL_0:
					return GameLanguage.lang.village_name;
				case CityBuilding.LEVEL_1:
					return GameLanguage.lang.small_city_name;
				case CityBuilding.LEVEL_2:
					return GameLanguage.lang.medium_city_name;
				case CityBuilding.LEVEL_3:
					return GameLanguage.lang.big_city_name;
				default:
					trace("Invalid city level received. Returning default name.");
					return GameLanguage.lang.village_name;
			}
		}
		
		public static function getDesc(level:int) : String
		{
			switch(level)
			{
				case CityBuilding.LEVEL_0:
					return GameLanguage.lang.village_desc;
				case CityBuilding.LEVEL_1:
					return GameLanguage.lang.small_city_desc;
				case CityBuilding.LEVEL_2:
					return GameLanguage.lang.medium_city_desc;
				case CityBuilding.LEVEL_3:
					return GameLanguage.lang.big_city_desc;
				default:
					trace("Invalid city level received. Returning default description.");
					return GameLanguage.lang.village_desc;
			}
		}
		
		public static function getStatus(level:int) : CityStatus
		{
			switch(level)
			{
				case CityBuilding.LEVEL_0:
					return new CityStatus(
						CityBuilding.VILLAGE_GROWTH,
						CityBuilding.VILLAGE_INCOME,
						CityBuilding.VILLAGE_MILITARY,
						CityBuilding.VILLAGE_DEFENSE_BONUS);
						
				case CityBuilding.LEVEL_1:
					return new CityStatus(
						CityBuilding.SMALL_CITY_GROWTH,
						CityBuilding.SMALL_CITY_INCOME,
						CityBuilding.SMALL_CITY_MILITARY,
						CityBuilding.SMALL_CITY_DEFENSE_BONUS);
						
				case CityBuilding.LEVEL_2:
				case CityBuilding.LEVEL_3:
				default:
					trace("Invalid city level received. Returning default status.");
					return new CityStatus(
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
				case CityBuilding.LEVEL_0:
					view.gotoAndPlay("village");
					break;
				case CityBuilding.LEVEL_1:
					view.gotoAndPlay("small city");
					break;
				case CityBuilding.LEVEL_2:
					view.gotoAndPlay("medium city");
					break;
				case CityBuilding.LEVEL_3:
					view.gotoAndPlay("big city");
					break;
				default:
					trace("Invalid city level received. Returning default view.");
					view.gotoAndPlay("village");
					break;
				
			}
			return view;
		}
	}
	
}