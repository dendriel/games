package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import src.tiles.Grass01Tile;
	import src.ui.MainMenu;
	import src.maps.*;
	
	[SWF(width = "800", height = "600", frameRate = "30", backgroundColor = "#333333")] //set project properties
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Engine extends MovieClip
	{
		private var gameStageR:GameStage;
		private var mainMenuR:MainMenu;
		private var gamePlayR:GamePlay;
		
		public function Engine() : void
		{			
			gameStageR = new GameStage();
			gameStageR.x = 0;
			gameStageR.y = 0;
			
			mainMenuR = new MainMenu();
			gamePlayR = new GamePlay();
			
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
		
//##################################################################################################
// Display Menus.
//##################################################################################################

//################### Main Menu.
		private function displayMainMenu() : void
		{
			if ( gameStageR.contains(mainMenuR) )
			{
				trace ("Error. Trying to add mainMenu to stage, but it's already in the references.");
				return;
			}
			
			gameStageR.addChild(mainMenuR);
			gameStageR.mouseEnabled = false;
			mainMenuR.addEventListener(Const.EVT_SINGLE_PLAYER_CLICK, handleSinglePlayerClick, false, 0, true);
			mainMenuR.addEventListener(Const.EVT_MULTIPLAYER_CLICK, handleMultiplayerClick, false, 0, true);
			mainMenuR.addEventListener(Const.EVT_CREDITS_CLICK, handleCreditsClick, false, 0, true);
			mainMenuR.enable();
		}
		
		private function hideMainMenu() : void
		{
			if ( gameStageR.contains(mainMenuR) != true)
			{
				trace ("Error. Trying to hide mainMenu from stage, but it is not in the references.");
				return;
			}
			
			gameStageR.removeChild(mainMenuR);
			mainMenuR.removeEventListener(Const.EVT_SINGLE_PLAYER_CLICK, handleSinglePlayerClick);
			mainMenuR.removeEventListener(Const.EVT_MULTIPLAYER_CLICK, handleMultiplayerClick);
			mainMenuR.removeEventListener(Const.EVT_CREDITS_CLICK, handleCreditsClick);
		}
		
		private function handleSinglePlayerClick(e:Event) : void
		{
			hideMainMenu();
			
			gamePlayR.loadMap(new TestMap2);
			
			addChild(gamePlayR);
		}
		
		private function handleMultiplayerClick(e:Event) : void
		{
			trace("handleMultiplayerClick");
		}
		
		private function handleCreditsClick(e:Event) : void
		{
			trace("handleCreditsClick");
		}

//################### Main Menu END.

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