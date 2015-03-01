package src.language
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class BaseLanguage implements ILanguage
	{
		// Main Menu text.
		protected var _main_title:String;
		protected var _single_player_button:String;
		protected var _multiplayer_button:String;
		protected var _credits_button:String;
		
		// Display information screen.
		protected var _moveable_str:String;
		protected var _blocked_str:String;
		
		// Timer.
		protected var _of_the_year_str:String;
		protected var _january_str:String;
		protected var _february_str:String;
		protected var _march_str:String;
		protected var _april_str:String;
		protected var _may_str:String;
		protected var _jun_str:String;
		protected var _july_str:String;
		protected var _august_str:String;
		protected var _september_str:String;
		protected var _october_str:String;
		protected var _november_str:String;
		protected var _december_str:String;
		
		// Units text.
		protected var _levy_infantry01_name:String;
		protected var _levy_infantry01_desc:String;
		protected var _knight01_name:String;
		protected var _knight01_desc:String;
		protected var _light_infantry01_name:String;
		protected var _light_infantry01_desc:String;
		protected var _levy_archer01_name:String;
		protected var _levy_archer01_desc:String;
		
		// Buildings text.
		protected var _village01_name:String;
		protected var _village01_desc:String;
		protected var _bridge01_name:String;
		protected var _bridge01_desc:String;
		
		// Tiles text.
		protected var _grass01_name:String;
		protected var _grass01_desc:String;
		protected var _mountain01_name:String;
		protected var _mountain01_desc:String;
		protected var _river01_name:String;
		protected var _river01_desc:String;
		protected var _tree01_name:String;
		protected var _tree01_desc:String;
		protected var _road01_name:String;
		protected var _road01_desc:String;
		
		
//##################################################################################################
// Main Menu.
		public function get main_title():String {return _main_title;}		
		public function get single_player_button():String {return _single_player_button;}		
		public function get multiplayer_button():String {return _multiplayer_button;}		
		public function get credits_button():String { return _credits_button;}
		
//##################################################################################################
// Display information screen.
		public function get moveable_str():String { return _moveable_str; }
		public function get blocked_str():String { return _blocked_str; }
		
//##################################################################################################
// Timer.
		public function get of_the_year_str() : String {return _of_the_year_str;}
		public function get january_str() : String { return _january_str;}
		public function get february_str() : String { return _february_str;}
		public function get march_str() : String { return _march_str;}
		public function get april_str() : String { return _april_str;}
		public function get may_str() : String { return _may_str;}
		public function get jun_str() : String { return _jun_str;}
		public function get july_str() : String { return _july_str;}
		public function get august_str() : String { return _august_str;}
		public function get september_str() : String { return _september_str;}
		public function get october_str() : String { return _october_str;}
		public function get november_str() : String { return _november_str;}
		public function get december_str() : String { return _december_str;}

//##################################################################################################
// Units.
		public function get levy_infantry01_name():String { return _levy_infantry01_name;}
		public function get levy_infantry01_desc():String { return _levy_infantry01_desc; }
		public function get knight01_name():String { return _knight01_name; }
		public function get knight01_desc():String { return _knight01_desc; }
		public function get light_infantry01_name():String { return _light_infantry01_name; }
		public function get light_infantry01_desc():String { return _light_infantry01_desc; }
		public function get levy_archer01_name():String { return _levy_archer01_name;}
		public function get levy_archer01_desc():String { return _levy_archer01_desc; }
		

//##################################################################################################
// Buildings.
		public function get village01_name():String { return _village01_name;}
		public function get village01_desc():String { return _village01_desc; }
		public function get bridge01_name():String { return _bridge01_name; }
		public function get bridge01_desc():String { return _bridge01_desc; }


//##################################################################################################
// Tiles.
		public function get grass01_name():String { return _grass01_name; }
		public function get grass01_desc():String { return _grass01_desc; }
		public function get mountain01_name():String { return _mountain01_name; }
		public function get mountain01_desc():String { return _mountain01_desc; }
		public function get river01_name():String { return _river01_name; }
		public function get river01_desc():String { return _river01_desc; }
		public function get tree01_name():String { return _tree01_name; }
		public function get tree01_desc():String { return _tree01_desc; }
		public function get road01_name():String { return _road01_name; }
		public function get road01_desc():String { return _road01_desc; }
	}
	
}