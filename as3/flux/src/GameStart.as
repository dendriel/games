package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameStart extends MovieClip
	{
		private const GAME_NAME:String = "Flux"
		private var stageRef:Stage;
		private var gameNameText:TextField;
		
		private const startButtonValue:String = "Start Game";
		private var startButton:GameButton;
		private const controlButtonValue:String = "Controls"
		private var controlButton:GameButton;
		
		public function GameStart(stageRef:Stage) 
		{
			this.stageRef = stageRef;
			
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			var format:TextFormat = new TextFormat;
			format.size = 52;
			
			gameNameText = new TextField();
			gameNameText.defaultTextFormat = format;
			gameNameText.text =  this.GAME_NAME;
			gameNameText.textColor = 0xffffff;
			gameNameText.selectable = false;
			gameNameText.mouseEnabled = false;
			
			gameNameText.width = stageRef.stageWidth;
			gameNameText.height = stageRef.stageHeight;
			gameNameText.x = (stageRef.stageWidth / 2) - 50;
			gameNameText.y = (stageRef.stageHeight / 2) - 200;
			
			startButton = new GameButton(startButtonValue);
			startButton.setPos(Calc.alignMiddle(gameNameText.x,
												gameNameText.textWidth,
												startButton.width),
											gameNameText.y + 100);
			startButton.addEventListener(MouseEvent.CLICK, startGameHandler, false, 0, true);
			
			controlButton = new GameButton(controlButtonValue);
			controlButton.setPos(Calc.alignMiddle(startButton.x,
													startButton.width,
													controlButton.width),
													startButton.y + 40);
		}
		
		public function show() : void
		{
			this.addChild(gameNameText);
			this.addChild(startButton);
			this.addChild(controlButton);
		}
		
		public function hide() : void
		{
			if (this.contains(gameNameText))
			{
				this.removeChild(gameNameText);
			}
			
			if (this.contains(startButton))
			{
				this.removeChild(startButton);
			}
			
			if (this.contains(controlButton))
			{
				this.removeChild(controlButton);
			}
		}
		
		private function startGameHandler(e:MouseEvent) : void
		{
			dispatchEvent(new Event("startGameClicked"));
		}
	}

}