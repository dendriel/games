package src.tiles.tileset1000
{
	import flash.display.Bitmap;
	import src.language.GameLanguage;
	import src.tiles.*;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tile1066 extends GameTile
	{
		public function Tile1066()
		{
			_id = ConstTileset1000.TILE1066_ID;
			_name = GameLanguage.lang.grass_name;
			_desc = GameLanguage.lang.grass_desc;
			_def = ConstTile.GRASS_DEF;
			_moveable = ConstTile.GRASS_MOVEABLE;
			_moveEffort = ConstTile.GRASS_MOVEEFFORT;
			
			addChild(new Bitmap(new tile1066));
		}
	}
}