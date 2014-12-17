package src.stage
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Stage2 extends MyStage 
	{
		/**
		 * 
		 * @param	w Stage width.
		 * @param	h Stage height.
		 */
		public function Stage2(w:Number, h:Number)
		{
			// Fill background.
			bgImage = new BgLevel1Stage2;
			// Fill wall holder.
			wallHolderList = new WallHolderLevel1Stage2;
			//wallHolderList = new WallHolderTest;
			// Fill target.
			targeHoldertList = new TargetHolderLevel1Stage2;
			
			// Center the cannon.
			cann.x = w/2
			cann.y = h - (cann.height);
		
			drawSelf();
		}
	}
	
}