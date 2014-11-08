package src
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.geom.Point;
	
	[SWF(width="640", height="640", frameRate="30", backgroundColor="#00FFFF")] //set project properties
	
	public class Engine extends MovieClip
	{
		private var gameStage:MovieClip;
		private var monsterFactory:MonsterFactory;
		private var levels:Vector.<ILevel>;
		private var currLevel:ILevel;

		public function Engine()
		{
			// Use a movie clip instead of directly accessing the stage.
			gameStage = new MovieClip;
			stage.addChild(gameStage);

			monsterFactory = new MonsterFactory(gameStage);
			levels = new Vector.<ILevel>;
			
			levels.push(new Level1(monsterFactory));
		}
		
		public function gameIntro() : void
		{
			gotoAndStop(Const.GAME_PLAY);
		}
		
		public function gamePlay() : void
		{
			if ( levels.length > 0)
			{
				currLevel = levels.pop();
				loadLevel();
			}
			else
			{
				gotoAndStop(Const.GAME_WIN);
			}
		}
		
		public function gameWin() : void
		{
			
		}
		
		public function gameOver() : void
		{
			
		}
		
		private function loadLevel() : void
		{
			gotoAndStop(currLevel.getMapLabel());
			(currLevel as MovieClip).addEventListener(Const.EVT_LEVEL_END, nextLevel, false, 0, true);
			currLevel.playLevel();
		}
		
		private function nextLevel(e:Event) : void
		{
			(currLevel as MovieClip).removeEventListener(Const.EVT_LEVEL_END, nextLevel);
			gotoAndStop(Const.GAME_PLAY);
		}

	}
	
}
