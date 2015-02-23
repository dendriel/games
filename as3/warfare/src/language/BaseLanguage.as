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
		
		// Units text.
		protected var _levy_infantry01_name:String;
		protected var _levy_infantry01_desc:String;
		
		// Buildings text.
		protected var _village01_name:String;
		protected var _village01_desc:String;
		
		// Tiles text.
		protected var _grass01_name:String;
		protected var _grass01_desc:String;
		protected var _mountain01_name:String;
		protected var _mountain01_desc:String;
		protected var _river01_name:String;
		protected var _river01_desc:String;
		protected var _tree01_name:String;
		protected var _tree01_desc:String;
		
		
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
// Units.
		public function get levy_infantry01_name():String { return _levy_infantry01_name;}
		public function get levy_infantry01_desc():String { return _levy_infantry01_desc;}
		

//##################################################################################################
// Buildings.
		public function get village01_name():String { return _village01_name;}
		public function get village01_desc():String { return _village01_desc;}


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
	}
	
}