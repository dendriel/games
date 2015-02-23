package src.language
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameLanguage
	{
		// Default language is portuguese.
		private static var _lang:ILanguage = new PortugueseLanguage;
		
		/**
		 * @brief Change the game language.
		 * @param	value
		 */
		public static function load_language(value:ILanguage) : void
		{
			_lang = value;
		}
		
		public static function get lang() : ILanguage
		{
			return _lang;
		}
	}
	
}