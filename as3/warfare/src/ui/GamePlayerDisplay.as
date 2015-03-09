package src.ui
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import src.GamePlay;
	import src.GamePlayer;
	import src.language.GameLanguage;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GamePlayerDisplay extends MovieClip
	{
		// Constants.
		private var firstColumnPosX:int = 0;
		private var nickTxtPosY:int = 0;
		private var textVerticalOffset:int = 16;
		
		// Text.
		private var nickTxt:TextField;
		private var goldTxt:TextField;
		
		private var _player:GamePlayer;
		
		public function GamePlayerDisplay(px:int = 0, py:int = 0)
		{
			x = px;
			y = py;
			
			drawSelf();
		}
		
		public function drawSelf() : void
		{
			nickTxt = GameTextFormat.newDisplayTextTitle(firstColumnPosX, nickTxtPosY);			
			goldTxt = GameTextFormat.newDisplayTextTitle(firstColumnPosX, (nickTxt.y + textVerticalOffset) );
			
			addChild(nickTxt);
			addChild(goldTxt);
		}
		
		public function loadPlayer(player:GamePlayer) : void
		{
			_player = player;
			update();
		}
		
		public function update() : void
		{
			if (_player == null)
			{
				return;
			}
			nickTxt.text = String(_player.nick);
			goldTxt.text = GameLanguage.lang.gold_str + ": " + String(_player.gold);
		}
	}
	
}