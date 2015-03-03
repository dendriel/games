package src.tiles
{
	import src.language.GameLanguage;
	import src.as3.math.Calc;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Grass01Tile extends GameTile
	{
		public function Grass01Tile()
		{
			_id = ConstTile.GRASS_01_ID;
			_name = GameLanguage.lang.grass01_name;
			_desc = GameLanguage.lang.grass01_desc;
			_def = ConstTile.GRASS_01_DEF;
			_moveable = ConstTile.GRASS_01_MOVEABLE;
			_moveEffort = ConstTile.GRASS_01_MOVEEFFORT;
			
			// Add random grass tile.
			var number = int(Calc.randomRange(1, 5));
				trace("random number is: " + number);
			switch(number)
			//switch(Calc.randomRange(1, 5))
			{
				case 1:
					addChild(new Grass010Tile);
					break;
				case 2:
					addChild(new Grass011Tile);
					break;
				case 3:
					addChild(new Grass012Tile);
					break;
				case 4:
					addChild(new Grass013Tile);
					break;
				case 5:
					addChild(new Grass014Tile);
					break;
					
				default:
					addChild(new Grass010Tile);
					break;
			}
		}
	}
}