package src.buildings
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Village01Building extends MovieClip 
	{
		private var attr:BuildingAttr;
		
		public function Village01Building() : void
		{
			attr = new BuildingAttr();
			
			attr.id = ConstBuilding.VILLAGE_01_ID;
		}
		
	}
	
}