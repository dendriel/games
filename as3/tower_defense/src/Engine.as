package src
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import src.com.senocular.utils.KeyObject;
	
	[SWF(width="640", height="640", frameRate="30", backgroundColor="#ffffff")] //set project properties
	
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
		
		// Game Events Timers.
		private var gameStartLevelTimer:Timer;	// New level message displaying delay.
		private var gameEndLevelTimer:Timer;	// End level message displaying delay.
		private var gameLevelTransition:Timer;	// Transition image displaying delay.
		
		public function Engine()
		{
			// Use a movie clip instead of directly accessing the stage.
			// As i'm creating objects directly on stage.. we need to take care of it when needed. :/
			gameStage = new GameStage(stage);
			
			// Configure timer.
			gameStartLevelTimer = new Timer(Const.GAME_EVENT_DELAY, 1);
			gameStartLevelTimer.addEventListener(TimerEvent.TIMER, loadLevelPlay, false, 0, true);
			gameEndLevelTimer = new Timer(Const.GAME_EVENT_DELAY, 1);
			gameEndLevelTimer.addEventListener(TimerEvent.TIMER, nextLevelPlay, false, 0, true);
			gameLevelTransition = new Timer(Const.GAME_EVENT_DELAY, 1);
			gameLevelTransition.addEventListener(TimerEvent.TIMER, gamePlay, false, 0, true);
			
			// Load sounds.
			SoundLoader.init();
			
			key = new KeyObject(stage);
			
			// It starts 2 tiles above stage origin.
			gameStage.origin.y = (Const.TILE_H)
			gameStage.origin.x = 0;
			// It ends 2 tiles before stage.
			gameStage.size.y = stage.stageHeight - (Const.TILE_H * 2);
			gameStage.size.x = stage.stageWidth;
			
			stage.addChild(gameStage);
			
			score = new ScoreHUD();
			score.addEventListener(Const.EVT_GAME_OVER, handleGameOver, false, 0, true);
			
			monsterFactory = new MonsterFactory(gameStage, score);
			towerFactory = new TowerFactory(gameStage, monsterFactory);
			levels = new Vector.<Level>;
			menuHandler = new MenuUIHandler(gameStage, key, towerFactory, score);
			score.menuHandler = menuHandler;
			
			menuHandler.visible = false;
			gameStage.menu = menuHandler;
			
			addLevels();
		}
		
		private function addLevels() : void
		{
			// We can have a "levels holder" / stage.
			levels.push(new Level5(monsterFactory));
			levels.push(new Level4(monsterFactory));
			levels.push(new Level3(monsterFactory));
			levels.push(new Level2(monsterFactory));
			levels.push(new Level1(monsterFactory));
		}
		
		public function gameIntroWrapper(e:MouseEvent) : void
		{
			btnBackToMainMenu.removeEventListener(MouseEvent.CLICK, gameIntroWrapper);
			addLevels();
			gotoAndStop(Const.GAME_INTRO);
		}
		
		public function gameIntro(e:TimerEvent) : void
		{
			// Wait until engine is fully loaded.
			if (levels.length  > 0) {
				mainMenuUI.btnStartGame.addEventListener(MouseEvent.CLICK, gamePlayWrapper, false, 0 , true);
			}
			else {
				// I don't know if leaving the Timer ref will be a problem (leak? garbage collector?)
				var waitEngineLoad:Timer = new Timer(1000, 1);
				waitEngineLoad.addEventListener(TimerEvent.TIMER, gameIntro, false, 0, true);
				waitEngineLoad.start();
			}
		}
		
		public function gameWin() : void
		{
			score.level = 0;
			menuHandler.visible = false;
			SoundLoader.playVictory1();
			btnBackToMainMenu.addEventListener(MouseEvent.CLICK, gameIntroWrapper, false, 0, true);
		}
		
		private function handleGameOver(e:Event) : void
		{
			gotoAndStop(Const.GAME_OVER);
		}
		
		// No game over condition was implemented.
		public function gameOver() : void
		{
			// STOP THE GAME HERE.
			currLevel.stopLevel();
			unloadLevel1();
			unloadLevel2();
			score.level = 0;
			SoundLoader.playGameOver();
			
			menuHandler.visible = false;
			btnBackToMainMenu.addEventListener(MouseEvent.CLICK, gameIntroWrapper, false, 0, true);
		}
		
		private function nextWave(e:Event) : void
		{
			score.wave = 1;
		}
		
		private function gamePlayWrapper(e:MouseEvent) : void
		{
			mainMenuUI.btnStartGame.removeEventListener(MouseEvent.CLICK, gamePlayWrapper);
			gamePlay(null);
		}
		
		public function gamePlay(e:TimerEvent) : void
		{
			// While we still have levels left.
			if ( levels.length > 0)
			{
				menuHandler.visible = true;
				score.level++;				
				currLevel = levels.pop();
				score.reload();
				loadLevel();
			}
			// Player could make through all levels.
			else
			{
				gotoAndStop(Const.GAME_WIN);
			}
		}
		
		/**
		 * Start the level in currLevel variable.
		 */
		private function loadLevel() : void
		{
			gotoAndStop(currLevel.getMapLabel());
			
			gameStage.addChildBellowMenu(currLevel.getPlaceAreaRef());
			
			currLevel.addEventListener(Const.EVT_LEVEL_END, nextLevel, false, 0, true);
			currLevel.addEventListener(Const.EVT_NEXT_WAVE, nextWave, false, 0, true);
			
			score.gold = currLevel.startGold;
			
			menuHandler.setGameEventText(Const.LEVEL_START_TEXT);
			currLevel.displayPlaceArea();
			// Wait some time so the message can be read by the user.
			gameStartLevelTimer.start();
		}
		
		/**
		 * Finish loading the level.
		 */
		private function loadLevelPlay(e:TimerEvent) : void
		{
			currLevel.hidePlaceArea();
			menuHandler.setGameEventText("");
			
			menuHandler.loadLevel(currLevel);
			currLevel.playLevel();
			gameStage.stageR.stageFocusRect = false;
			gameStage.stageR.focus = gameStage;
		}
		
		/**
		 * When a level finalize, call gamePlay again.
		 */
		private function nextLevel(e:Event) : void
		{
			unloadLevel1();
			
			SoundLoader.playVictory();
			menuHandler.setGameEventText(Const.LEVEL_CLEARED_TEXT);
			// Wait some time so the message can be read by the user.
			gameEndLevelTimer.start();
		}
		
		private function unloadLevel1() : void
		{
			currLevel.removeEventListener(Const.EVT_NEXT_WAVE, nextWave);
			currLevel.removeEventListener(Const.EVT_LEVEL_END, nextLevel);
			
			if (gameStage.contains(currLevel.getPlaceAreaRef()))
			{
				gameStage.removeChild(currLevel.getPlaceAreaRef());
			}
			
			menuHandler.unloadGameUI();
		}
		
		private function nextLevelPlay(e:TimerEvent) : void
		{
			unloadLevel2();
			
			menuHandler.setGameEventText("");
			gotoAndStop(Const.GAME_LEVEL_TRANSITION);
			gameLevelTransition.start();
			SoundLoader.playNextLevel();
		}
		
		private function unloadLevel2() : void
		{
			towerFactory.removeAllTowers();
		}

	}
	
}
