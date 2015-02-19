package src.tiles
{
	import src.as3.media.Image;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * Tile attributes
	 */
	public class TileAttr 
	{
		// Unique ID.
		private var _id:int;
		// Defense from the land.
		private var _def:Number;
		// If land is moveable;
		private var _moveable:Boolean;
		// Effort to move through this land.
		private var _moveEffort:int;
		
		public function get image():Image 
		{
			return _image;
		}
		
		public function set image(value:Image):void 
		{
			_image = value;
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
	}
	
}