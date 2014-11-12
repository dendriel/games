package src
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.geom.Point;
	
	[SWF(width="640", height="640", frameRate="30", backgroundColor="#00FFFF")] //set project properties
	
	public class Engine extends MovieClip
	{
		private var gameStage:GameStage;
		private var monsterFactory:MonsterFactory;
		private var towerFactory:TowerFactory;
		private var levels:Vector.<Level>;
		private var currLevel:Level;

		public function Engine()
		{
			// Use a movie clip instead of directly accessing the stage.
			gameStage = new GameStage;
			
			// Load sounds.
			SoundLoader.init();
			
			// It starts 2 tiles above stage origin.
			gameStage.origin.y = (Const.TILE_H * 2)
			gameStage.origin.x = 0;
			// It ends 2 tiles before stage.
			gameStage.size.y = stage.stageHeight - (Const.TILE_H * 4);
			gameStage.size.x = stage.stageWidth;
			
			stage.addChild(gameStage);

			monsterFactory = new MonsterFactory(gameStage);
			towerFactory = new TowerFactory(gameStage, monsterFactory);
			levels = new Vector.<Level>;
			
			//levels.push(new Level1(monsterFactory));
			levels.push(new Level2(monsterFactory));
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
		
		/**
		 * Start the level in currLevel variable.
		 */
		private function loadLevel() : void
		{
			gotoAndStop(currLevel.getMapLabel());
			currLevel.addEventListener(Const.EVT_LEVEL_END, nextLevel, false, 0, true);
			currLevel.playLevel();
			
			towerFactory.createFireTower(8, 6);
		}
		
		/**
		 * When a level finalize, call gamePlay again.
		 */
		private function nextLevel(e:Event) : void
		{
			currLevel.removeEventListener(Const.EVT_LEVEL_END, nextLevel);
			towerFactory.removeAllTowers();
			gotoAndStop(Const.GAME_PLAY);
		}

	}
	
}
