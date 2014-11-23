package src
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.geom.Point;
	import src.com.senocular.utils.KeyObject;
	
	[SWF(width="640", height="640", frameRate="30", backgroundColor="#00FFFF")] //set project properties
	
	public class Engine extends MovieClip
	{
		private var gameStage:GameStage;
		private var monsterFactory:MonsterFactory;
		private var towerFactory:TowerFactory;
		private var menuHandler:MenuUIHandler;
		private var key:KeyObject;
		private var levels:Vector.<Level>;
		private var currLevel:Level;
		private var score:ScoreHUD;

		public function Engine()
		{
			// Use a movie clip instead of directly accessing the stage.
			// As i'm creating objects directly on stage.. we need to take care of it when needed. :/
			gameStage = new GameStage(stage);
			
			// Load sounds.
			SoundLoader.init();
			
			key = new KeyObject(stage);
			
			// It starts 2 tiles above stage origin.
			gameStage.origin.y = (Const.TILE_H * 2)
			gameStage.origin.x = 0;
			// It ends 2 tiles before stage.
			gameStage.size.y = stage.stageHeight - (Const.TILE_H * 4);
			gameStage.size.x = stage.stageWidth;
			
			stage.addChild(gameStage);

			score = new ScoreHUD;
			monsterFactory = new MonsterFactory(gameStage, score);
			towerFactory = new TowerFactory(gameStage, monsterFactory);
			levels = new Vector.<Level>;
			menuHandler = new MenuUIHandler(gameStage, key, towerFactory, score);
			
			levels.push(new Level1(monsterFactory));
			levels.push(new Level2(monsterFactory));
			levels.push(new Level3(monsterFactory));

		}
		
		public function gameIntro() : void
		{
			gotoAndStop(Const.GAME_PLAY);
		}
		
		public function gamePlay() : void
		{
			// While we still have levels left.
			if ( levels.length > 0)
			{
				score.level++;
				score.resetWave();
				currLevel = levels.pop();
				loadLevel();
			}
			// Player could make through all levels.
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
		
		public function loadMenu() : void
		{
			trace("loadMenu");
			menuHandler.loadGameUI(mcMenuUI);
			
			score.load(menuHandler);
		}
		
		private function nextWave(e:Event) : void
		{
			trace("increase wave");
			score.wave = 1;
		}
		
		/**
		 * Start the level in currLevel variable.
		 */
		private function loadLevel() : void
		{
			gotoAndStop(currLevel.getMapLabel());
			currLevel.addEventListener(Const.EVT_LEVEL_END, nextLevel, false, 0, true);
			currLevel.addEventListener(Const.EVT_NEXT_WAVE, nextWave, false, 0, true);
			currLevel.playLevel();
			gameStage.stageR.stageFocusRect = false;
			gameStage.stageR.focus = gameStage;
		}
		
		/**
		 * When a level finalize, call gamePlay again.
		 */
		private function nextLevel(e:Event) : void
		{
			currLevel.removeEventListener(Const.EVT_NEXT_WAVE, nextWave);
			currLevel.removeEventListener(Const.EVT_LEVEL_END, nextLevel);
			towerFactory.removeAllTowers();
			menuHandler.unloadGameUI();
			gotoAndStop(Const.GAME_PLAY);
		}

	}
	
}
