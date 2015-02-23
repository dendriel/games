package src.buildings
{
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Village01Building extends GameBuilding 
	{		
		public function Village01Building()
		{
			_id = ConstBuilding.VILLAGE_01_ID;
			_name = GameLanguage.lang.village01_name;
			_desc = GameLanguage.lang.village01_desc;
		}
	}
	
}