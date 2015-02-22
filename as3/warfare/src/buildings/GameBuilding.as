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
		// Type identifier for map building.
		protected var _id:int;
		// Element type identifier;
		private var _type:int = ElementType.BUILDING;
		protected var _name:String;
		protected var _desc:String;
		
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
		public function get id():int {return _id;}
		
		public function get elemType():int {return _type;}
		public function get elemName():String { return _name; }
		public function get elemDesc():String {return _desc;}
	}
	
}