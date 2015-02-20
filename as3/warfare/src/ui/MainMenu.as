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
		
		public function enable() : void
		{
			singlePlayerB.addEventListener(MouseEvent.CLICK, handleSinglePlayerClick, false, 0, true);
			multiPlayerB.addEventListener(MouseEvent.CLICK, handleMultiplayerClick, false, 0, true);
			creditsB.addEventListener(MouseEvent.CLICK, handleCreditsClick, false, 0, true);
		}
		
		public function disable() : void
		{
			singlePlayerB.removeEventListener(MouseEvent.CLICK, handleSinglePlayerClick);
			multiPlayerB.removeEventListener(MouseEvent.CLICK, handleMultiplayerClick);
			creditsB.removeEventListener(MouseEvent.CLICK, handleCreditsClick);
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
			this.addChild(titleTxt);
			this.addChild(singlePlayerB);
			this.addChild(multiPlayerB);
			this.addChild(creditsB);
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