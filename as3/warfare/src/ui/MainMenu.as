package src.ui
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	import src.as3.media.Image;
	import src.as3.math.Calc;
	import src.as3.ui.GameButton;
	import src.language.GameLanguage;
	import src.*;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MainMenu extends MovieClip 
	{
		private const px:Number = 0;
		private const py:Number = 0;
		
		// Text.
		private var format:TextFormat;
		private var titleTxt:TextField;
		
		// Buttons.
		private var singlePlayerB:GameButton;
		private var multiPlayerB:GameButton;
		private var creditsB:GameButton;
		
		public function MainMenu() : void
		{
			x = px;
			y = py;
			drawSelf();
		}
		
		// Enable will refresh the buttons text.
		public function enable() : void
		{
			titleTxt.text = GameLanguage.lang.main_title;
			singlePlayerB.textValue = GameLanguage.lang.single_player_button;
			multiPlayerB.textValue = GameLanguage.lang.multiplayer_button;
			creditsB.textValue = GameLanguage.lang.credits_button;
			
			titleTxt.width = titleTxt.textWidth;
			titleTxt.height = titleTxt.textHeight;
			titleTxt.x = Calc.alignMiddle(0, Const.SCREEN_SIZE_W, titleTxt.width);
			
			singlePlayerB.addEventListener(MouseEvent.CLICK, handleSinglePlayerClick, false, 0, true);
			multiPlayerB.addEventListener(MouseEvent.CLICK, handleMultiplayerClick, false, 0, true);
			creditsB.addEventListener(MouseEvent.CLICK, handleCreditsClick, false, 0, true);
			
			//SoundLoader.playIntro();
		}
		
		public function disable() : void
		{
			singlePlayerB.removeEventListener(MouseEvent.CLICK, handleSinglePlayerClick);
			multiPlayerB.removeEventListener(MouseEvent.CLICK, handleMultiplayerClick);
			creditsB.removeEventListener(MouseEvent.CLICK, handleCreditsClick);
			
			//SoundLoader.stopIntro();
		}
		
		private function drawSelf() : void
		{			
			// Buttons.
			singlePlayerB = new GameButton();
			singlePlayerB.setPos(
				Calc.alignMiddle(0, Const.SCREEN_SIZE_W, singlePlayerB.width),
				Const.SCREEN_SIZE_H/2);
			
			multiPlayerB = new GameButton();
			multiPlayerB.setPos(
				Calc.alignMiddle(singlePlayerB.x, singlePlayerB.width, multiPlayerB.width),
				singlePlayerB.y + Const.MAIN_MENU_BUTTON_OFFSET);
			
			creditsB = new GameButton();
			creditsB.setPos(
				Calc.alignMiddle(multiPlayerB.x, multiPlayerB.width, creditsB.width),
				multiPlayerB.y + Const.MAIN_MENU_BUTTON_OFFSET);
				
			// Text.
			format = new TextFormat;
			format.size = 52;
			format.bold = true;
			
			titleTxt = new TextField();
			titleTxt.defaultTextFormat = format;
			titleTxt.textColor = 0xffffff;
			titleTxt.selectable = false;
			titleTxt.mouseEnabled = false;
			// Cant believe that the text strig must be the last to be set, otherwise the format won't work. (-_-)'
			titleTxt.y = Const.TITLE_VERTICAL_OFFSET;
				
			addChild(new MainMenuBg);
			addChild(titleTxt);
			addChild(singlePlayerB);
			addChild(multiPlayerB);
			addChild(creditsB);
		}
		
		private function handleSinglePlayerClick(e:MouseEvent) : void
		{
			dispatchEvent(new Event(Const.EVT_SINGLE_PLAYER_CLICK));
		}
		
		private function handleMultiplayerClick(e:MouseEvent) : void
		{
			dispatchEvent(new Event(Const.EVT_MULTIPLAYER_CLICK));
		}
		
		private function handleCreditsClick(e:MouseEvent) : void
		{
			dispatchEvent(new Event(Const.EVT_CREDITS_CLICK));
		}
	}
	
}