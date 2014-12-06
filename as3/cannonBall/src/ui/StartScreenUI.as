package src.ui
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class StartScreenUI extends MovieClip 
	{
		/******************************************************************************************/
		/* Public methods */
		/******************************************************************************************/
		
		/**
		 * @usage Initialize elements.
		 */
		public function load() : void
		{
			btnStartGameUI.addEventListener(MouseEvent.CLICK, handleStartGame, false, 0, true);
			
		}
		
		/**
		 * @usage Finalize elements.
		 */
		public function unload() : void
		{
			btnStartGameUI.removeEventListener(MouseEvent.CLICK, handleStartGame);
		}
		
		/******************************************************************************************/
		/* Private methods */
		/******************************************************************************************/
		
		/**
		 * @usage Handle start game button click.
		 * @param	e
		 */
		private function handleStartGame(e:Event) : void
		{
			dispatchEvent(new Event(Const.START_GAME_CLICK_EVT));
		}
	}
	
}