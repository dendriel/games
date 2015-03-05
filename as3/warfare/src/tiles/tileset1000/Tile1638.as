package src.tiles.tileset1000
{
	import flash.display.Bitmap;
	import src.language.GameLanguage;
	import src.tiles.*;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Tile1638 extends GameTile
	{
		public function Tile1638()
		{
			_id = ConstTileset1000.TILE1638_ID;
			_name = GameLanguage.lang.lake_name;
			_desc = GameLanguage.lang.lake_desc;
			_def = ConstTile.LAKE_DEF;
			_moveable = ConstTile.LAKE_MOVEABLE;
			_moveEffort = ConstTile.LAKE_MOVEEFFORT;
			
			addChild(new Bitmap(new tile1638));
		}
	}
}