package src
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class MonsterFactory 
	{
		private var gameStage:GameStage;
		private var monsterList:Vector.<Monster>;
		private var score:ScoreHUD;
		
		public function MonsterFactory (gameStageRef:GameStage, scoreR:ScoreHUD)
		{
			gameStage = gameStageRef;
			monsterList = new Vector.<Monster>;
			score = scoreR;
		}
		
		/*******************************************************************************************
		 * Public functions.
		 */
		
		/**
		 * @usage Create a slime at the given position (in tiles).
		 * @param	pw Horizontal position (in tiles).
		 * @param	ph Vertical position (in tiles).
		 * @param	checkpoints Where the monster needs to go.
		 */
		public function createSlime(pw:Number = 0, ph:Number = 0, checkpoints:Vector.<Point> = null, type:String = "") : void
		{
			if (type == Const.SLIME_NAME)
			{
				createSlimeP(pw * Const.TILE_W, ph * Const.TILE_H, new Slime(checkpoints));
			}
			else if (type == Const.WATER_SLIME_NAME)
			{
				trace("water slime");
				createSlimeP(pw * Const.TILE_W, ph * Const.TILE_H, new WaterSlime(checkpoints));
			}
		}
		
		/**
		 * @usage Use to check if the monster is inside the range of a tower.
		 * @return A copy of the monster's list.
		 */
		public function getMonsterListCopy() : Vector.<Monster>
		{
			return monsterList.concat();
		}
		
		/**
		 * @return The number of monsters inside the game.
		 */
		public function getMonsterListSize() : int
		{
			return monsterList.length;
		}
		
		
		/*******************************************************************************************
		 * Private functions.
		 */
		
		/**
		 * @usage Create a slime at the given position (in pixels).
		 * @param	x Horizontal position (in pixels).
		 * @param	y Vertical position (in pixels).
		 * @param	checkpoints Where the monster needs to go.
		 */
		private function createSlimeP(x:Number, y:Number, slime:Slime) : void
		{
			slime.x = x;
			slime.y = y;
			slime.addEventListener(Const.EVT_END_REACHED_STR, monsterReachedEnd, false, 0, true);
			slime.addEventListener(Const.EVT_MONSTER_KILLED, monsterKilled, false, 0, true);
			
			monsterList.push(slime as Monster);
			// Add  monster in 0, so it will not pass over the menu.
			gameStage.addChildBellowMenu(slime);
		}
		
		private function monsterKilled(e:Event) : void
		{
			var m:Monster = e.currentTarget as Monster;
			
			score.goldFromMonster = m.getGold();
			
			if (gameStage.contains(m))
			{
				gameStage.removeChild(m);
			}
			
			removeMonster(m);
		}
		
		private function monsterReachedEnd(e:Event) : void
		{
			var m:Monster = e.currentTarget as Monster;
			
			if (gameStage.contains(m))
			{
				gameStage.removeChild(m);
			}
			
			removeMonster(m);
			
			score.missed = 1;
			
			// Add only half of the gold, so the game keep balanced.
			score.goldFromMonster = m.getGold() / 2;
		}
		
		private function removeMonster(m:Monster) : void
		{
			m.removeEventListener(Const.EVT_END_REACHED_STR, monsterReachedEnd);
			m.removeEventListener(Const.EVT_MONSTER_KILLED, monsterReachedEnd);
			monsterList.splice(monsterList.indexOf(m), 1);
		}
	}
	
}