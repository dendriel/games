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
		private var gameStage:MovieClip;
		private var monsterList:Vector.<Monster>;
		
		public function MonsterFactory (gameStageRef:MovieClip)
		{
			gameStage = gameStageRef;
			monsterList = new Vector.<Monster>;
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
		public function createSlime(pw:Number = 0, ph:Number = 0, checkpoints:Vector.<Point> = null) : void
		{
			createSlimeP(pw * Const.TILE_W, ph * Const.TILE_H, checkpoints);
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
		private function createSlimeP(x:Number = 0, y:Number = 0, checkpoints:Vector.<Point> = null) : void
		{
			var slime:Slime = new Slime(gameStage, checkpoints);
			
			slime.x = x;
			slime.y = y;
			slime.addEventListener(Const.EVT_END_REACHED_STR, monsterReachedEnd);
			
			monsterList.push(slime as Monster);
		}
		
		private function monsterReachedEnd(e:Event) : void
		{
			trace("old size: " + monsterList.length);
			monsterList.splice(monsterList.indexOf(e.currentTarget), 1);
			trace("new size: " + monsterList.length);
		}
	}
	
}