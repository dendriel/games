package src.language
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameLanguage
	{
		// Default language is portuguese.
		public static var language:ILanguage = new PortugueseLanguage;
		
		/**
		 * @brief Change the game language.
		 * @param	value
		 */
		public static function load_language(value:ILanguage) : void
		{
			language = value;
		}
		
//##################################################################################################
// Main Menu.
		public static function get main_title():String {return language.main_title;}
		public static function get single_player_button():String {return language.single_player_button;}
		public static function get multiplayer_button():String {return language.multiplayer_button;}
		public static function get credits_button():String {return language.credits_button;}
		
//##################################################################################################
// Units.
		

//##################################################################################################
// Buildings.
		public static function get village01_name():String { return language.village01_name;}
		public static function get village01_desc():String { return language.village01_desc;}


//##################################################################################################
// Tiles.

	}
	
}