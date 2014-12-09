package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.ui.StartScreenUI;
	import src.stage.*;
	import src.com.senocular.utils.KeyObject;
	
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
		private var key:KeyObject;
		
		// UI.
		private var startScreenUIR:StartScreenUI;
		
		// Engine.
		private var levelHolderR:LevelHolder;
		
		public function Engine()
		{
			// Create stage.
			gameStageR = new GameStage();
			gameStageR.w = stage.stageWidth;
			gameStageR.h = stage.stageHeight;
			
			stage.addChild(gameStageR);
			
			// Create auxiliary objects.
			key = new KeyObject(stage);
			
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
			// Create Level 1.
			var level1 = new Level();
			level1.add(new Stage1(gameStageR.w, gameStageR.h));
			
			// Create Level 2.
			// Create Level 3.
			// Create Level 4...
			
			levelHolderR.add(level1);
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
			
			// Call GameLevelSelectorScreen
			// then, GameStageSelectorScreen
			// then, play stage.
			
			/* Testing purpose. */
			var lvl = levelHolderR.getLevel();
			var stage = lvl.getStage();
			
			// Play this stage.
			loadStage(stage);
		}
		
		/*************************************************/
		/* GamePlay related methods. */
		/*************************************************/
		/**
		 * @usage Loads and start the given stage.
		 */
		private function loadStage(stg:MyStage) : void
		{
			stg.load(key);
			gameStageR.addChild(stg);
			
			stage.stageFocusRect = false;
			stage.focus = gameStageR;
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
		
		/*************************************************/
		/* Stage Screen related methods. */
		/*************************************************/
	}
	
}