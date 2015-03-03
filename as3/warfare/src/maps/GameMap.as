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
			unit_actions = new Array(handleUnitMove, handleUnitEngage, handleUnitBattle);
			
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
		
		private function handleUnitMove(e:UnitMoveEvent) : void
		{ 
			var holderFrom:Vector.<GameUnit> = unit_layer_element[e.fromIdx].units;
			var holderTo:GameUnitHolder = unit_layer_element[e.toIdx];
			
			// Check if destination still moveable.
			if (posIsFree(e.toIdx) != true)
			{
				e.unit.stopMove();
				return;
			}
			
			// Remove unit from the origin holder.
			holderFrom.splice(holderFrom.indexOf(e.unit), 1);
			// Remove weight from the unit.
			SPFNode(weightMap[e.fromIdx]).weight -= Const.UNIT_WEIGHT;
			
			// Insert unit into the destination holder.
			holderTo.addUnit(e.unit);
			// Add unit's weight in the layer.
			SPFNode(weightMap[e.toIdx]).weight += Const.UNIT_WEIGHT;
		}
		
		/**
		 * Handle the start of a battle. Stop defender current actions.
		 * @param	e
		 */
		private function handleUnitEngage(e:UnitEngageEvent) : void
		{
			var p:Point = Calc.coorToTile(e.defender.x, e.defender.y, ConstTile.TILE_W, ConstTile.TILE_H);
				
			// Check if defender still in the expected position.
			if (e.defenderPos != Calc.coor_to_idx(p.x, p.y, _width_tiles) )
			{
				e.attacker.stopAttack();
				return;
			}
			e.defender.engage(GameUnit.BATTLE_ROLE_DEFENDER);
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
			
			if (e.defender.soldiers == 0)
			{
				removeUnit(e.defender);
				e.attacker.stopAttack();
			}
			else if (e.attacker.soldiers == 0)
			{
				removeUnit(e.attacker);
				e.defender.stopAttack();
			}
			else
			{
				e.attacker.scheduleAttack(e.nextRole);
			}
		}

//##################################################################################################
// Public functions.
//##################################################################################################
		public function get width_tiles():int 
		{
			return _width_tiles;
		}
		
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
		 * Get a holder with all units from the given position.
		 * @param	idx
		 * @return The holder of units, if there is any unit on the position; null if there is no unit
		 * at the given position.
		 */
		public function getAllUnits(idx:int) : Vector.<GameUnit>
		{
			var holder:Vector.<GameUnit> = unit_layer_element[idx].units;
			
			if (holder.length > 0)
			{
				return holder;
			}
			else
			{
				return null;
			}
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
		 * Find unit by its uid.
		 * @param	idx
		 * @return The unit, if found; null otherwise.
		 */
		public function getUnitAt(idx:int) : GameUnit
		{
			return GameUnitHolder(unit_layer_element[idx]).unit;
		}
		
		public function moveUnit(unit:GameUnit, from:int, to:int) : void
		{
			// If is going to attack an unit.
			var moveAttack:Boolean = false;
			var unit:GameUnit;
			var enemy:GameUnit;
			
			// Check if can move to the given destination.
			if (posIsFree(to) != true)
			{
				enemy = GameUnitHolder(unit_layer_element[to]).unit;
				if (enemy == null)
				{
					trace("Can't move there.");
					return;
				}
				
				// If there is an unit in the destination, then this is an attack action.
				moveAttack = true;
			}
			
			unit = GameUnitHolder(unit_layer_element[from]).unit;
			
			var path:Vector.<SPFNode> = shortestPath.findSPF(from, to);
			if (moveAttack)
			{
				trace("moveAttack from " + from + " to " + to);
				unit.moveAttack(from, path, enemy);
			}
			else
			{
				trace("move unit from " + from + " to " + to);
				unit.move(from, path);
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
			}
			
			if (unit != null)
			{
				unitOnFocus = unit;
				unitOnFocus.focusSign = true;
			}
			else
			{
				unitOnFocus = null;
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
			var index:int = Calc.pixel_to_idx(unit.x, unit.y, ConstTile.TILE_W, _width_tiles);
			unit.removeSelf();
			GameMapBuilder.removeUnit(unit, unit_layer_element, unit_layer, unit_top_layer, index, weightMap);
		}
	}
	
}