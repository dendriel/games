package 
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.ui.Keyboard;
	import flash.utils.Timer;
	import senocular.utils.KeyObject;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class Ship extends MovieClip 
	{
		private const powerMax:Number = 200;
		private const drawRadius:Number = 35;
		private const drawInnerRadius:Number = 25;
		private const moveSpeed:Number = 6;
		private const initialPower:Number = 20;
		private var currPower:Number;
		private var stageRef:Stage;
		private var key:KeyObject;
		private var powerText:TextField;
		
		// Force field related variables.
		private const gravityPushingDefault:Boolean = false;
		private const forceFieldRangeMin:Number = 60;
		private const forceFieldRangeMax:Number = 200;
		private const forceFieldRangeDefault:Number = 100;
		private var forceFieldRange:Number;
		private var forceField:Shape;
		private var gravityPushing:Boolean;
		
		// Force field timer variables.
		private const changeForceFieldDelay:Number = 2000; // 2 seconds.
		private var changeForceFieldTimer:Timer;
		private var canChangeForceField:Boolean;
		
		// Continuous loss of power timer.
		private const powerLossDelay:Number = 1000; // 1 second.
		private const powerLossValue:Number = -1;
		private var powerLossTimer:Timer;
		
		private var speedBoostUsed:Boolean;
		
		public function Ship(stageRef:Stage)
		{
			this.stageRef = stageRef;
			key = new KeyObject(stageRef);
			powerText = new TextField;
			currPower = initialPower;
			gravityPushing = gravityPushingDefault;
			forceFieldRange = forceFieldRangeDefault;
			drawSelf();
			
			speedBoostUsed = false;
			
			x = stageRef.stageWidth / 2;
			y = stageRef.stageHeight - 100;
			
			canChangeForceField = false;
			changeForceFieldTimer = new Timer(changeForceFieldDelay, 1);
			changeForceFieldTimer.addEventListener(TimerEvent.TIMER, changeForceFieldHandler, false, 0, true);
			changeForceFieldTimer.start();
			
			powerLossTimer = new Timer(powerLossDelay);
			powerLossTimer.addEventListener(TimerEvent.TIMER, powerLossHandler, false, 0, true);
			powerLossTimer.start();
			
			addEventListener(Event.ENTER_FRAME, loop, false, 0, true);
		}
		
		private function drawSelf() : void
		{
			forceField = new Shape();
			updateForceField();
			this.addChild(forceField);
			
			graphics.beginFill(0x7ebff1);
            graphics.drawCircle(0, 0, drawInnerRadius);
            graphics.drawCircle(0, 0, drawRadius);
			graphics.endFill();
			
			var format:TextFormat = new TextFormat;
			format.size = 18;
			
			powerText.defaultTextFormat = format;
			powerText.x = -16;
			powerText.y = -13;
			powerText.textColor = 0xffffff;
			updatePower();
			this.addChild(powerText);
		}
		
		private function updateForceField(value:Number = 0) : void
		{
			forceFieldRange += value;
			
			forceFieldRange = Calc.clipGT(forceFieldRange, forceFieldRangeMax);
			forceFieldRange = Calc.clipLT(forceFieldRange, forceFieldRangeMin);
			
			forceField.graphics.clear();
			
			forceField.graphics.beginFill(0xCCCCCC, 0.1);
			if (canChangeForceField == false)
			{
				forceField.graphics.lineStyle(1,0xffffff);
			}
			forceField.graphics.drawCircle(0, 0, forceFieldRange);
			forceField.graphics.endFill();
		}
		
		private function changeForceFieldHandler(e:TimerEvent) : void
		{
			canChangeForceField = true;
			updateForceField();
		}
		
		private function powerLossHandler(e:TimerEvent) : void
		{
			var totalLoss:Number = powerLossValue;
			// Double the power loss if the player is boosting the ship speed.
			if (speedBoostUsed == true)
			{
				totalLoss *= 2;
				speedBoostUsed = false;
			}

			addEnergy(totalLoss);
		}
		
		public function addEnergy(value:Number) : void
		{
			currPower += value;
			currPower = Calc.clipGT(currPower, powerMax);
			currPower = Calc.clipLT(currPower, 0);
			
			updatePower();
			
			if (currPower == 0)
			{
				SoundLoader.playOutOfPowerSound();
				removeSelf();
			}
		}
		
		
		public function collided() : void
		{
			SoundLoader.playExplosionSound();
			removeSelf();
		}
		
		private function removeSelf() : void
		{
			removeEventListener(Event.ENTER_FRAME, loop);
			changeForceFieldTimer.stop();
			changeForceFieldTimer.removeEventListener(TimerEvent.TIMER, changeForceFieldHandler);
			powerLossTimer.stop();
			powerLossTimer.removeEventListener(TimerEvent.TIMER, powerLossHandler);
			// Main class added the Ship and it will remove the ship.
			dispatchEvent(new Event("playerKilled"));
		}
		
		private function updatePower() : void
		{
			powerText.text = String(currPower);
		}
		
		private function loop(e:Event) : void
		{
			// If SHIFT key is pressed, we will speed up the ship (and consume more energy).
			var speedUp:Boolean = key.isDown(Keyboard.SHIFT);
			if (speedUp == true)
			{
				speedBoostUsed = true;
			}
			
			if (key.isDown(Keyboard.LEFT) || key.isDown(Keyboard.A))
			{
				x -= moveSpeed * ( (speedUp)? 2 : 1);
				x = Calc.clipLT(x, drawRadius);
			}
			else if (key.isDown(Keyboard.RIGHT) || key.isDown(Keyboard.D))
			{
				x += moveSpeed * ( (speedUp)? 2 : 1);
				x = Calc.clipGT(x, (stageRef.stageWidth - drawRadius) );
			}
			
			if (key.isDown(Keyboard.UP) || key.isDown(Keyboard.W))
			{
				updateForceField(1);
			}
			else if (key.isDown(Keyboard.DOWN) || key.isDown(Keyboard.S))
			{
				updateForceField( -1);
			}
			
			// action key.
			if (key.isDown(Keyboard.SPACE) && (canChangeForceField == true) )
			{
				gravityPushing = !gravityPushing;
				canChangeForceField = false;
				updateForceField();
				changeForceFieldTimer.start();
			}
		}
		
		public function getRadius() : Number
		{
			return drawRadius;
		}
		
		public function getGravityPushing() : Boolean
		{
			return gravityPushing;
		}
		
		public function getForceFieldRange() : Number
		{
			return forceFieldRange;
		}
	}
	
}