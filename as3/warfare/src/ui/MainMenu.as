package src.ui
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import src.as3.media.Image;
	import src.as3.math.Calc;
	import src.as3.ui.GameButton;
	import src.MediaSource;
	import src.Const;
	import src.GameStage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MainMenu extends MovieClip 
	{
		private const px:Number = 0;
		private const py:Number = 0;
		
		// Text.
		private var titleTxt:TextField;
		
		// Buttons.
		private var singlePlayerB:GameButton;
		private var multiPlayerB:GameButton;
		private var creditsB:GameButton;
		
		public function MainMenu() : void
		{
			this.x = px;
			this.y = py;
			this.drawSelf();
		}
		
		private function drawSelf() : void
		{			
			// Buttons.
			singlePlayerB = new GameButton(Const.SINGLE_PLAYER_S);
			singlePlayerB.setPos(
				Calc.alignMiddle(0, Const.SCREEN_SIZE_W, singlePlayerB.width),
				Const.SCREEN_SIZE_H/2);
			
			multiPlayerB = new GameButton(Const.MULTI_PLAYER_S);
			multiPlayerB.setPos(
				Calc.alignMiddle(singlePlayerB.x, singlePlayerB.width, multiPlayerB.width),
				singlePlayerB.y + Const.MAIN_MENU_BUTTON_OFFSET);
			
			creditsB = new GameButton(Const.CREDITS_S);
			creditsB.setPos(
				Calc.alignMiddle(multiPlayerB.x, multiPlayerB.width, creditsB.width),
				multiPlayerB.y + Const.MAIN_MENU_BUTTON_OFFSET);
				
			// Text.
			var format = new TextFormat;
			format.size = 52;
			format.bold = true;
			
			titleTxt = new TextField();
			titleTxt.defaultTextFormat = format;
			titleTxt.textColor = 0xffffff;
			titleTxt.selectable = false;
			titleTxt.mouseEnabled = false;
			// Cant believe that the text strig must be the last to be set, otherwise the format won't work. (-_-)'
			titleTxt.text = Const.MAIN_MENU_TITLE;
			titleTxt.width = titleTxt.textWidth;
			titleTxt.height = titleTxt.textHeight;
			
			titleTxt.x = Calc.alignMiddle(0, Const.SCREEN_SIZE_W, titleTxt.width);
			titleTxt.y = Const.TITLE_VERTICAL_OFFSET;
				
			//this.addChild(bg);
			this.addChild(new MainMenuBg);
			this.addChild(singlePlayerB);
			this.addChild(multiPlayerB);
			this.addChild(creditsB);
		}
	}
	
}