package src.buildings
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Bridge01Building extends MovieClip 
	{
		private var attr:BuildingAttr;
		
		public function Bridge01Building() : void
		{
			attr = new BuildingAttr();
			
			attr.id = ConstBuilding.BRIDGE_01_ID;
		}
	}
	
}