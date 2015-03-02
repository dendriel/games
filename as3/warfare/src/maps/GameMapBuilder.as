package src.maps
{
	import flash.display.MovieClip;
	import flash.geom.Point;
	import src.buildings.*;
	import src.tiles.*;
	import src.units.*;
	import src.Const;
	import src.as3.math.graph.SPFNode;
	import src.as3.math.Calc;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameMapBuilder 
	{
		public static function drawLandscape(map_layer:Array, element_layer:Array, map_width:int, map_height:int) : MovieClip
		{
			var image_layer:MovieClip = new MovieClip();
			
			for (var i in map_layer)
			{
				if (map_layer[i] == 0)
				{
					continue;
				}
				
				var tile:GameTile = newTileFromId(map_layer[i]);
				tile.x = (int) (i % map_width) * ConstTile.TILE_W;
				tile.y = (int)(i / map_height) * ConstTile.TILE_H;
				element_layer[i] = tile;
				
				image_layer.addChild(tile);
			}
			
			return image_layer;
		}
		
		public static function drawBuildings(map_layer:Array, element_layer:Array, map_width:int, map_height:int) : MovieClip
		{
			var image_layer:MovieClip = new MovieClip();
			
			for (var i in map_layer)
			{
				if (map_layer[i] == 0)
				{
					continue;
				}
				
				var building:GameBuilding = newBuildingFromId(map_layer[i]);
				building.x = (int) (i % map_width) * ConstTile.TILE_W;
				building.y = (int)(i / map_height) * ConstTile.TILE_H;
				element_layer[i] = building;
				
				image_layer.addChild(building);
			}
			
			return image_layer;
		}
		
		/**
		 * Create unit image layers (top and bottom) and fill unit layers with the units from map.
		 * @param	map_layer
		 * @param	element_layer
		 * @param	map_width
		 * @param	map_height
		 * @param   actions - an Array with the unit actions function handlers.
		 * [0] - move unit action handler.
		 * @return An Array with bottom layer (index 0) and upper layer (index 1).
		 */
		public static function createUnits(map_layer:Array, element_layer:Array, map_width:int, map_height:int, actions:Array, weightMap:Array) : Array
		{
			var image_layer:MovieClip = new MovieClip();
			var image_layer_top:MovieClip = new MovieClip();

			for (var i in map_layer)
			{
				if (map_layer[i] == 0)
				{
					continue;
				}
				
				spawnUnit(map_layer[i], actions, i, map_width, element_layer, image_layer, image_layer_top, weightMap);
			}
			
			return new Array(image_layer, image_layer_top);
		}
		
		/**
		 * Update weight map nodes according to the tiles and buildings on the layers.
		 */
		public static function buildWeightMap(weight_map:Array, tile_layer_element:Array, building_layer_element:Array) : void
		{			
			// Update weight.
			for (var i in weight_map)
			{
				var node:SPFNode = weight_map[i];
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
		public static function linkNeighborsOnMap(weight_map:Array, map_width:int, map_height:int) : void
		{
			var neighbor:SPFNode;
			
			// Find neighbors.
			for (var i in weight_map)
			{
				var node:SPFNode = weight_map[i];				
				var rightNeighbors:Boolean = true;
				var leftNeighbors:Boolean = true;
				var bottomNeighbors:Boolean = true;
				var topNeighbors:Boolean = true;
				
				if (node.weight == Const.NODE_DISCONNECTED)
				{
					continue;
				}
				
				// Check right neighbors.
				if ( ( (i + 1) % map_width) == 0)
				{
					rightNeighbors = false;
				}
				
				// Check left neighbors.
				if ( (i % map_width) == 0)
				{
					leftNeighbors = false;
				}
				
				// Check top neighbors.
				if ( i < map_width)
				{
					topNeighbors = false;
				}
				
				// Check bottom neighbors.
				if ( ( i + map_width) >= (map_width * map_height) )
				{
					bottomNeighbors = false;
				}
				
				/*  X 0 0
				 *  0 0 0
				 *  0 0 0 */
				if (topNeighbors && leftNeighbors)
				{
					neighbor = weight_map[i - map_width - 1];
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
					neighbor = weight_map[i - map_width];
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
					neighbor = weight_map[i - map_width + 1];
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
					neighbor = weight_map[i - 1];
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
					neighbor = weight_map[i + 1];
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
					neighbor = weight_map[i + map_width - 1];
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
					neighbor = weight_map[i + map_width];
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
					neighbor = weight_map[i + map_width + 1];
					if (neighbor.weight != Const.NODE_DISCONNECTED)
					{
						node.neighborList.push(neighbor);
					}
				}
			}
		}
		
		public static function spawnUnit(
			type:int,
			actions:Array,
			index:int,
			map_width:int,
			element_layer:Array,
			image_layer:MovieClip,
			image_layer_top:MovieClip,
			weightMap:Array) : void
		{
			var unit:GameUnit = GameMapBuilder.createUnit(type, actions, index, map_width);
			GameMapBuilder.addUnit(unit, element_layer, image_layer, image_layer_top, index);
			// Update the weight of the node that the unit is in.
			SPFNode(weightMap[index]).weight += Const.UNIT_WEIGHT;
		}
		
		public static function createUnit(type:int, actions:Array, index:int, map_width:int) : GameUnit
		{
			var unit:GameUnit = newUnitFromId(type);
			var pos:Point = Calc.idx_to_coor(index, map_width);
			unit.addEventListener(UnitMoveEvent.EVT_UNIT_MOVE, actions[0], false, 0, true);
			unit.x = pos.x * ConstTile.TILE_W;
			unit.y = pos.y * ConstTile.TILE_H;
			
			return unit;
		}
		
		public static function addUnit(unit:GameUnit, element_layer:Array, image_layer:MovieClip, image_layer_top:MovieClip, index:int) : void
		{
			element_layer[index].units.push(unit);
			image_layer.addChild(unit);
			
			if (unit.topImg != null)
			{
				unit.topImg.x = unit.x;
				unit.topImg.y = unit.y - ConstTile.TILE_H;
				image_layer_top.addChild(unit.topImg);
			}
		}
		
		// Create tile object from its ID.
		private static function newTileFromId(id:int) : GameTile
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
		
		private static function newBuildingFromId(id:int) : GameBuilding
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
		
		private static function newUnitFromId(id:int) : GameUnit
		{
			switch (id)
			{
				case ConstUnit.LEVY_INFANTRY01_ID: return new LevyInfantryUnit;
				case ConstUnit.KNIGHT01_ID_ID: return new KnightUnit;
				case ConstUnit.LIGHT_INFANTRY01_ID: return new LightInfantryUnit;
				case ConstUnit.LEVY_ARCHER01_ID: return new LevyArcherUnit;
					
				default:
					trace("Invalid unit id: " + id + " received.");
					return new LevyInfantryUnit;
			}
		}
	}
	
}