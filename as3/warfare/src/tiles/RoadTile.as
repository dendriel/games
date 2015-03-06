package src.tiles
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class RoadTile extends GameTile 
	{
		public function RoadTile()
		{
			_def = ConstTile.ROAD_DEF;
			_moveable = ConstTile.ROAD_MOVEABLE;
			_moveEffort = ConstTile.ROAD_MOVEEFFORT;
			_name = GameLanguage.lang.road_name;
			_desc = GameLanguage.lang.road_desc;
			
		}
	}
}