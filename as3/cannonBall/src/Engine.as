package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.ui.StartScreenUI;
	
	[SWF(width = "480", height = "320", frameRate = "30", backgroundColor = "#ff0000")] //set project properties
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * 
	 * Some tips for myself.
	 * 
	 * - Don't create variables nor parameters with the name of types/classes.
	 * 
	 * 
	 * 
	 */
	public class Engine extends MovieClip
	{
		private var gameStageR:GameStage;
		
		// UI.
		private var startScreenUIR:StartScreenUI;
		
		// Engine.
		private var levelHolderR:LevelHolder;
		
		public function Engine()
		{
			// Create stage.
			gameStageR = new GameStage();
			stage.addChild(gameStageR);
			
			
			// Create UI.
			startScreenUIR = new StartScreenUI();
			
			// Create game play objects.
			levelHolderR = new LevelHolder();
			
			
			// Load Levels.
			loadLevelHolder();
			
			
			// Start Game.
			displayStartScreen();
		}
		
		
		/******************************************************************************************/
		/* Private methods */
		/******************************************************************************************/
		
		/**
		 * @usage Fill level holder with levels.
		 */
		private function loadLevelHolder() : void
		{
			levelHolderR.add(new Level());
		}
		
		/*************************************************/
		/* Start Screen related methods. */
		/*************************************************/
		/**
		 * @usage Initialize and display start screen.
		 */
		private function displayStartScreen() : void
		{
			startScreenUIR.load();
			
			startScreenUIR.addEventListener(Const.START_GAME_CLICK_EVT, handleStartGameClick, false, 0, true);
			
			gameStageR.addChild(startScreenUIR);
		}
		
		/**
		 * @usage Initialize and hide start screen.
		 */
		private function hideStartScreen() : void
		{
			startScreenUIR.unload();
			
			startScreenUIR.removeEventListener(Const.START_GAME_CLICK_EVT, handleStartGameClick);
			
			if (gameStageR.contains(startScreenUIR))
			{
				gameStageR.removeChild(startScreenUIR);
			}
		}
		
		/**
		 * @usage Handle start game event.
		 */
		private function handleStartGameClick(e:Event) : void
		{
			hideStartScreen();
			
			/* Testing purpose. */
			var l:Level = levelHolderR.getLevel();
			gameStageR.addChild(l);
		}
		
		/*************************************************/
		/* Selector Screen related methods. */
		/*************************************************/
		
		/*************************************************/
		/* Transition Screen related methods. */
		/*************************************************/
		
		/*************************************************/
		/* Level Screen related methods. */
		/*************************************************/
	}
	
}