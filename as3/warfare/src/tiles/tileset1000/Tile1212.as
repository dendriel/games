package src.tiles.tileset1000
{
	import flash.display.Bitmap;
	import src.language.GameLanguage;
	import src.tiles.*;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tile1212 extends GameTile
	{
		public function Tile1212()
		{
			_id = ConstTileset1000.TILE1212_ID;
			_name = GameLanguage.lang.sea_name;
			_desc = GameLanguage.lang.sea_desc;
			_def = ConstTile.SEA_DEF;
			_moveable = ConstTile.SEA_MOVEABLE;
			_moveEffort = ConstTile.SEA_MOVEEFFORT;
			
			addChild(new Bitmap(new tile1212));
		}
	}
}