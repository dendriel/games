package src.language
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class BaseLanguage implements ILanguage
	{
		// Main Menu Text.
		protected var _main_title:String;
		protected var _single_player_button:String;
		protected var _multiplayer_button:String;
		protected var _credits_button:String;
		
		// Units text.
		protected var _levy_infantry01_name:String;
		protected var _levy_infantry01_desc:String;
		
		// Buildings Text.
		protected var _village01_name:String;
		protected var _village01_desc:String;
		
		
//##################################################################################################
// Main Menu.
		public function get main_title():String {return _main_title;}		
		public function get single_player_button():String {return _single_player_button;}		
		public function get multiplayer_button():String {return _multiplayer_button;}		
		public function get credits_button():String { return _credits_button;}
		
//##################################################################################################
// Units.
		public function get levy_infantry01_name():String { return _levy_infantry01_name;}
		public function get levy_infantry01_desc():String { return _levy_infantry01_desc;}
		

//##################################################################################################
// Buildings.
		public function get village01_name():String { return _village01_name;}
		public function get village01_desc():String { return _village01_desc;}


//##################################################################################################
// Tiles.
	}
	
}