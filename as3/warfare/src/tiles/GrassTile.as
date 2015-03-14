package src.tiles
{
	import src.language.GameLanguage;
	import src.as3.math.Calc;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GrassTile extends GameTile
	{
		public function GrassTile()
		{
			_id = ConstTile.GRASS_TILE_ID;
			
			_name = GameLanguage.lang.grass_name;
			_desc = GameLanguage.lang.grass_desc;
			_def = ConstTile.GRASS_DEF;
			_moveable = ConstTile.GRASS_MOVEABLE;
			_moveBonus = ConstTile.GRASS_MOVEEFFORT;
		}
	}
}