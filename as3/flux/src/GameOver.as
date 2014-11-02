package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.TextEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.events.MouseEvent;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameOver extends MovieClip
	{
		private const backToMenuValue:String = "Back to menu";
		private const GAME_OVER:String = "Game Over!";
		private var stageRef:Stage;
		private var gameOverText:TextField;
		private var backToMenuButton:GameButton;
		private var finalScore:TextField;
		
		public function GameOver(stageRef:Stage) 
		{
			this.stageRef = stageRef;
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			var format:TextFormat = new TextFormat;
			format.size = 48;
			
			gameOverText = new TextField();
			gameOverText.defaultTextFormat = format;
			gameOverText.text =  this.GAME_OVER;
			gameOverText.textColor = 0xffffff;
			gameOverText.selectable = false;
			gameOverText.mouseEnabled = false;
			
			gameOverText.width = stageRef.stageWidth;
			gameOverText.height = stageRef.stageHeight;
			gameOverText.x = (stageRef.stageWidth / 2) - 100;
			gameOverText.y = (stageRef.stageHeight / 2) - 100;
			
			backToMenuButton = new GameButton(backToMenuValue);
			backToMenuButton.x = Calc.alignMiddle(gameOverText.x, gameOverText.textWidth, backToMenuButton.width);
			backToMenuButton.y = gameOverText.y + gameOverText.textHeight + 50;
			backToMenuButton.addEventListener(MouseEvent.CLICK, backToMenuHandler, false, 0, true);
			
			format.size = 18;
			
			finalScore = new TextField();
			finalScore.defaultTextFormat = format;
			finalScore.textColor = 0xffffff;
			finalScore.text = "";
			finalScore.width = 200;
			finalScore.selectable = false;
			finalScore.mouseEnabled = false;
			finalScore.x = gameOverText.x + 50;
			finalScore.y = gameOverText.y + gameOverText.textHeight + 10;
		}
		
		public function show(score:Number) : void
		{
			this.addChild(gameOverText);
			this.addChild(backToMenuButton);
			finalScore.text = "Final Score: " + String(score);
			this.addChild(finalScore);
		}
		
		public function hide() : void
		{
			if (this.contains(backToMenuButton))
			{
				this.removeChild(backToMenuButton);
			}
			
			if (this.contains(gameOverText))
			{
				this.removeChild(gameOverText);
			}
			
			if (this.contains(finalScore))
			{
				this.removeChild(finalScore);
			}
		}
		
		private function backToMenuHandler(e:Event) : void
		{
			dispatchEvent(new Event("backToMenu"));
		}
		
	}

}