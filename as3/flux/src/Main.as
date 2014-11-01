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
	 * 
	 * 
	 * This game was based on this tutorial:
		 * http://code.tutsplus.com/tutorials/creating-flux-a-simple-flash-game-with-a-gravity-mechanic--active-11806
	 * 
	 * I gave a look in the game and started reading the tutorial, but I don't really liked the code and I set out to
	 * write the code by myself. Anyway, the forcefield mechanics was entirely based on the tutorial. Congrats for its
	 * author. :)
	 * 
	 * I'm new in AS language. You probably will find bad practices in my code.. as I have not documented any function
	 * correctly. Hope you can enjoy something.
	 * 
	 * 01/nov/2014.
	 * 
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
			
			gameOver = new GameOver(stage);
			energyFactory = new AstroFactory(stage);
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
			
			// Game over by asteroid collision.
			energyFactory.addEventListener("gameOver", gameEnding, false, 0, true);
			gameOver.addEventListener("restartGame", startGame, false, 0, true);
			
			// Freeze feature from http://mokshalstudios.wordpress.com/2011/01/22/easiest-way-to-pause-game-as3/
			stage.addEventListener(Event.ACTIVATE, yesFocus);
			stage.addEventListener(Event.DEACTIVATE, noFocus);
			
			stage.addChild(new Background(stage));
			stage.addChild(gameOver);
			
			this.startGame(null);
		}
		
		private function gameEnding(e:Event) : void
		{
			energyFactory.deactivate();
			energyFactory.removeAstros();
			
			player.removeEventListener("outOfEnergy", gameEnding);
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
		
		private function startGame(e:Event) : void
		{
			gameOver.hide();
			
			scoreHud = new ScoreHud(stage);
			scoreHud.x = 10;
			scoreHud.y = 10;
			player = new Ship(stage);
			
			energyFactory.activate(player, scoreHud);
			
			// Game over by out of energy.
			player.addEventListener("outOfEnergy", gameEnding, false, 0, true);
			
			stage.addChild(player);
			stage.addChild(scoreHud);
			
			energyFactory.activate(player, scoreHud);
			
			stage.stageFocusRect = false;
			stage.focus = player;
		}
		
		private function loop(e:Event) : void
		{
		}
		
		// Freeze feature from http://mokshalstudios.wordpress.com/2011/01/22/easiest-way-to-pause-game-as3/
		private function yesFocus(event:Event):void
		{
			stage.frameRate = stageFrameRate; // change this to whatever your normal frame rate is
		}

		// Freeze feature from http://mokshalstudios.wordpress.com/2011/01/22/easiest-way-to-pause-game-as3/
		private function noFocus(event:Event):void
		{
			stage.frameRate = 0; // freezes everything pretty much
		}
	}
	
}