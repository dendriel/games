package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.text.TextField;
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameStart extends MovieClip
	{
		private const GAME_NAME:String = "Flux"
		private var stageRef:Stage;
		private var gameNameText:TextField;
		
		public function GameStart(stageRef:Stage) 
		{
			this.stageRef = stageRef;
			drawSelf();
		}
		
		private function drawSelf() : void
		{
			var format:TextFormat = new TextFormat;
			format.size = 48;
			
			gameNameText = new TextField();
			gameNameText.defaultTextFormat = format;
			gameNameText.text =  this.GAME_NAME;
			gameNameText.textColor = 0xffffff;
			gameNameText.selectable = false;
			gameNameText.mouseEnabled = false;
			
			gameNameText.width = stageRef.stageWidth;
			gameNameText.height = stageRef.stageHeight;
			gameNameText.x = (stageRef.stageWidth / 2) - 100;
			gameNameText.y = (stageRef.stageHeight / 2) - 100;
		}
	}

}