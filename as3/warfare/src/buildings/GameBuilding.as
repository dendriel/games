package src.buildings
{
	import flash.display.MovieClip;
	import src.IElementInfo;
	import src.ElementType;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameBuilding extends MovieClip implements IElementInfo
	{
		// Unique identifier.
		private var _uid:int;
		// Type identifier.
		private var _id:int;
		// Element type identifier;
		private var _type:int = ElementType.BUILDING;
		private var _name:String;
		private var _desc:String;
		
//##################################################################################################
		// Unique building identifier.
		private static var uid_count:int;
		
		/**
		 * @return An unique identifier for the building.
		 */
		public static function generateUID() : int
		{
			var new_uid = uid_count;
			uid_count++;
			return new_uid;
		}
//##################################################################################################

		public function GameBuilding()
		{
			_uid = GameBuilding.generateUID();
		}
		
		public function get uid() : int {return _uid;}
		public function get elemType():int {return _type;}
		
		public function set id(value:int):void {_id = value;}
		public function get id():int {return _id;}
		
		public function set elemName(value:String):void {_name = value;}
		public function get elemName():String { return _name; }

		public function set elemDesc(value:String):void {_desc = value;}
		public function get elemDesc():String {return _desc;}
	}
	
}