package src
{
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public interface ILevel  
	{
		/**
		 * @return The level map label in timeline.
		 */
		function getMapLabel() : String;
		
		/**
		 * @return The level waves data.
		 */
		function getWaves() : Vector.<MonsterWave>;
		
		/**
		 * Update/play level.
		 */
		function playLevel() : void;
	}
	
}