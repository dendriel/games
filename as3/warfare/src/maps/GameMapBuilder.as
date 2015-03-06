package src.maps
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import src.buildings.*;
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
		public static function drawLandscape(map_layer:Array, element_layer:Array, map_width:int, map_height:int, tileset:GameTileset) : MovieClip
		{
			var layer:MovieClip = new MovieClip();
			var bitmap_data:BitmapData = new BitmapData(map_width * ConstTile.TILE_W, map_height * ConstTile.TILE_H);
			
			for (var i in map_layer)
			{
				if (map_layer[i] == 0)
				{
					continue;
				}
				
				var type:int = map_layer[i];
				
				// draw tile X in position for index 'i'.
				tileset.drawTile(bitmap_data, type, i);
				element_layer[i] = tileset.getTileElement(type);
			}
			
			layer.addChild(new Bitmap(bitmap_data));
			
			return layer;
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
			unit.addEventListener(UnitEngageEvent.EVT_UNIT_ENGAGE, actions[1], false, 0, true);
			unit.addEventListener(UnitBattleEvent.EVT_UNIT_BATTLE, actions[2], false, 0, true);
			unit.addEventListener(UnitRemoveEvent.EVT_UNIT_REMOVE, actions[3], false, 0, true);
			
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
		
		public static function removeUnit(unit:GameUnit, element_layer:Array, image_layer:MovieClip, image_layer_top:MovieClip, index:int, weightMap:Array) : void
		{			
			// Remove unit from reference array.
			GameUnitHolder(element_layer[index]).removeUnit(unit);
			
			// Remove bottom image of the unit.
			if (image_layer.contains(unit))
			{
				image_layer.removeChild(unit);
			}
			
			if ( (unit.topImg != null) && (image_layer_top.contains(unit.topImg)) )
			{
				image_layer_top.removeChild(unit.topImg);
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