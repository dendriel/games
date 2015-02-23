package src.tiles
{
	import flash.display.MovieClip;
	import src.IElementInfo;
	import src.ElementType;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * Tile attributes
	 */
	public class GameTile extends MovieClip implements IElementInfo, IElementTileInfo
	{
		// Unique identifier.
		private var _uid:int;
		// Type identifier.
		protected var _id:int;
		
		// Element type identifier;
		private var _type:int = ElementType.TILE;
		protected var _name:String;
		protected var _desc:String;

		// Defense from the land.
		protected var _def:Number;
		// If land is moveable;
		protected var _moveable:Boolean;
		// Effort to move through this land.
		protected var _moveEffort:int;
		
//##################################################################################################
		// Unique tile identifier.
		private static var uid_count:int;
		
		/**
		 * @return An unique identifier for the tile.
		 */
		public static function generateUID() : int
		{
			var new_uid = uid_count;
			uid_count++;
			return new_uid;
		}
//##################################################################################################

		public function GameTile()
		{
			_uid = GameTile.generateUID();
		}
		
		public function get uid() : int { return _uid; }
		public function get id():int { return _id; }
		
		public function get elemType():int {return _type;}
		public function get elemName():String { return _name; }
		public function get elemDesc():String { return _desc; }
		
		public function get def():Number {return _def;}		
		public function get moveable():Boolean {return _moveable;}
		public function get moveEffort():int {return _moveEffort;}
		
	}
	
}