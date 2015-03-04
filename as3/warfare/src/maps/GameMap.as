package src.maps
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	import src.Const;
	import src.IElementInfo;
	import src.tiles.*;
	import src.buildings.*;
	import src.ui.GameUnitDisplay;
	import src.units.*;
	import src.as3.math.Calc;
	import src.as3.math.graph.*;
	import src.GameBattleProcessor;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameMap extends MovieClip 
	{
		// Map properties.
		protected var _width_tiles:int;
		protected var height_tiles:int;
		
		// Layer 0.
		protected var tile_layer_map:Array;
		private var tile_layer_element:Array;
		private var tile_layer:MovieClip;
		
		// Layer 1.
		protected var building_layer_map:Array;
		private var building_layer_element:Array;
		private var building_layer:MovieClip;
		
		// Layer 2.
		protected var unit_layer_map:Array;
		private var unit_layer_element:Array;
		private var unit_layer:MovieClip;
		private var unit_actions:Array;
		
		// Layer 3.
		private var unit_top_layer:MovieClip;
		
		// Graph map.
		private var weightMap:Array;
		
		// Calculation.
		private var shortestPath:SPF;
		
		// Internal map state.
		private var unitOnFocus:GameUnit;
		
		protected function drawSelf() : void
		{
			shortestPath = new SPF();
			
			tile_layer_element = new Array(_width_tiles * height_tiles);
			building_layer_element = new Array(_width_tiles * height_tiles);
			unit_layer_element = new Array(_width_tiles * height_tiles);
			weightMap = new Array(_width_tiles * height_tiles);
			// Don't forget to update GameMapBuilder to add event listeners for these functions.
			unit_actions = new Array(handleUnitMove, handleUnitEngage, handleUnitBattle, handleUnitRemove);
			
			// Initialize weight map (with default values) and unit layer array.
			for (var i:int = 0; i < (_width_tiles * height_tiles); i++)
			{
				var p:Point = Calc.idx_to_coor(i, _width_tiles);
				unit_layer_element[i] = new GameUnitHolder( (p.x * ConstTile.TILE_W), (p.y * ConstTile.TILE_H) );
				weightMap[i] = new SPFNode(i);
			}
			
			// Draw landscape.
			if (tile_layer_map != null)
			{
				tile_layer = GameMapBuilder.drawLandscape(tile_layer_map, tile_layer_element, _width_tiles, height_tiles);
				// Add layer 0.
				addChild(tile_layer);
			}
			
			// Draw buildings.
			if (building_layer_map != null)
			{
				building_layer = GameMapBuilder.drawBuildings(building_layer_map, building_layer_element, _width_tiles, height_tiles);
				// Add layer 1.
				addChild(building_layer);
			}
			
			// Configure SPF.
			GameMapBuilder.buildWeightMap(weightMap, tile_layer_element, building_layer_element);
			GameMapBuilder.linkNeighborsOnMap(weightMap, _width_tiles, height_tiles);
			shortestPath.loadGraph(weightMap);
			
			// Draw units.
			if (unit_layer_map != null)
			{
				var layers:Array = GameMapBuilder.createUnits(unit_layer_map, unit_layer_element, _width_tiles, height_tiles, unit_actions, weightMap);
				unit_layer = layers[0];
				unit_top_layer = layers[1];
				
				// Add layer 3.
				addChild(unit_layer);
				addChild(unit_top_layer);
			}
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
			
			var tile:GameTile = tile_layer_element[idx];
			var building:GameBuilding = building_layer_element[idx];
			var unit:GameUnit = GameUnitHolder(unit_layer_element[idx]).units.concat().pop();
			
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
			return unit_layer_element[findUnitMapIndex(unit)];
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
		
		/**
		 * This callback receives the unit instead of its index so we can handle multiple units in the
		 * same node.
		 * @param	e
		 */
		private function handleUnitMove(e:UnitMoveEvent) : void
		{
			var holderFrom:GameUnitHolder = findUnitHolder(e.unit);
			var weightNodeFrom:SPFNode = findUnitWeightNode(e.unit);
			var holderTo:GameUnitHolder = unit_layer_element[e.toIdx];
			
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
		}
		
		/**
		 * Handle the start of a battle. Stop defender current actions.
		 * @param	e
		 */
		private function handleUnitEngage(e:UnitEngageEvent) : void
		{
			var expectedDefenderPosHolder:GameUnitHolder = GameUnitHolder(unit_layer_element[e.defenderExpectedPos]);
				
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
			GameMapBuilder.removeUnit(unit, unit_layer_element, unit_layer, unit_top_layer, index, weightMap);
		}

//##################################################################################################
// Public functions.
//##################################################################################################
		public function get width_tiles():int {	return _width_tiles;}
		
		/**
		 * @brief Get an element from the map.
		 * @param	idx Position of the Element.
		 */
		public function getElement(idx:int) : IElementInfo
		{
			// Search inside units layer.			
			if (unit_layer_element != null)
			{
				var units_list_temp:Vector.<GameUnit> = unit_layer_element[idx].units.concat();
				
				// TODO: return a list of all the units in the stack.
				if (units_list_temp.length > 0)
				{
					return units_list_temp.pop();
				}
			}
			
			// Search inside buildings layer.
			if (building_layer_element != null)
			{
				if (building_layer_element[idx] != null)
				{
					return building_layer_element[idx];
				}
			}
			
			// Search inside tiles layer.
			if (tile_layer_element != null)
			{
				if (tile_layer_element[idx] != null)
				{
					return tile_layer_element[idx];
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
			var holder:Vector.<GameUnit> = unit_layer_element[idx].units;
			
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
			return GameUnitHolder(unit_layer_element[idx]).unit;
		}
		
		public function moveUnit(from:int, to:int) : void
		{
			var unit:GameUnit;
			var enemy:GameUnit = null;
			
			unit = GameUnitHolder(unit_layer_element[from]).unit;
			if (unit == null)
			{
				trace("Nothing to move from here!");
				// There is no unit to move from this position.
				return;
			}
			
			// Check if can move to the given destination.
			if (posIsFree(to) != true)
			{
				// Destination is an enemy?
				enemy = GameUnitHolder(unit_layer_element[to]).unit;
				if (enemy == null)
				{
					trace("Can't move there.");
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
		}
		
		/**
		 * Define a unit on focus. 
		 * @param	unit The unit that will be on focus. If null is passed, remove the focus from
		 * the current unit.
		 */
		public function setUnitOnFocus(unit:GameUnit) : void
		{
			// Remove focus from previous unit (if exist).
			if (unitOnFocus != null)
			{
				unitOnFocus.focusSign = false;
				unitOnFocus = null;
			}
			
			if (unit != null)
			{
				unitOnFocus = unit;
				unitOnFocus.focusSign = true;
			}
		}
		
		/**
		 * Create and add a unit of 'type' on the map with 'posx' and 'posy'.
		 * @param	type
		 * @param	posx
		 * @param	posy
		 * @return true
		 */
		public function spawnUnit(type:int, posx:int, posy:int) : Boolean
		{
			var index:int = Calc.coor_to_idx(posx, posy, _width_tiles);
			// Create and add unit in the map.
			GameMapBuilder.spawnUnit(type, unit_actions, index, _width_tiles, unit_layer_element, unit_layer, unit_top_layer, weightMap);
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