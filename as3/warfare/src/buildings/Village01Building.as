package src.buildings
{
	import flash.display.MovieClip;
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Village01Building extends GameBuilding 
	{		
		public function Village01Building() : void
		{
			id = ConstBuilding.VILLAGE_01_ID;
			elemName = GameLanguage.village01_name;
			elemDesc = GameLanguage.village01_desc;
		}
	}
	
}