package src.stage
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Stage1 extends MyStage 
	{
		/**
		 * 
		 * @param	w Stage width.
		 * @param	h Stage height.
		 */
		public function Stage1(w:Number, h:Number)
		{
			// Fill background.
			bgImage = new BgLevel1Stage1;
			// Fill wall holder.
			wallHolderList = new WallHolderLevel1Stage1;
			
			// Center the cannon.
			cann.x = w/2
			cann.y = h - (cann.height);
		
			drawSelf();
		}
	}
	
}