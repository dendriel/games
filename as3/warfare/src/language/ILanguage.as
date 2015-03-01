package src.language
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public interface ILanguage 
	{
		// Main menu.
		function get main_title() : String;
		function get single_player_button() : String;
		function get multiplayer_button() : String;
		function get credits_button() : String;
		
		// Display information screen.
		function get moveable_str() : String;
		function get blocked_str() : String;
		
		// Timer.
		function get of_the_year_str() : String;
		function get january_str() : String;
		function get february_str() : String;
		function get march_str() : String;
		function get april_str() : String;
		function get may_str() : String;
		function get jun_str() : String;
		function get july_str() : String;
		function get august_str() : String;
		function get september_str() : String;
		function get october_str() : String;
		function get november_str() : String;
		function get december_str() : String;
		
		// Units.
		function get levy_infantry01_name() : String;
		function get levy_infantry01_desc() : String;
		function get knight01_name() : String;
		function get knight01_desc() : String;
		function get light_infantry01_name() : String;
		function get light_infantry01_desc() : String;
		function get levy_archer01_name() : String;
		function get levy_archer01_desc() : String;
		
		// Buildings.
		function get village01_name() : String;
		function get village01_desc() : String;
		function get bridge01_name():String;
		function get bridge01_desc():String;
		
		// Tiles.
		function get grass01_name() : String;
		function get grass01_desc() : String;
		function get mountain01_name() : String;
		function get mountain01_desc() : String;
		function get river01_name():String;
		function get river01_desc():String;
		function get tree01_name():String;
		function get tree01_desc():String;
		function get road01_name():String;
		function get road01_desc():String;
	}
	
}