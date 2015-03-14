package src.buildings
{
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import src.IElementInfo;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class ImprovementStatus extends MovieClip implements IElementInfo
	{
		// Population growth.
		protected var _growth:Number;
		// Semianual cash.
		protected var _income:int;
		// Amount of militar units that support without cost.
		protected var _military:int;
		// Defense bonus for garrisoned soldiers.
		protected var _defense_bonus:int;
		
		// Tiles wich can hold the improvement.
		protected var _tileable:Boolean; // If the improvement is placed over a tile on the map.
		protected var _placeable_tiles:Vector.<int>;
		
		// Displaying icon.
		protected var _icon:BitmapData;
		
		// Element Info.
		protected var _elemType:int;
		protected var _elemName:String;
		protected var _elemDesc:String;
		
		
		public function ImprovementStatus(growth:Number = 0, income:int = 0, military:int = 0, defense_bonus:int = 0)
		{
			_growth = growth;
			_income = income;
			_military = military;
			_defense_bonus = defense_bonus;
		}
		
		public function clone() : ImprovementStatus
		{
			return new ImprovementStatus(growth, income, military, defense_bonus);
		}
		
		public function merge(status:ImprovementStatus) : void
		{
			growth += status.growth;
			income += status.income;
			military += status.military;
			defense_bonus += status.defense_bonus;
		}
		
		public function get growth():Number { return _growth;}
		public function set growth(value:Number):void {	_growth = value;}
		
		public function get income():int { return _income;}
		public function set income(value:int):void { _income = value;}
		
		public function get military():int {return _military;}
		public function set military(value:int):void {_military = value;}
		
		public function get defense_bonus():int {return _defense_bonus;}
		public function set defense_bonus(value:int):void {	_defense_bonus = value;	}
		
		public function get elemType():int 	{return _elemType;}
		public function get elemName():String {	return _elemName;}
		public function get elemDesc():String {	return _elemDesc;	}
		
		public function get icon():BitmapData { return _icon; }
		
		public function get tileable():Boolean 
		{
			return _tileable;
		}
		
		/**
		 * Check if the given tile ID can hold this improvement.
		 * @param	tile
		 * @return
		 */
		public function checkTilePlaceable(tile:int) : Boolean
		{
			return ( (_placeable_tiles.indexOf(tile) >= 0)? true : false);
		}
	}
	
}