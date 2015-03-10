package src.maps
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import src.tiles.*;
	import src.buildings.*;
	import src.units.*;
	import src.as3.math.Calc;
	import src.as3.math.graph.*;
	import src.*;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameMap extends MovieClip 
	{
		// Map properties.
		protected var _width_tiles:int;
		protected var height_tiles:int;
		protected var tileset:GameTileset;
		
		// Tile layer.
		protected var tile_layer_map:Array;
		private var tiles_list:Array;
		private var tile_layer:MovieClip;
		
		// Building layer.
		private var buildings_list:Array;
		private var building_layer:MovieClip;
		
		// Path layer.
		private var path_layer:MovieClip;
		
		// Unit layer.
		private var unit_layers:Array	// [0] bottom layer; [1] top layer.
		private var units_list:Array;
		private var unit_actions:Array;
		
		// Graph map.
		private var weightMap:Array;
		
		// Calculation.
		private var shortestPath:SPF;
		
		// Internal map state.
		private var unitOnFocus:GameUnit;
		private var _timer:GameTimer;					// Date/time object handler.
		
		// Players.
		protected var players_list:Array;
		
		protected function drawSelf() : void
		{
			var player:GamePlayer;
			var i:int;
			var map_lenght:int = _width_tiles * height_tiles
			
			path_layer = new MovieClip();
			shortestPath = new SPF();
			weightMap = new Array(map_lenght);
			units_list = new Array(map_lenght);
			
			// Initialize weight map (with default values) and unit layer array.
			for (i = 0; i < map_lenght; i++)
			{
				var pos:Point = Calc.idx_to_pixel(i, _width_tiles, ConstTile.TILE_W);
				units_list[i] = new GameUnitHolder(pos);
				weightMap[i] = new SPFNode(i);
			}

			trace("Draw landscape.");
			tiles_list = new Array(map_lenght);
			if (tile_layer_map != null)
			{
				tile_layer = GameMapBuilder.drawLandscape(tile_layer_map, tiles_list, _width_tiles, height_tiles, tileset);
				// Add layer 0.
				addChild(tile_layer);
			}
			
			trace("Draw buildings.");;
			building_layer = new MovieClip();
			buildings_list = new Array(map_lenght);
			for each (player in players_list)
			{
				if (player.buildings_map == null)
				{
					continue;
				}
				
				GameMapBuilder.createBuildings(player, buildings_list, _width_tiles, tileset, building_layer);
			}
			addChild(building_layer);
			
			// Configure SPF.
			GameMapBuilder.buildWeightMap(weightMap, tiles_list, buildings_list);
			GameMapBuilder.linkNeighborsOnMap(weightMap, _width_tiles, height_tiles);
			shortestPath.loadGraph(weightMap);
			
			// Draw units.
			trace("Draw units.");
			unit_layers = new Array(new MovieClip, new MovieClip);
			// Don't forget to update GameMapBuilder to add event listeners for these functions.
			unit_actions = new Array(handleUnitMove,
									handleUnitEngage,
									handleUnitBattle,
									handleUnitRemove);
			for each (player in players_list)
			{
				if (player.units_map == null)
				{
					continue;
				}
				
				GameMapBuilder.createUnits(player, units_list, _width_tiles, unit_actions, weightMap,  unit_layers);
			}
			addChild(unit_layers[0]);
			addChild(unit_layers[1]);
			
			// Create timer.
			_timer = new GameTimer();
			_timer.addEventListener(GameTimerSemesterEvent.EVT_TIMER_SEMESTER, handleTimerSemester, false, 0, true);
		}
		
		public function playMap() : void
		{
			_timer.start();
		}

//##################################################################################################
// Private functions.
//##################################################################################################		
		/**
		 * @param	px Element horizontal position.
		 * @param	py Element vertical position.
		 * @return  The element index in Matrix.
		 */
		private function getElementIdx(px:int, py:int) : int
		{
			var tilex = Calc.pixel_to_tile(px, ConstTile.TILE_W);
			var tiley = Calc.pixel_to_tile(py, ConstTile.TILE_H);
			
			return Calc.coor_to_idx(tilex, tiley, width_tiles);
		}
		
		/**
		 * Check if the given position in the map is moveable.
		 * @param	idx
		 * @return true if can move there; false otherwise.
		 */
		private function posIsFree(idx:int) : Boolean
		{
			var moveable = true;
			
			var tile:GameTile = tiles_list[idx];
			var building:GameBuilding = buildings_list[idx];
			var unit:GameUnit = GameUnitHolder(units_list[idx]).units.concat().pop();
			
			// If the tile isn't moveable.
			if (tile.moveable != true)
			{
				moveable = false;
			}
			
			if ( (building != null) && (building.moveable == true) )
			{
				moveable = true;
			}
			
			if (unit != null)
			{
				moveable = false;
			}
			
			return moveable;
		}
		
		/**
		 * Find out the index in the map that the unit is contained.
		 * @param	unit
		 * @return The index of the holder.
		 */
		private function findUnitMapIndex(unit:GameUnit) : int
		{
			return Calc.pixel_to_idx(unit.x, unit.y, ConstTile.TILE_W, _width_tiles);
		}
		
		/**
		 * Find out the holder of the unit
		 * @param	unit
		 * @return The holder itself.
		 */
		private function findUnitHolder(unit:GameUnit) : GameUnitHolder
		{
			return units_list[findUnitMapIndex(unit)];
		}
		
		/**
		 * Find out the SPFNode that the unit registered it weight.
		 * @param	unit
		 * @return The SPFNode that have the unit weight.
		 */
		private function findUnitWeightNode(unit:GameUnit) : SPFNode
		{
			return weightMap[findUnitMapIndex(unit)];
		}
		
		private function handleTimerSemester(e:GameTimerSemesterEvent) : void
		{
			updatePlayerStatus();
		}
		
		private function updatePlayerStatus() : void
		{
			for (var i in players_list)
			{
				var player:GamePlayer = players_list[i];
				var profits:int = 0;
				
				// Update cities. // Maybe change buildings from vector to array.
				for (var j in player.buildings)
				{
					var building:GameBuilding = player.buildings[j];
					if (building.id != GameBuilding.CITY_ID)
					{
						continue;
					}
					// Process city. TODO: create a new function.
					var city:CityBuilding = CityBuilding(building);
					var status:ImprovementStatus = city.getStatus();
					player.gold += status.income;
					city.updateStatus();
				}				
			}
			
			dispatchEvent(new GameMapUpdatePlayerEvent());
		}
		
		/**
		 * This callback receives the unit instead of its index so we can handle multiple units in the
		 * same node.
		 * @param	e
		 */
		private function handleUnitMove(e:UnitMoveEvent) : void
		{
			var holderFrom:GameUnitHolder = findUnitHolder(e.unit);
			var weightNodeFrom:SPFNode = findUnitWeightNode(e.unit);
			var holderTo:GameUnitHolder = units_list[e.toIdx];
			
			// Check if destination still moveable.
			if (posIsFree(e.toIdx) != true)
			{
				e.unit.stopMove();
				return;
			}
			
			// Remove unit from the origin holder.
			holderFrom.removeUnit(e.unit);
			// Remove weight from the unit.
			weightNodeFrom.weight -= Const.UNIT_WEIGHT;
			
			// Insert unit into the destination holder.
			holderTo.addUnit(e.unit);
			// Add unit's weight in the layer.
			SPFNode(weightMap[e.toIdx]).weight += Const.UNIT_WEIGHT;
			
			// Schedule next movement.
			e.unit.scheduleMove();
			
			if ( (unitOnFocus != null) && (unitOnFocus.uid == e.unit.uid) )
			{
				drawUnitPath(e.unit);
			}
		}
		
		/**
		 * Handle the start of a battle. Stop defender current actions.
		 * @param	e
		 */
		private function handleUnitEngage(e:UnitEngageEvent) : void
		{
			var expectedDefenderPosHolder:GameUnitHolder = GameUnitHolder(units_list[e.defenderExpectedPos]);
				
			// Check if defender still in the expected position.
			if (expectedDefenderPosHolder.containsUnit(e.defender) != true)
			{
				trace("Defender left the expected position");
				e.attacker.stopAttack();
				return;
			}
			if (e.defender.engage() != true)
			{
				trace("Unit is already in a fight.");
				e.attacker.stopAttack();
				return;
			}
			// The unit that took the initiative.
			e.attacker.scheduleAttack(GameUnit.BATTLE_ROLE_ATTACKER);
		}
		
		/**
		 * Process unit battle.
		 * @param	e
		 */
		private function handleUnitBattle(e:UnitBattleEvent) : void
		{
			// Initiative unit is the attacker.
			if (e.nextRole == GameUnit.BATTLE_ROLE_DEFENDER)
			{
				GameBattleProcessor.processBattle(e.attacker, e.defender);
			}
			// Initiative unit is the defender.
			else
			{
				GameBattleProcessor.processBattle(e.defender, e.attacker );
			}
			
			// Check if defender has fallen.
			if (e.defender.soldiers == 0)
			{
				removeUnit(e.defender);
				e.attacker.stopAttack();
			}
			// Check if attacker has fallen.
			else if (e.attacker.soldiers == 0)
			{
				removeUnit(e.attacker);
				e.defender.stopAttack();
			}
			// If no unit has lost the battle, schedule the next batle. Switch the attacker for the
			// next battle.
			else
			{
				e.attacker.scheduleAttack(e.nextRole);
			}
		}
		
		/**
		 * Remove unit from all references.
		 * @param	e
		 */
		private function handleUnitRemove(e:UnitRemoveEvent) : void
		{
			var unit:GameUnit = e.unit;
			var index:int = Calc.pixel_to_idx(unit.x, unit.y, ConstTile.TILE_W, _width_tiles);
			GameMapBuilder.removeUnit(unit, units_list, unit_layers, index, weightMap);
		}
		
		private function drawUnitPath(unit:GameUnit) : void
		{
			var path:Vector.<SPFNode>;
			var node:SPFNode;
			var mark:Bitmap;
			var pos:Point;
			
			// Remove old reference, if needed.
			if ( (path_layer != null) && (contains(path_layer)) )
			{
				removeChild(path_layer);
				path_layer = null;
			}
			
			if ( (unit == null) ||
				( (unit != null) && ( (unit.move_to == null) || (unit.engaged == true) ) )
				)
			{
				return;
			}
			
			// Get a clear movieclip.
			path_layer = new MovieClip();
			
			node = unit.move_to;
			path = unit.move_path;
			
			// First node.
			// If is the final destination, add a different mark.
			mark = (path != null)? new Bitmap(new PathMarkImage()) : new Bitmap(new PathDestinationMarkImage());
			pos = Calc.idx_to_pixel(node.uid, _width_tiles, ConstTile.TILE_W);
			mark.x = pos.x;
			mark.y = pos.y;
			path_layer.addChild(mark);
			
			// Subsequent nodes.
			while ( (path != null) && (path.length != 0) )
			{
				node = path.pop();
				// If is the final destination, add a different mark.
				mark = (path.length > 0)? new Bitmap(new PathMarkImage()) : new Bitmap(new PathDestinationMarkImage());
				pos = Calc.idx_to_pixel(node.uid, _width_tiles, ConstTile.TILE_W);
				mark.x = pos.x;
				mark.y = pos.y;
				path_layer.addChild(mark);
			}
			
			// Above tile and building layer.
			addChildAt(path_layer, 2);
		}

//##################################################################################################
// Public functions.
//##################################################################################################
		public function get width_tiles():int {	return _width_tiles;}
		
		public function get players():Array 
		{
			return players_list;
		}
		
		public function set players(value:Array):void 
		{
			players_list = value;
		}
		
		public function get timer():GameTimer 
		{
			return _timer;
		}
		
		/**
		 * @brief Get an element from the map.
		 * @param	idx Position of the Element.
		 */
		public function getElement(idx:int) : IElementInfo
		{
			// Search inside units layer.			
			if (units_list != null)
			{
				var units_list_temp:Vector.<GameUnit> = units_list[idx].units.concat();
				
				// TODO: return a list of all the units in the stack.
				if (units_list_temp.length > 0)
				{
					return units_list_temp.pop();
				}
			}
			
			// Search inside buildings layer.
			if (buildings_list != null)
			{
				if (buildings_list[idx] != null)
				{
					return buildings_list[idx];
				}
			}
			
			// Search inside tiles layer.
			if (tiles_list != null)
			{
				if (tiles_list[idx] != null)
				{
					return tiles_list[idx];
				}
			}
			
			// Should not get here!
			return null;
		}
		
		/**
		 * Find unit by its uid.
		 * @param	idx
		 * @return The unit, if found; null otherwise.
		 */
		public function getUnit(idx:int, uid:int=0) : GameUnit
		{
			var holder:Vector.<GameUnit> = units_list[idx].units;
			
			for each (var unit:GameUnit in holder)
			{
				if (unit.uid == uid)
				{
					return unit;
				}
			}
			
			trace("Nothing to move from here!");
			return null;
		}
		
		/**
		 * @param	idx
		 * @return The unit, if found; null otherwise.
		 */
		public function getUnitAt(idx:int) : GameUnit
		{
			return GameUnitHolder(units_list[idx]).unit;
		}
		
		public function moveUnit(player:GamePlayer, from:int, to:int) : void
		{
			var unit:GameUnit;
			var enemy:GameUnit = null;
			
			unit = GameUnitHolder(units_list[from]).unit;
			if (unit == null)
			{
				trace("Nothing to move from here!");
				// There is no unit to move from this position.
				return;
			}
			
			if (player.id != unit.player.id)
			{
				trace("Can't move an unit that isn't yours.");
				return;
			}
			
			// Check if can move to the given destination.
			if (posIsFree(to) != true)
			{
				// Destination is an enemy?
				enemy = GameUnitHolder(units_list[to]).unit;
				if (enemy == null)
				{
					// The path is blocked by nature.
					trace("Can't move there.");
					SoundLoader.playUnitError01();
					return;
				}
				
				// Check if destination unit is friend or foe.
				if (enemy.player.id == unit.player.id)
				{
					trace("Can't attack a friendly unit.");
					SoundLoader.playUnitError01();
					return;
				}
			}
			
			// Find out the shortest path.
			var path:Vector.<SPFNode> = shortestPath.findSPF(from, to);
			// Remove first node, that is the own unit node.
			path.pop();
			
			if (enemy != null)
			{
				unit.startAttack(path, enemy);
			}
			else
			{
				unit.startMove(path);
			}
			
			if ( (unitOnFocus != null) && (unitOnFocus.uid == unit.uid) )
			{
				drawUnitPath(unit);
			}
		}
		
		/**
		 * Define a unit on focus. 
		 * @param	unit The unit that will be on focus. If null is passed, remove the focus from
		 * the current unit.
		 */
		public function setUnitOnFocus(unit:GameUnit) : void
		{
			if ( (unitOnFocus != null) && (unit != null) && (unit.uid == unitOnFocus.uid) )
			{
				// If unit already in focus.
				return;
			}
			
			if (unitOnFocus != null)
			{
				unitOnFocus.focusSign = false;
				unitOnFocus = null;
				drawUnitPath(null);
			}
			
			if (unit != null)
			{
				unitOnFocus = unit;
				unitOnFocus.focusSign = true;
				drawUnitPath(unit);
			}
		}
		
		/**
		 * Create and add a unit of 'type' on the map with 'posx' and 'posy'.
		 * @param	type
		 * @param	posx
		 * @param	posy
		 * @return true
		 */
		public function spawnUnit(player:GamePlayer, type:int, posx:int, posy:int) : Boolean
		{
			var index:int = Calc.coor_to_idx(posx, posy, _width_tiles);
			// Create and add unit in the map.
			GameMapBuilder.spawnUnit(type, unit_actions, index, _width_tiles, units_list, unit_layers, weightMap, player);
			return true;
		}
		
		/**
		 * Stops and remove the given unit.
		 * @param	unit
		 */
		public function removeUnit(unit:GameUnit) : void
		{
			trace("removing unit!");
			unit.removeSelf();
		}
	}
	
}