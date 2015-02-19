package src.buildings
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Bridge02Building extends MovieClip 
	{
		private var attr:BuildingAttr;
		
		public function Bridge02Building() : void
		{
			attr = new BuildingAttr();
			
			attr.id = ConstBuilding.BRIDGE_02_ID;
		}
		
	}
	
}