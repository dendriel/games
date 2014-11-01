package 
{
	import flash.display.SimpleButton;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.text.TextField;
	
	[SWF(width="600", height="600", frameRate="30", backgroundColor="#00FFFF")] //set project properties
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Main extends Sprite 
	{
		private const stageFrameRate:Number = 30;
		private var player:Ship;
		private var energyFactory:AstroFactory;
		private var gameOver:GameOver;
		private var scoreHud:ScoreHud;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			
			scoreHud = new ScoreHud(stage);
			scoreHud.x = 10;
			scoreHud.y = 10;
			gameOver = new GameOver(stage);
			player = new Ship(stage);
			energyFactory = new AstroFactory(stage, player, scoreHud);
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
			
			energyFactory.addEventListener("gameOver", gameEnding, false, 0, true);
			gameOver.addEventListener("restartGame", restartGame, false, 0, true);
			
			// testing stuff!
			player.addEventListener("action", gameEnding, false, 0, true);
			
			// Freeze feature from http://mokshalstudios.wordpress.com/2011/01/22/easiest-way-to-pause-game-as3/
			stage.addEventListener(Event.ACTIVATE, yesFocus); //check if focus is there
			stage.addEventListener(Event.DEACTIVATE, noFocus); // check if focus is not there
			
			stage.addChild(new Background(stage));
			stage.addChild(player);
			stage.addChild(gameOver);
			stage.addChild(scoreHud);
		}
		
		private function gameEnding(e:Event) : void
		{
			energyFactory.deactivate();
			energyFactory.removeAstros();
			
			if (stage.contains(player))
			{
				stage.removeChild(player);
			}
			
			gameOver.show(scoreHud.getScore());
			
			if (stage.contains(scoreHud))
			{
				stage.removeChild(scoreHud);
			}
		}
		
		private function restartGame(e:Event) : void
		{
			gameOver.hide();
			player = new Ship(stage);
			scoreHud = new ScoreHud(stage);
			
			energyFactory.activate(player, scoreHud);
			stage.addChild(player);
			stage.addChild(scoreHud);
			
			stage.stageFocusRect = false;
			stage.focus = player;
		}
		
		private function loop(e:Event) : void
		{
		}
		
		// Freeze feature from http://mokshalstudios.wordpress.com/2011/01/22/easiest-way-to-pause-game-as3/
		function yesFocus(event:Event):void
		{
			stage.frameRate = stageFrameRate; // change this to whatever your normal frame rate is
			//pauseScreen_mc.x = 5000; // remove pause screen
		}

		// Freeze feature from http://mokshalstudios.wordpress.com/2011/01/22/easiest-way-to-pause-game-as3/
		function noFocus(event:Event):void
		{
			stage.frameRate = 0; // freezes everything pretty much
			//pauseScreen_mc.x = 0; // place the pause screen in screen
			//pauseScreen_mc.y = 0; // place the pause screen in screen
		}
	}
	
}