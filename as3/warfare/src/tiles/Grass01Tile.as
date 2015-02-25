package src.tiles
{
	import src.language.GameLanguage;
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
		}
	}
}