package src
{
	import flash.display.MovieClip;
	import src.tiles.Grass01Tile;
	import src.ui.MainMenu;
	import src.maps.*;
	
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
		
		// Main line.
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
			
			var map = new TestMap();
			gameStageR.addChild(map);
		}
		
		private function hideMainMenu() : void
		{
			if ( gameStageR.contains(mainMenuR) )
			{
				gameStageR.removeChild(mainMenuR);
				return;
			}
			else
			{
				trace ("Error. Trying to hide mainMenu from stage, but it is not in the references.");
			}
		}
		
		private function displaySinglePlayerSetup() : void
		{
			// TODO;
		}
		
		private function hideSinglePlayerSetup() : void
		{
			// TODO;
		}

		
		private function displayMultiplayerSetup() : void
		{
			// TODO;
		}
		
		private function hideMultiplayerSetup() : void
		{
			// TODO;
		}
		
		private function displayCredits() : void
		{
			// TODO;
		}
		
		private function hideCredits() : void
		{
			// TODO;
		}
		
// #################################################################################################
// In game view.
// #################################################################################################




	}
}