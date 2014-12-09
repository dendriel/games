package src.stage
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	import src.com.senocular.utils.KeyObject;
	
	import src.Cannon;
	
	/**
	 * @usage Contains levels.
	 * @author Vitor Rozsa
	 */
	public class MyStage extends MovieClip
	{
		protected var bgImage:MovieClip;
		protected var cann:Cannon;
		
		public function MyStage()
		{
			cann = new Cannon();
		}

		/******************************************************************************************/
		/* Private methods */
		/******************************************************************************************/
		/**
		 * @usage Load necessary resources.
		 */
		public function load(key:KeyObject) : void
		{
			// Load key control into cannon.
			cann.load(key);
			// Add cannon into stage.
			this.addChild(cann);
			
			// Start updateSelf.
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
		}
		
		/**
		 * @usage Free allocated resources.
		 */
		public function unload() : void
		{
			// Stop cannon.
			cann.unload();
			if (this.contains(cann))
			{
				this.removeChild(cann);
			}
			
			// Stop running.
			removeEventListener(Event.ENTER_FRAME, updateSelf);
		}		
		
		/******************************************************************************************/
		/* Protected methods */
		/******************************************************************************************/
		
		/**
		 * @usage Draw the stage contents.
		 */
		protected function drawSelf() : void
		{
			// Draw background.
			this.addChild(bgImage);
		}
		
		/**
		 * @usage Remove the stage contents.
		 */
		protected function removeSelf() : void
		{
			if (this.contains(bgImage))
			{
				this.removeChild(bgImage);
			}
		}
		
		/******************************************************************************************/
		/* Private methods */
		/******************************************************************************************/
		/**
		 * @usage Update self.
		 * @param	e
		 */
		private function updateSelf(e:Event) : void
		{
		}
	}
	
}