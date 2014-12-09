package src
{
	import flash.display.Stage;
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.com.senocular.utils.KeyObject;
	import flash.ui.Keyboard;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Cannon extends MovieClip 
	{
		private var key:KeyObject;
		
		/******************************************************************************************/
		/* Public methods */
		/******************************************************************************************/
		/**
		 * @usage Allow player to interact with the cannon.
		 * @param	keyRef
		 */
		public function load(keyRef:KeyObject)
		{
			// out of use, so far.
			key = keyRef;
			
			// Start updateSelf.
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
		}
		
		/**
		 * @usage Stop interaction and free resources.
		 */
		public function unload() : void
		{
			removeEventListener(Event.ENTER_FRAME, updateSelf);
			key = null;
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
			if (key.isDown(Keyboard.LEFT) || key.isDown(Keyboard.A))
			{
				trace("left");
			}
			else if (key.isDown(Keyboard.RIGHT) || key.isDown(Keyboard.D))
			{
				trace("right");
			}
			
			if (key.isDown(Keyboard.UP) || key.isDown(Keyboard.W))
			{
				trace("up");
			}
			else if (key.isDown(Keyboard.DOWN) || key.isDown(Keyboard.S))
			{
				trace("down");
			}
			
			// action key.
			if (key.isDown(Keyboard.SPACE))
			{
				trace("space");
			}
		}
	}
	
}