package src
{
	import flash.display.MovieClip;
	import src.maps.GameMap;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GamePlay extends MovieClip 
	{
		private var gameMap:GameMap;
		//private var menuArea:MovieClip; // will handle this latter.
		
		
		
//##################################################################################################
// Public functions.
//##################################################################################################

		public function loadMap(map:GameMap) : void
		{
			gameMap = map;
			addChild(map);
		}
		
		public function unloadMap() : void
		{
			if (contains(gameMap) != true)
			{
				trace("Error: there is no game map to unload");
			}
			
			removeChild(gameMap);
		}




	}
	
}