package 
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class RedSlime extends Slime 
	{
		public function RedSlime(checkpointsRef:Vector.<Point>)
		{			
			super(checkpointsRef, Const.RED_SLIME_COLOR, Const.RED_SLIME_COLOR, Const.RED_SLIME_COLOR);
			drawSelf(Const.RED_SLIME_COLOR);
		}
	}
	
}