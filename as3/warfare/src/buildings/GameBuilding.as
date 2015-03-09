package src.buildings
{
	import flash.display.MovieClip;
	import src.GamePlayer;
	import src.IElementInfo;
	import src.tiles.IElementTileInfo;
	import src.ElementType;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameBuilding extends MovieClip implements IElementInfo, IElementTileInfo, IElementBuildingInfo
	{
//##################################################################################################
// Static Definitions.
		public static const CITY_ID:int = 1;

//##################################################################################################
		// Unique identifier.
		private var _uid:int;
		// Type identifier for map building.
		protected var _id:int;
		// Owner.
		private var _player:GamePlayer;
		
		// Element type identifier;
		private var _type:int = ElementType.BUILDING;
		protected var _name:String;
		protected var _desc:String;
		
		// Tile attributes.
		// Defense from the land.
		protected var _def:Number;
		// If land is moveable;
		protected var _moveable:Boolean;
		// Effort to move through this land.
		protected var _moveEffort:int;
		
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
		public function get elemDesc():String { return _desc; }
		
		public function get def():Number {return _def;}		
		public function get moveable():Boolean {return _moveable;}
		public function get moveEffort():int {return _moveEffort;}
		
		public function get player():GamePlayer {return _player;}
		public function set player(value:GamePlayer):void {_player = value;}
	}
	
}