package src.maps
{
	import flash.display.MovieClip;
	import src.IElementInfo;
	import src.tiles.*;
	import src.buildings.*;
	import src.units.*;
	import src.as3.math.Calc;
	
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
		private var tile_layer:MovieClip;
		private var tile_layer_element:Vector.<GameTile>;
		
		// Layer 1.
		protected var building_layer_map:Array;		
		private var building_layer:MovieClip;
		private var building_layer_element:Vector.<GameBuilding>;
		
		// Layer 2.
		protected var unit_layer_map:Array;
		private var unit_layer:MovieClip;
		private var unit_layer_element:Vector.<GameUnit>;
		
		protected function drawSelf() : void
		{
			var i:int;
			tile_layer = new MovieClip;
			tile_layer_element = new Vector.<GameTile>;
			building_layer = new MovieClip;
			building_layer_element = new Vector.<GameBuilding>;
			unit_layer = new MovieClip;
			unit_layer_element = new Vector.<GameUnit>;
			
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
					tile_layer_element.push(tile);
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
					building_layer_element.push(building);
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
					
					//TODO.
					//unit_layer_element.push(unit);
					//unit_layer.addChild(unit);
				}
				// Add layer 3.
				addChild(unit_layer);
			}
		}
		
		private function newBuildingFromId(id:int) : GameBuilding
		{
			switch (id)
			{
				case ConstBuilding.BRIDGE_01_ID:
					return new Bridge01Building;
					
				case ConstBuilding.BRIDGE_02_ID:
					return new Bridge02Building;
					
				case ConstBuilding.VILLAGE_01_ID:
					return new Village01Building;
					
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
				case ConstTile.GRASS_01_ID:
					return new Grass01Tile;
				
				case ConstTile.TREE_01_ID:
					return new Tree01Tile;
					
				case ConstTile.TREE_02_ID:
					return new Tree02Tile;
					
				case ConstTile.TREE_03_ID:
					return new Tree03Tile;
					
				case ConstTile.TREE_04_ID:
					return new Tree04Tile;
					
				case ConstTile.TREE_05_ID:
					return new Tree05Tile;
					
				case ConstTile.TREE_06_ID:
					return new Tree06Tile;
					
				case ConstTile.MOUNTAIN_01_ID:
					return new Mountain01Tile;
					
				case ConstTile.MOUNTAIN_02_ID:
					return new Mountain02Tile;
					
				case ConstTile.MOUNTAIN_03_ID:
					return new Mountain03Tile;
					
				case ConstTile.MOUNTAIN_04_ID:
					return new Mountain04Tile;
					
				case ConstTile.MOUNTAIN_05_ID:
					return new Mountain05Tile;
					
				case ConstTile.MOUNTAIN_06_ID:
					return new Mountain06Tile;
					
				case ConstTile.RIVER_01_ID:
					return new River01Tile;
					
				case ConstTile.RIVER_02_ID:
					return new River02Tile;
					
				case ConstTile.RIVER_03_ID:
					return new River03Tile;
					
				case ConstTile.RIVER_04_ID:
					return new River04Tile;
					
				case ConstTile.RIVER_05_ID:
					return new River05Tile;
					
				case ConstTile.RIVER_06_ID:
					return new River06Tile;
					
				case ConstTile.RIVER_07_ID:
					return new River07Tile;
					
				case ConstTile.RIVER_08_ID:
					return new River08Tile;
					
				default:
					trace("Invalid tile id: " + id + " received.");
					return new Grass01Tile;
			}
		}
		
		public function get width_tiles():int 
		{
			return _width_tiles;
		}
		
		/**
		 * @brief Get an element from the map.
		 * @param	idx Position of the Element.
		 */
		public function getElement(idx:int) : void
		{
			trace("index: " + idx);
			
			// Search inside units layer.
			/*var unit_layer_temp:Vector.<GameUnit> = unit_layer_element.concat();
			
			while (unit_layer_temp.lenght()
			if (unit_layer_element != null)
			{
				for each (var unit in unit_layer)
				{
					if (unit.getElementIdx(unit.x, unit.y) == idx)
					{
						trace("found unit!");
						break;
					}
				}
			}*/
			
			// Search inside building layer.
			if (building_layer_element != null)
			{
				var building_layer_temp:Vector.<GameBuilding> = building_layer_element.concat();
				var building:GameBuilding;
				
				while (building_layer_temp.length > 0)
				{
					building = building_layer_temp.pop();
					if (getElementIdx(building.x, building.y) == idx)
					{
						var info:IElementInfo = IElementInfo(building);
						trace("found building! Type is: " + info.get_type() + "; Name: " + info.get_name());
						break;
					}
					
				}
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
	}
	
}