package src
{
	import src.units.GameUnit;
	import src.buildings.GameBuilding;
	import src.tiles.GameTileset;
	import src.as3.math.Calc;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GamePlayer 
	{
		private var _nick:String;
		private var _id:int;
		private var _units_map:Array;
		private var units_list:Vector.<GameUnit>
		private var _buildings_map:Array;
		private var buildings_list:Vector.<GameBuilding>;
		private var _gold:int;
		// Tileset index offset.
		private var _indexOffset:int;

//##################################################################################################
// Factory:
		static const player_max:int = 8;
		static var player_counter:int = 1; 
		
		public static function newPlayer(nick:String, gold:int=0) : GamePlayer
		{
			if (player_counter > player_max)
			{
				return null;
			}
			
			var id:int = player_counter;
			player_counter++;
			
			return new GamePlayer(nick, gold, id);
		}

//##################################################################################################
// GamePlayer:
		public function GamePlayer(nick:String, gold:int, id:int)
		{
			units_list = new Vector.<GameUnit>;
			buildings_list = new Vector.<GameBuilding>;
			_nick = nick
			_gold = gold;
			_id = id;
		}
		
		public function get nick():String {	return _nick;}
		
		public function get gold():int {return _gold;}
		
		public function get id():int { return _id; }
		
		public function get indexOffset():int {return _indexOffset;}
		public function set indexOffset(value:int):void {_indexOffset = value;}
		
		public function get units_map():Array {return _units_map;}
		public function set units_map(value:Array):void {_units_map = value;}
		
		public function get buildings_map():Array {	return _buildings_map;}
		public function set buildings_map(value:Array):void {_buildings_map = value;}
		
		public function get units():Vector.<GameUnit> {return units_list;}
		public function set units(value:Vector.<GameUnit>):void {units_list = value;}
		
		public function get buildings():Vector.<GameBuilding> {return buildings_list;}
		public function set buildings(value:Vector.<GameBuilding>):void {buildings_list = value;}
		
	}
	
}