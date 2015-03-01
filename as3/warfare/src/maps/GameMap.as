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
			unit_layer_element = new Array(_width_tiles * height_tiles);
			weightMap = new Array(_width_tiles * height_tiles);
			unit_actions = new Array(handleUnitMove);
			
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
			
			// Draw units.
			if (unit_layer_map != null)
			{
				var layers:Array = GameMapBuilder.createUnits(unit_layer_map, unit_layer_element, _width_tiles, height_tiles, unit_actions);
				unit_layer = layers[0];
				unit_top_layer = layers[1];
				
				// Add layer 3.
				addChild(unit_layer);
				addChild(unit_top_layer);
			}
			
			// Configure SPF.
			GameMapBuilder.buildWeightMap(weightMap, tile_layer_element, building_layer_element);
			GameMapBuilder.linkNeighborsOnMap(weightMap, _width_tiles, height_tiles);
			shortestPath.loadGraph(weightMap);
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
		private function posIsMoveable(idx:int) : Boolean
		{
			var moveable = true;
			
			var tile:GameTile = tile_layer_element[idx];
			var building:GameBuilding = building_layer_element[idx];
			
			// If the tile isn't moveable.
			if (tile.moveable != true)
			{
				moveable = false;
			}
			
			if ( (building != null) && (building.moveable == true) )
			{
				moveable = true;
			}
			
			return moveable;
		}
		
		private function handleUnitMove(e:UnitMoveEvent) : void
		{ 
			var holderFrom:Vector.<GameUnit> = unit_layer_element[e.fromIdx].units;
			var holderTo:GameUnitHolder = unit_layer_element[e.toIdx];
			
			// Remove unit from the origin holder.
			holderFrom.splice(holderFrom.indexOf(e.unit), 1);
			// Insert unit into the destination holder.
			holderTo.addUnit(e.unit);
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
		 * Get the unit at the top of a position (the last to enter in the position).
		 * @param	idx
		 * @return
		 */
		public function getUpperMostUnit(idx:int) : GameUnit
		{
			// Search inside units layer.			
			if (unit_layer_element != null)
			{
				var units_list_temp:Vector.<GameUnit> = unit_layer_element[idx].units.concat();
				
				trace("units list: " + units_list_temp.length);
				if (units_list_temp.length > 0)
				{
					var unit:GameUnit = units_list_temp.pop();
					trace("unit uid: " + unit.uid);
					return unit;
				}
			}
			
			return null;
		}
		
		/**
		 * Find unit by its index.
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
		
		public function moveUnit(unit:GameUnit, from:int, to:int) : void
		{			
			// Check if can move to the given destination.
			if (posIsMoveable(to) != true)
			{
				trace("Can't move there.");
				return;
			}
			
			var path:Vector.<SPFNode> = shortestPath.findSPF(from, to);
			unit.move(from, path);
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
		
		public function addUnit(type:int, posx:int, posy:int) : Boolean
		{
			var index:int = Calc.coor_to_idx(posx, posy, _width_tiles);
			var unit:GameUnit = GameMapBuilder.createUnit(type, unit_actions, index, _width_tiles);
			GameMapBuilder.addUnit(unit, unit_layer_element, unit_layer, unit_top_layer, index);
			
			return true;
		}
	}
	
}