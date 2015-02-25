package src.buildings
{
	import src.language.GameLanguage;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Bridge02Building extends GameBuilding 
	{
		public function Bridge02Building() : void
		{
			_id = ConstBuilding.BRIDGE_02_ID;
			_name = GameLanguage.lang.bridge01_name;
			_desc = GameLanguage.lang.bridge01_desc;
			
			_def = ConstBuilding.BRIDGE_01_DEF;
			_moveable =  ConstBuilding.BRIDGE_01_MOVEABLE;
			_moveEffort = ConstBuilding.BRIDGE_01_MOVEEFFORT;
		}
	}
	
}