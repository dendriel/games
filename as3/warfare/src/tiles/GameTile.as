package src.tiles
{
	import flash.display.MovieClip;
	import src.as3.media.Image;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * Tile attributes
	 */
	public class GameTile extends MovieClip
	{
		// Unique identifier.
		private var _uid:int;
		// Type identifier.
		private var _id:int;
		// Defense from the land.
		private var _def:Number;
		// If land is moveable;
		private var _moveable:Boolean;
		// Effort to move through this land.
		private var _moveEffort:int;
		
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
		
		public function get id():int 
		{
			return _id;
		}
		
		public function set id(value:int):void 
		{
			_id = value;
		}
		
		public function get def():Number 
		{
			return _def;
		}
		
		public function set def(value:Number):void 
		{
			_def = value;
		}
		
		public function get moveable():Boolean 
		{
			return _moveable;
		}
		
		public function set moveable(value:Boolean):void 
		{
			_moveable = value;
		}
		
		public function get moveEffort():int 
		{
			return _moveEffort;
		}
		
		public function set moveEffort(value:int):void 
		{
			_moveEffort = value;
		}
		
		public function get uid() : int
		{
			return _uid;
		}
	}
	
}