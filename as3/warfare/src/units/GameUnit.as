package src.units
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.utils.Timer;
	import src.IElementInfo;
	import src.ElementType;
	import src.Const;
	import src.as3.math.graph.*;
	import src.as3.math.Calc;
	import src.tiles.ConstTile;
	import src.SoundLoader;
	import src.ui.BlockHitSign;
	import src.ui.DamageSign;
	import src.ui.SwordHitSign;
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class GameUnit extends MovieClip implements IElementInfo, IElementUnitInfo
	{
		public static const BATTLE_ROLE_ATTACKER:Number = 1;
		public static const BATTLE_ROLE_DEFENDER:Number = 2;
		
		// Constants.
		private const focusSignRadiusW:Number = ConstTile.TILE_W;
		private const focusSignRadiusH:Number = ConstTile.TILE_H / 2;
		private const focusSignRadiusPosX:Number = 0;
		private const focusSignRadiusPosY:Number = (ConstTile.TILE_H / 2) - 3;
		
		private const busySignPosX:Number = ConstTile.TILE_W - 8;
		private const busySignPosY:Number = -12;
		
		// Unique identifier.
		private var _uid:int;
		// Type identifier for map building.
		protected var _id:int;
		
		// Element type identifier;
		private var _type:int = ElementType.UNIT;
		protected var _name:String;
		protected var _desc:String;
		
		// Unit type attributes.
		protected var _soldiers_max;      //! Maximum number of soldiers that can hold.
		protected var _soldiers;    //! Number of soldiers that can fight.
		protected var _soldiers_injuried; //! Number of soldiers that are hurt and can't fight;
		protected var _health_max;
		protected var _health;
		protected var _attack;
		protected var _defense;
		protected var _distance;
		protected var _move_time;			//! Time to move a square in days.
		protected var _recruit_cost;
		
		// Action definitions.
		private var _busy:Boolean;
		private var moveTimer:Timer;
		private var movePath:Vector.<SPFNode>;
		private var moveTo:SPFNode;
		private var moveFrom:int;
		private var attackInProgress:Boolean;
		private var enemy:GameUnit;
		private var attackTimer:Timer;
		private var _battleRole:Number;
		private var engaged:Boolean;
		
		// Images.
		protected var _topImg:MovieClip;
		private var _focusSign:Shape;
		private var _busySign:HourglassSign;
		private var _swordHitSign:SwordHitSign;
		private var _damageSign:DamageSign;
		private var _blockHitSign:BlockHitSign;
		
		// Unit advantages and disadvantages.
		
//##################################################################################################
		// Unique building identifier.
		private static var uid_count:int;
		
		/**
		 * @return An unique identifier for the unit.
		 */
		public static function generateUID() : int
		{
			var new_uid = uid_count;
			uid_count++;
			return new_uid;
		}
//##################################################################################################

		public function GameUnit()
		{
			_uid = GameUnit.generateUID();
			
			moveTimer = new Timer(0);
			moveTimer.addEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_move, false, 0, true);
			attackTimer = new Timer(0);
			attackTimer.addEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_attack, false, 0, true);
			
			drawSigns();
			busy = false;
			attackInProgress = false;
			engaged = false;
		}
		
		public function removeSelf() : void
		{
			moveTimer.removeEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_move);
			attackTimer.removeEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_attack);
		}
		
		public function get uid() : int {return _uid;}
		public function get id():int { return _id; }
		
		public function get elemType():int {return _type;}
		public function get elemName():String { return _name; }
		public function get elemDesc():String { return _desc; }
		
		public function get soldiers_max() : int { return _soldiers_max; }
		public function get soldiers() : int { return _soldiers; }
		public function get soldiers_injuried() : int { return _soldiers_injuried; }
		public function get health_max() : int { return _health_max; }
		public function get health() : int { return _health; }
		public function get attack() : int { return _attack; }
		public function get defense() : int { return _defense; }
		public function get distance() : int { return _distance; }
		public function get move_time() : Number { return _move_time; }
		public function get recruit_cost() : int { return _recruit_cost; }
		
		public function get topImg() : MovieClip { return _topImg; }
		
		public function set focusSign(value:Boolean) : void { _focusSign.visible = value; }
		public function get battleRole():Number { return _battleRole;}
		
		/**
		 * Update unit x and y through a Point object.
		 */
		public function set position(pos:Point) : void
		{
			x = pos.x;
			y = pos.y;
		}
		
		/**
		 * Call after processing an unit action.
		 */
		public function unBusy() : void
		{
			if (movePath == null)
			{
				_busy = false;
				_busySign.visible = false;
			}
		}
		
		private function set busy(value:Boolean) : void
		{
			_busy = value;
			_busySign.visible = value;
		}
		
		/**
		 * Schedule unit movement.
		 */
		public function move(fromIdx:int, path:Vector.<SPFNode>) : void
		{
			if (engaged)
			{
				trace("Unit is fighting. Can't move right now.");
				return;
			}
			
			if (_busy == true)
			{
				// Unit movement can be canceled.
				trace("Unit is busy right now. Restarting movement timer.");
				moveTimer.stop();
				attackTimer.stop();
				attackInProgress = false;
				enemy = null;
			}
			
			busy = true;
			movePath = path;
			moveFrom = fromIdx;
				
			// We know that the first node on the list is the own node, so we discard it.
			moveTo = movePath.pop();	
			scheduleMovement();
		}
		
		public function moveAttack(fromIdx:int, path:Vector.<SPFNode>, unit:GameUnit) : void
		{
			if (engaged)
			{
				trace("Unit is fighting. Can't move right now.");
				return;
			}
			
			if (_busy == true)
			{
				// Unit movement can be canceled.
				trace("Unit is busy right now. Restarting movement timer.");
				moveTimer.stop();
				attackTimer.stop();
			}
			
			attackInProgress = true;
			enemy = unit;
			
			busy = true;
			movePath = path;
			moveFrom = fromIdx;
				
			// We know that the first node on the list is the own node, so we discard it.
			moveTo = movePath.pop();	
			scheduleMovement();
		}
		
		/**
		 * Stop current unit action.
		 */
		public function stopMove() : void
		{
			if (_busy != true)
			{
				return;
			}
			
			moveTimer.stop();
			moveFrom = -1;
			moveTo = null;
			movePath = null;
			busy = false;
		}
		
		public function stopAttack() : void
		{
			if (_busy != true)
			{
				return;
			}
			
			attackTimer.stop();
			moveFrom = -1;
			moveTo = null;
			movePath = null;
			attackInProgress = false;
			busy = false;
			_battleRole = 0;
			engaged = false;
		}
		
		public function engage(battleRole:Number) : void
		{
			trace("preempted. Batle role is: " + battleRole);
			engaged = true;
			_battleRole = battleRole;
			if (_battleRole == GameUnit.BATTLE_ROLE_DEFENDER)
			{
				stopMove();
				attackInProgress = true;
				busy = true;
			}
		}
		
		public function scheduleAttack(role:Number) : void
		{
			attackTimer.delay = Const.HALF_DAY_MS;
			attackTimer.repeatCount = 1;
			
			_battleRole = role;
			
			attackTimer.reset();
			attackTimer.start();
		}
		
		public function takeDamage(value:int) : void
		{
			if (value < 0)
			{
				trace("Internal error. Received a negative value in takeDamage function. " + value);
				return;
			}
			_soldiers -= value;
			trace("taking damage: " + value + " remaining soldiers: " + _soldiers);
			if (_soldiers < 0)
			{
				_soldiers = 0;
			}
			
			if (value > 0)
			{
				_swordHitSign.gotoAndPlay(Const.ANIMATION_PLAYING);
				_damageSign.gotoAndPlay(Const.ANIMATION_PLAYING);
				_damageSign.damage.text = String(value);
				SoundLoader.playSwordHit01();
			}
			else
			{
				_blockHitSign.gotoAndPlay(Const.ANIMATION_PLAYING);
				SoundLoader.playBlockHit01();
			}
		}

//##################################################################################################
// Private functions.
//##################################################################################################
		private function drawSigns() : void
		{
			_focusSign = new Shape();
			_focusSign.graphics.beginFill(0xffffcc);
			_focusSign.graphics.drawEllipse(focusSignRadiusPosX, focusSignRadiusPosY, focusSignRadiusW, focusSignRadiusH);
			_focusSign.graphics.drawEllipse(focusSignRadiusPosX, focusSignRadiusPosY, focusSignRadiusW - 2, focusSignRadiusH - 2);
			_focusSign.graphics.endFill();
			_focusSign.visible = false;
			addChildAt(_focusSign, 0);
			
			_busySign = new HourglassSign();
			_busySign.visible = false;
			_topImg.addChild(_busySign);
			
			_swordHitSign = new SwordHitSign();
			_topImg.addChild(_swordHitSign);
			
			_damageSign = new DamageSign();
			_topImg.addChild(_damageSign);
			
			_blockHitSign = new BlockHitSign();
			_topImg.addChild(_blockHitSign);
		}

		private function scheduleMovement() : void
		{			
			moveTo = movePath.pop();
			
			// If is the last node and we are in a battle.
			if ( (movePath.length == 0) && (attackInProgress == true) )
			{
				trace("attacking");
				engaged = true;
				dispatchEvent(new UnitEngageEvent(this, enemy, moveTo.uid));
				return;
			}
			
			moveTimer.delay = ( (Const.MOVE_TIME_1_DAY / _move_time) * Const.DAY_TIME_MS) +  weightFromNode(moveTo);
			moveTimer.repeatCount = 1;
			
			trace("next mode to weight: " + weightFromNode(moveTo) + "; total delay: " + moveTimer.delay);
			
			if (movePath.length == 0)
			{
				movePath = null;
			}
			
			moveTimer.reset();
			moveTimer.start();
		}
		
		/**
		 * What out. If the bonus weight of the node is less than the default weight, the unit verification
		 * in this function may fail.		 * 
		 * @param	node
		 * @return
		 */
		private function weightFromNode(node:SPFNode) : Number
		{
			var bonus:Number;
			var weigth:Number = node.weight;
			
			// Check if node have a unit inside it.
			if (weigth >= Const.UNIT_WEIGHT)
			{
				weigth -= Const.UNIT_WEIGHT;
			}
			
			// Get bonus percentage.
			weigth = Const.DEFAULT_WEIGHT - weigth;
			
			bonus = (_move_time / 10) * weigth;
			bonus *= Const.DAY_TIME_MS;
			// Invert bonus time so we can naturally sum it.
			bonus *= -1;
			
			return bonus;
		}
		
		private function handleTimerComplete_move(e:TimerEvent) : void
		{
			dispatchEvent(new UnitMoveEvent(this, moveFrom, moveTo.uid));
			
			if (movePath == null)
			{
				moveFrom = -1;
				moveTo = null;
				// Unit finished moving.
				return;
			}
			
			moveFrom = moveTo.uid;
			scheduleMovement()
		}
		
		private function handleTimerComplete_attack(e:TimerEvent) : void
		{
			// Attacker.
			if (_battleRole == GameUnit.BATTLE_ROLE_ATTACKER)
			{
				trace("Attacker.");
				dispatchEvent(new UnitBattleEvent(this, enemy, GameUnit.BATTLE_ROLE_DEFENDER));
			}
			// Defender.
			else
			{
				trace("Defender.");
				dispatchEvent(new UnitBattleEvent(this, enemy, GameUnit.BATTLE_ROLE_ATTACKER));
			}
		}
	}
	
}