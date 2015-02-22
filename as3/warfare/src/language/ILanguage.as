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
		
		// Units.
		function get levy_infantry01_name() : String;
		function get levy_infantry01_desc() : String;
		
		// Buildings.
		function get village01_name() : String;
		function get village01_desc() : String;
	}
	
}