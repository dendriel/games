package src.maps
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	import src.Const;
	import src.IElementInfo;
	import src.tiles.*;
	import src.buildings.*;
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
		
		// Layer 3.
		private var unit_top_layer:MovieClip;
		
		// Graph map.
		private var weightMap:Array;
		
		// Calculation.
		var shortestPath:SPF;
		
		protected function drawSelf() : void
		{
			var i:int;
			tile_layer = new MovieClip;
			building_layer = new MovieClip;
			unit_layer = new MovieClip;
			
			shortestPath = new SPF();
			
			tile_layer_element = new Array(_width_tiles * height_tiles);
			building_layer_element = new Array(_width_tiles * height_tiles);
			unit_layer_element = new Array(_width_tiles * height_tiles);
			weightMap = new Array(_width_tiles * height_tiles);
			unit_top_layer = new MovieClip();
			
			// Initialize weight map (with default values) and unit layer array.
			for (i = 0; i < unit_layer_element.length; i++)
			{
				var p:Point = Calc.idx_to_coor(i, _width_tiles);
				unit_layer_element[i] = new GameUnitHolder( (p.x * ConstTile.TILE_W), (p.y * ConstTile.TILE_H) );
				
				weightMap[i] = new SPFNode(i);
			}
			
			// Draw landscape.
			if (tile_layer_map != null)
			{
				for (i = 0; i < tile_layer_map.length; i++)
				{
					if (tile_layer_map[i] == 0)
					{
						continue;
					}
					
					var tile = newTileFromId(tile_layer_map[i]);
					tile.x = (int) (i % width_tiles) * ConstTile.TILE_W;
					tile.y = (int)(i / height_tiles) * ConstTile.TILE_H;
					tile_layer_element[i] = tile;
					tile_layer.addChild(tile);
				}
			
				// Add layer 0.
				addChild(tile_layer);
			}
			
			// Draw buildings.
			if (building_layer_map != null)
			{
				for (i = 0; i < building_layer_map.length; i++)
				{
					if (building_layer_map[i] == 0)
					{
						continue;
					}
					
					var building = newBuildingFromId(building_layer_map[i]);
					building.x = (int) (i % width_tiles) * ConstTile.TILE_W;
					building.y = (int)(i / height_tiles) * ConstTile.TILE_H;
					
					building_layer_element[i] = building;
					building_layer.addChild(building);
				}
				
				// Add layer 1.
				addChild(building_layer);
			}
			
			// Draw units.
			if (unit_layer_map != null)
			{
				for ( i = 0; i < unit_layer_map.length; i++)
				{
					if (unit_layer_map[i] == 0)
					{
						continue;
					}
					
					var unit:GameUnit = createUnit(unit_layer_map[i]);
					unit.x = (int) (i % width_tiles) * ConstTile.TILE_W;
					unit.y = (int)(i / height_tiles) * ConstTile.TILE_H;
					
					unit_layer_element[i].units.push(unit);
					unit_layer.addChild(unit);
					
					if (unit.topImg != null)
					{
						unit.topImg.x = unit.x;
						unit.topImg.y = unit.y - ConstTile.TILE_H;
						unit_top_layer.addChild(unit.topImg);
						// add movieclip in layer
					}
				}
				// Add layer 3.
				addChild(unit_layer);
				addChild(unit_top_layer);
			}
			
			buildWeightMap();
			linkNeighborsOnMap();
			
			shortestPath.loadGraph(weightMap);
			//shortestPath.dumpGraph();
		}

//##################################################################################################
// Private functions.
//##################################################################################################
		private function createUnit(id:int) : GameUnit
		{
			var unit:GameUnit = newUnitFromId(id);
			
			// Configure unit.
			unit.addEventListener(UnitMoveEvent.EVT_UNIT_MOVE, handleUnitMove, false, 0, true);
			
			return unit;
		}

		private function newUnitFromId(id:int) : GameUnit
		{
			switch (id)
			{
				case ConstUnit.LEVY_INFANTRY01_ID: return new LevyInfantryUnit;
				case ConstUnit.KNIGHT01_ID_ID: return new KnightUnit;
				case ConstUnit.LIGHT_INFANTRY01_ID: return new LightInfantryUnit;
					
				default:
					trace("Invalid unit id: " + id + " received.");
					return new LevyInfantryUnit;
			}
		}
		
		private function newBuildingFromId(id:int) : GameBuilding
		{
			switch (id)
			{
				case ConstBuilding.BRIDGE_01_ID: return new Bridge01Building;
				case ConstBuilding.BRIDGE_02_ID: return new Bridge02Building;
				case ConstBuilding.VILLAGE_01_ID: return new Village01Building;
					
				default:
					trace("Invalid building id: " + id + " received.");
					return new Village01Building;
			}
		}
		
		// Create tile object from its ID.
		private function newTileFromId(id:int) : GameTile
		{
			switch (id)
			{
				case ConstTile.GRASS_01_ID:	return new Grass01Tile;
				case ConstTile.TREE_01_ID: return new Tree01Tile;
				case ConstTile.TREE_02_ID: return new Tree02Tile;
				case ConstTile.TREE_03_ID: return new Tree03Tile;
				case ConstTile.TREE_04_ID: return new Tree04Tile;					
				case ConstTile.TREE_05_ID: return new Tree05Tile;
				case ConstTile.TREE_06_ID: return new Tree06Tile;
				case ConstTile.MOUNTAIN_01_ID: return new Mountain01Tile;
				case ConstTile.MOUNTAIN_02_ID: return new Mountain02Tile;
				case ConstTile.MOUNTAIN_03_ID: return new Mountain03Tile;
				case ConstTile.MOUNTAIN_04_ID: return new Mountain04Tile;
				case ConstTile.MOUNTAIN_05_ID: return new Mountain05Tile;
				case ConstTile.MOUNTAIN_06_ID: return new Mountain06Tile;
				case ConstTile.RIVER_01_ID: return new River01Tile;
				case ConstTile.RIVER_02_ID: return new River02Tile;
				case ConstTile.RIVER_03_ID: return new River03Tile;
				case ConstTile.RIVER_04_ID: return new River04Tile;
				case ConstTile.RIVER_05_ID: return new River05Tile;
				case ConstTile.RIVER_06_ID: return new River06Tile;
				case ConstTile.RIVER_07_ID: return new River07Tile;
				case ConstTile.RIVER_08_ID: return new River08Tile;
				case ConstTile.ROAD_01_ID: return new Road01Tile;
				case ConstTile.ROAD_02_ID: return new Road02Tile;
				case ConstTile.ROAD_03_ID: return new Road03Tile;
				case ConstTile.ROAD_05_ID: return new Road05Tile;
				case ConstTile.ROAD_07_ID: return new Road07Tile;
				case ConstTile.ROAD_10_ID: return new Road10Tile;
				case ConstTile.ROAD_12_ID: return new Road12Tile;
				case ConstTile.ROAD_13_ID: return new Road13Tile;
				case ConstTile.ROAD_16_ID: return new Road16Tile;
					
				default:
					trace("Invalid tile id: " + id + " received.");
					return new Grass01Tile;
			}
		}
		
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
			
			// TODO: get unit by uid.
			var unit:GameUnit = holderFrom.pop();
			holderTo.addUnit(unit);
		}
		
		/**
		 * Update weight map nodes according to the tiles and buildings on the layers.
		 */
		private function buildWeightMap() : void
		{			
			// Update weight.
			for (var i in weightMap)
			{
				var node:SPFNode = weightMap[i];
				var tile:GameTile = tile_layer_element[i];
				var building:GameBuilding = building_layer_element[i];
				
				// Update weight.
				// Tile.
				if (tile.moveable != true)
				{
					node.weight = Const.NODE_DISCONNECTED;
				}
				else
				{
					// Transform move effort in weight. Bonuses will decrese the node weight while
					// penalties will increase the node it.
					node.weight = (-1 * (tile.moveEffort / 10) ) + Const.DEFAULT_WEIGHT;
				}
				
				// Building. Replaces the previous tile weight.
				if (building != null)
				{
					if (building.moveable != true)
					{
						node.weight = Const.NODE_DISCONNECTED;
					}
					else
					{
						// Transform move effort in weight. Bonuses will decrese the node weight while
						// penalties will increase the node it.
						node.weight = (-1 * (building.moveEffort / 10) ) + Const.DEFAULT_WEIGHT;
					}
				}
			}
		}
		
		/**
		 * Link the neighbors on the nodes.
		 */
		private function linkNeighborsOnMap() : void
		{
			var neighbor:SPFNode;
			
			// Find neighbors.
			for (var i in weightMap)
			{
				var node:SPFNode = weightMap[i];				
				var rightNeighbors:Boolean = true;
				var leftNeighbors:Boolean = true;
				var bottomNeighbors:Boolean = true;
				var topNeighbors:Boolean = true;
				
				if (node.weight == Const.NODE_DISCONNECTED)
				{
					continue;
				}
				
				// Check right neighbors.
				if ( ( (i + 1) % _width_tiles) == 0)
				{
					rightNeighbors = false;
				}
				
				// Check left neighbors.
				if ( (i % _width_tiles) == 0)
				{
					leftNeighbors = false;
				}
				
				// Check top neighbors.
				if ( i < _width_tiles)
				{
					topNeighbors = false;
				}
				
				// Check bottom neighbors.
				if ( ( i + _width_tiles) >= (_width_tiles * height_tiles) )
				{
					bottomNeighbors = false;
				}
				
				/*  X 0 0
				 *  0 0 0
				 *  0 0 0 */
				if (topNeighbors && leftNeighbors)
				{
					neighbor = weightMap[i - _width_tiles - 1];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
				
				/*  0 X 0
				 *  0 0 0
				 *  0 0 0 */
				if (topNeighbors)
				{
					neighbor = weightMap[i - _width_tiles];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
					
				}
				
				/*  0 0 X
				 *  0 0 0
				 *  0 0 0 */
				if (topNeighbors && rightNeighbors)
				{
					neighbor = weightMap[i - _width_tiles + 1];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
				
				/*  0 0 0
				 *  X 0 0
				 *  0 0 0 */
				if (leftNeighbors)
				{
					neighbor = weightMap[i - 1];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
				
				/*  0 0 0
				 *  0 0 X
				 *  0 0 0 */
				if (rightNeighbors)
				{
					neighbor = weightMap[i + 1];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
				
				/*  0 0 0
				 *  0 0 0
				 *  X 0 0 */
				if (bottomNeighbors && leftNeighbors)
				{
					neighbor = weightMap[i + _width_tiles - 1];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
				
				/*  0 0 0
				 *  0 0 0
				 *  0 X 0 */
				if (bottomNeighbors)
				{
					neighbor = weightMap[i + _width_tiles];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
				
				/*  0 0 0
				 *  0 0 0
				 *  X 0 0 */
				if (bottomNeighbors && rightNeighbors)
				{
					neighbor = weightMap[i + _width_tiles + 1];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
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
		 * Find unit by its index.
		 * @param	idx
		 * @return
		 */
		public function getUnit(idx:int) : GameUnit
		{
			var holder:Vector.<GameUnit> = unit_layer_element[idx].units;
			
			if (holder.length == 0)
			{
				return null;
			}
			// Return the first unit. TODO: select a specific unit.
			return holder[0];
		}
		
		public function moveUnit(from:int, to:int) : void
		{
			var holderFrom:Vector.<GameUnit> = unit_layer_element[from].units;
			
			// Check if there is any unit to move.
			if (holderFrom.length == 0)
			{
				trace("Nothing to move from here!");
				return;
			}
			
			// Check if can move to the given destination.
			if (posIsMoveable(to) != true)
			{
				trace("Can't move there.");
				return;
			}
			
			var unit:GameUnit = holderFrom.concat().pop();
			unit.move(from, to);
		}
	}
	
}