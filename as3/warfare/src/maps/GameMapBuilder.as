package src.maps
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import src.buildings.*;
	import src.GamePlayer;
	import src.tiles.*;
	import src.tiles.tileset1000.*;
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
		public static function drawLandscape(elements_map:Array, elements:Array, map_width:int, map_height:int, tileset:GameTileset) : MovieClip
		{
			var layer:MovieClip = new MovieClip();
			var bitmap_data:BitmapData = new BitmapData(map_width * ConstTile.TILE_W, map_height * ConstTile.TILE_H);
			
			for (var i in elements_map)
			{				
				if ( (elements_map[i] - tileset.baseIndex) == 0)
				{
					continue;
				}
				
				// draw tile X in position for index 'i'.
				tileset.drawTile(bitmap_data,  elements_map[i], i);
				elements[i] = tileset.getTileElement(elements_map[i]);
			}
			
			layer.addChild(new Bitmap(bitmap_data));
			
			return layer;
		}
		
		public static function createBuildings(player:GamePlayer, elements:Array, map_width:int, tileset:GameTileset, layer:MovieClip) : void
		{
			var elements_map:Array = player.buildings_map;
			
			for (var i in elements_map)
			{
				if ( (elements_map[i] - tileset.baseIndex) == 0)
				{
					continue;
				}
				
				var building:GameBuilding = newBuildingFromId(elements_map[i]);
				var pos:Point = Calc.idx_to_pixel(i, map_width, ConstTile.TILE_W);
				building.x = pos.x;
				building.y = pos.y;
				elements[i] = building;
				
				layer.addChild(building);
				player.buildings.push(building);
			}
		}
		
		/**
		 * Create unit image layers (top and bottom) and fill unit layers with the units from map.
		 * @param	map_layer
		 * @param	element_layer
		 * @param	map_width
		 * @param   actions - an Array with the unit actions function handlers.
		 * [0] - move unit action handler.
		 * @return An Array with bottom layer (index 0) and upper layer (index 1).
		 */
		public static function createUnits(player:GamePlayer, elements:Array, map_width:int, actions:Array, weightMap:Array, layers:Array) : void
		{
			var elements_map:Array = player.units_map;

			for (var i in elements_map)
			{
				if (elements_map[i] == 0)
				{
					continue;
				}
				var unit:GameUnit = spawnUnit(elements_map[i], actions, i, map_width, elements, layers, weightMap);
				player.units.push(unit);
			}
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
				if (tile != null)
				{
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
		
		public static function spawnUnit(
			type:int,
			actions:Array,
			index:int,
			map_width:int,
			elements:Array,
			layers:Array,
			weightMap:Array) : GameUnit
		{
			var unit:GameUnit = GameMapBuilder.createUnit(type, actions, index, map_width);
			GameMapBuilder.addUnit(unit, elements, layers, index);
			// Update the weight of the node that the unit is in.
			SPFNode(weightMap[index]).weight += Const.UNIT_WEIGHT;
			
			return unit;
		}
		
		public static function createUnit(type:int, actions:Array, index:int, map_width:int) : GameUnit
		{
			var unit:GameUnit = newUnitFromId(type);
			var pos:Point = Calc.idx_to_pixel(index, map_width, ConstTile.TILE_W);
			
			unit.addEventListener(UnitMoveEvent.EVT_UNIT_MOVE, actions[0], false, 0, true);
			unit.addEventListener(UnitEngageEvent.EVT_UNIT_ENGAGE, actions[1], false, 0, true);
			unit.addEventListener(UnitBattleEvent.EVT_UNIT_BATTLE, actions[2], false, 0, true);
			unit.addEventListener(UnitRemoveEvent.EVT_UNIT_REMOVE, actions[3], false, 0, true);
			
			unit.x = pos.x;
			unit.y = pos.y;
			
			return unit;
		}
		
		public static function addUnit(unit:GameUnit, elements:Array, layers:Array, index:int) : void
		{
			var bottom_layer:MovieClip = layers[0];
			var top_layer:MovieClip = layers[1];
			var unit_holder:GameUnitHolder = GameUnitHolder(elements[index]);
			
			unit_holder.units.push(unit);
			bottom_layer.addChild(unit);
			
			if (unit.topImg != null)
			{
				unit.topImg.x = unit.x;
				unit.topImg.y = unit.y - ConstTile.TILE_H;
				top_layer.addChild(unit.topImg);
			}
		}
		
		public static function removeUnit(unit:GameUnit, elements:Array, layers:Array, index:int, weightMap:Array) : void
		{
			var bottom_layer:MovieClip = layers[0];
			var top_layer:MovieClip = layers[1];
			
			// Remove unit from reference array.
			GameUnitHolder(elements[index]).removeUnit(unit);
			
			// Remove bottom image of the unit.
			if (bottom_layer.contains(unit))
			{
				bottom_layer.removeChild(unit);
			}
			
			if ( (unit.topImg != null) && (top_layer.contains(unit.topImg)) )
			{
				top_layer.removeChild(unit.topImg);
			}
			
			// Update the weight of the node that the unit is in.
			SPFNode(weightMap[index]).weight -= Const.UNIT_WEIGHT;
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
		
		private static function newBuildingFromId(id:int) : GameBuilding
		{
			switch (id)
			{
				case ConstBuilding.BRIDGE_01_ID: return new Bridge01Building;
				case ConstBuilding.BRIDGE_02_ID: return new Bridge02Building;
				case ConstTileset1000.TILE1804_ID: return new CityBuilding(CityBuilding.LEVEL_0);
					
				default:
					trace("Invalid building id: " + id + " received.");
					return new Bridge01Building;
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