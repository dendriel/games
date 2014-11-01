package  
{
	import flash.display.Sprite;
	import flash.display.Stage;
	import flash.events.Event;
	/**
	 * ...
	 * @author Vitor Rozsa
	 * @usage Generate Energy objects through this class.
	 */
	public class AstroFactory extends Sprite
	{
		private var stageRef:Stage;
		private var shipRef:Ship;
		private var scoreHud:ScoreHud;
		private var activeFactory:Boolean;
		private var energyListGood:Vector.<Energy>;
		private var energyListBad:Vector.<Energy>;
		private var asteroidList:Vector.<Asteroid>;
		
		public function AstroFactory(stageRef:Stage, shipRef:Ship, scoreHud:ScoreHud, activeFactory:Boolean = true) 
		{
			this.stageRef = stageRef;
			this.shipRef = shipRef;
			this.scoreHud = scoreHud;
			energyListGood = new Vector.<Energy>;
			energyListBad = new Vector.<Energy>;
			asteroidList = new Vector.<Asteroid>;
			
			// The Factory starts initialized.
			this.activeFactory = activeFactory;
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
		}
		
		private function loop(e:Event) : void
		{
			if (activeFactory != true)
			{
				return;
			}
			
			// rever			
			if (Math.random() > 0.9)
			{
				createEnergyGood();
			}
			
			if (Math.random() > 0.95)
			{
				createEnergyBad();
			}
			
			if (Math.random() > 0.98)
			{
				createAsteroid();
			}
		}
		
		public function deactivate() : void
		{
			activeFactory = false;
		}
		
		/*
		 * We remove the ship and scoreHud in the game over, then re-create then
		 * in restart. So we need to update its references here.
		 */
		public function activate(shipRef:Ship, scoreHudRef:ScoreHud) : void
		{
			this.shipRef = shipRef;
			this.scoreHud = scoreHudRef;
			activeFactory = true;
		}
		
		private function updateScore(e:Event) : void
		{
			scoreHud.update(e.target.scoreValue);
		}
		
		private function raiseGameOver(e:Event) : void
		{
			// Player collided with asteroid. Game Over.
			dispatchEvent(new Event("gameOver"));
		}
		
		public function removeAstros() : void
		{
			var energy:Energy;
			var asteroid:Asteroid;
			var energyList_new:Vector.<Energy>;
			var asteroidList_new:Vector.<Asteroid>;
			
			// Create a copy of the vector, because the own energy will remove itself from with the original vector.
			energyList_new = energyListGood.concat();	
			while ((energy = energyList_new.pop()) != null)
			{
				energy.removeSelf();
			}
			
			energyList_new = energyListBad.concat();	
			while ((energy = energyList_new.pop()) != null)
			{
				energy.removeSelf();
			}
			
			asteroidList_new = asteroidList.concat();
			while ((asteroid = asteroidList_new.pop()) != null)
			{
				asteroid.removeSelf();
			}
		}
		
		public function createEnergyGood() : void
		{
			var energy:Energy = new Energy(stageRef, shipRef);
			energy.addEventListener(Event.REMOVED_FROM_STAGE, destroyEnergyGood, false, 0, true);
			energy.addEventListener("updateScore", updateScore, false, 0, true);
			
			energyListGood.push(energy);
		}
		
		private function destroyEnergyGood(e:Event) : void
		{
			energyListGood.splice(energyListGood.indexOf(e.currentTarget), 1);
		}
		
		public function createEnergyBad() : void
		{
			var energy:Energy = new Energy(stageRef, shipRef, Energy.BAD_ENERGY_COLOR, Energy.BAD_ENERGY_VALUE, Energy.BAD_ENERGY_SCORE_VALUE);
			energy.addEventListener(Event.REMOVED_FROM_STAGE, destroyEnergyBad, false, 0, true);
			
			energyListBad.push(energy);
		}
		
		private function destroyEnergyBad(e:Event) : void
		{
			energyListBad.splice(energyListBad.indexOf(e.currentTarget), 1);
		}
		
		public function createAsteroid() : void
		{
			var asteroid:Asteroid = new Asteroid(stageRef, shipRef);
			asteroid.addEventListener(Event.REMOVED_FROM_STAGE, destroyAsteroid, false, 0, true);
			asteroid.addEventListener("collided", raiseGameOver, false, 0, true);
			
			asteroidList.push(asteroid);
		}
		
		private function destroyAsteroid(e:Event) : void
		{
			asteroidList.splice(asteroidList.indexOf(e.currentTarget), 1);
		}
		
	}

}