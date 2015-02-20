package src.buildings
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameBuilding extends MovieClip
	{
		// Unique identifier.
		private var _uid:int;
		// Type identifier.
		private var _id:int;
		
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

		public function get id():int 
		{
			return _id;
		}
		
		public function set id(value:int):void 
		{
			_id = value;
		}
		
		public function get uid() : int
		{
			return _uid;
		}
	}
	
}