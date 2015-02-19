package src.ui
{
	import flash.display.MovieClip;
	import src.as3.media.Image;
	import src.as3.ui.GameButton;
	import src.MediaSource;
	import src.Const;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MainMenu extends MovieClip 
	{
		private const px:Number = 0;
		private const py:Number = 0;
		
		// Background.
		private var bg:Image;
		
		// Buttons.
		private var singlePlayerB:GameButton;
		private var multiPlayerB:GameButton;
		private var creditsB:GameButton;
		
		public function MainMenu() : void
		{
			this.x = px;
			this.y = py;
			
			bg = new Image(MediaSource.MAIN_MENU_BG_LOC,
							MediaSource.MAIN_MENU_W,
							MediaSource.MAIN_MENU_H);
			
			singlePlayerB = new GameButton(Const.SINGLE_PLAYER_S, 0, 0);
			multiPlayerB = new GameButton(Const.MULTI_PLAYER_S, 0, 0);
			creditsB = new GameButton(Const.CREDITS_S, 0, 0);
			
			this.addChild(bg);
			this.addChild(singlePlayerB);
			this.addChild(multiPlayerB);
			this.addChild(creditsB);
		}
	}
	
}