package src
{
	import flash.display.MovieClip;
	import src.ui.MainMenu;
	
	[SWF(width = "800", height = "600", frameRate = "30", backgroundColor = "#ff0000")] //set project properties
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Engine extends MovieClip
	{
		private var mainMenuR:MainMenu;
		private var gameStageR:GameStage;
		
		public function Engine() : void
		{
			mainMenuR = new MainMenu();
			
			gameStageR = new GameStage();
			gameStageR.x = 0;
			gameStageR.y = 0;
			
			this.addChild(gameStageR);
			
			startGame();
		}
		
		private function startGame() : void
		{
			// Display presentation.
			
			// Display main menu.
			
			displayMainMenu();
		}
		
// #################################################################################################
// Display Menus.
// #################################################################################################
		private function displayMainMenu() : void
		{
			if ( gameStageR.contains(mainMenuR) )
			{
				trace ("Error. Trying to add mainMenu to stage, but it's already in the references.");
				return;
			}

			gameStageR.addChild(mainMenuR);
		}
	}
}