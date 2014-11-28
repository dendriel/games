package src
{
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class WaterSlime extends Slime 
	{
		public function WaterSlime(checkpointsRef:Vector.<Point>)
		{			
			super(checkpointsRef, Const.WATER_SLIME_GOLD, Const.WATER_SLIME_SPEED, Const.WATER_SLIME_LIFE);
			drawSelf(Const.WATER_SLIME_COLOR);
		}
	}
	
}