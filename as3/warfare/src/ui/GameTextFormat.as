package src.ui
{
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameTextFormat 
	{
		// Definitions
		private static var _displayFieldsFormat:TextFormat = new TextFormat;
		_displayFieldsFormat.size = 12;
		private static var _displayTitleFormat:TextFormat = new TextFormat;
		_displayTitleFormat.size = 14;
		_displayTitleFormat.bold = true;
		
		private static var _displayTimerFormat:TextFormat = new TextFormat;
		_displayTimerFormat.size = 16
		_displayTitleFormat.bold = true;
		
		private static const _displayFieldsColor:uint = 0xffffff;
		
		// Getters.
		public static function get displayFieldsFormat() : TextFormat { return _displayFieldsFormat; }
		public static function get displayTitleFormat() : TextFormat { return _displayTitleFormat; }
		public static function get displayTimerFormat() : TextFormat { return _displayTimerFormat; }
		public static function get displayFieldsColor() : uint { return _displayFieldsColor; }
		
		/**
		 * @param	px Text horizontal position.
		 * @param	py Text vertival position.
		 * @return A new textfield with the default game text formatting for display title.
		 */
		public static function newDisplayTextTitle(px:int = 0, py:int = 0) : TextField
		{
			var title:TextField = new TextField();
			
			title.defaultTextFormat = GameTextFormat.displayTitleFormat;
			title.textColor = GameTextFormat.displayFieldsColor;
			title.selectable = false;
			title.mouseEnabled = false;
			title.x = px;
			title.y = py;
			
			return title;
		}
		
		/**
		 * @param	px Text horizontal position.
		 * @param	py Text vertival position.
		 * @return A new textfield with the default game text formatting for display fields.
		 */
		public static function newDisplayTextField(px:int = 0, py:int = 0) : TextField
		{
			var field:TextField = new TextField();
			
			field.defaultTextFormat = GameTextFormat.displayFieldsFormat;
			field.textColor = GameTextFormat.displayFieldsColor;
			field.selectable = false;
			field.mouseEnabled = false;
			field.x = px;
			field.y = py;
			
			return field;
		}
	}
	
}