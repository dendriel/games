package src.units
{
	import flash.display.Bitmap;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.utils.Timer;
	import src.GamePlayer;
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
		private const removeSelfTimerDelay:Number = 100;
		
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
		// Owner.
		private var _player:GamePlayer;
		
		// Element type identifier;
		private var _type:int = ElementType.UNIT;
		protected var _name:String;
		protected var _desc:String;
		
		// Unit type attributes.
		protected var _soldiers_max;      //! Maximum number of soldiers that can hold.
		protected var _soldiers;    //! Number of soldiers that can fight.
		protected var _soldiers_injuried; //! Number of soldiers that are hurt and can't fight;
		protected var _attack;
		protected var _defense;
		protected var _distance;
		protected var _move_time;			//! Time to move a square in days.
		protected var _recruit_cost;
		
		// Action definitions.
		private var moveTimer:Timer;
		private var _move_path:Vector.<SPFNode>;
		private var _move_to:SPFNode;
		private var attackInProgress:Boolean;
		private var enemy:GameUnit;
		private var attackTimer:Timer;
		private var _battleRole:Number;
		private var _engaged:Boolean;
		private var removeSelfTimer:Timer;
		
		// Images.
		protected var _topImg:MovieClip;
		private var _focusSign:Shape;
		private var _busySign:HourglassSign;
		private var _swordHitSign:SwordHitSign;
		private var _damageSign:DamageSign;
		private var _blockHitSign:BlockHitSign;
		private var _banner:Bitmap;
		
		// Unit advantages and disadvantages.
		// TODO.
		
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
			removeSelfTimer = new Timer(0);
			removeSelfTimer.addEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_ended, false, 0, true);
			
			drawSigns();
			attackInProgress = false;
			_engaged = false;
		}


//##################################################################################################
// Public functions.
//##################################################################################################
		public function removeSelf() : void
		{
			// Remove reference from player.
			player.removeUnit(this);
			
			moveTimer.removeEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_move);
			attackTimer.removeEventListener(TimerEvent.TIMER_COMPLETE, handleTimerComplete_attack);
			
			// Wait animations to finish.
			handleTimerComplete_ended(null);
		}
		
		public function get uid() : int {return _uid;}
		public function get id():int { return _id; }
		
		public function get player():GamePlayer {return _player;}
		public function set player(value:GamePlayer):void
		{
			trace("add player into unit " + this.uid);
			if ( (_player != null) && _topImg.contains(_banner) )
			{
				_topImg.removeChild(_banner);
			}
			
			_player = value;
			_banner = player.banner;
			_topImg.addChild(_banner);
		}
		
		public function get elemType():int {return _type;}
		public function get elemName():String { return _name; }
		public function get elemDesc():String { return _desc; }
		
		public function get soldiers_max() : int { return _soldiers_max; }
		public function get soldiers() : int { return _soldiers; }
		public function get soldiers_injuried() : int { return _soldiers_injuried; }
		public function get attack() : int { return _attack; }
		public function get defense() : int { return _defense; }
		public function get distance() : int { return _distance; }
		public function get move_time() : Number { return _move_time; }
		public function get recruit_cost() : int { return _recruit_cost; }
		
		public function get topImg() : MovieClip { return _topImg; }
		
		public function set focusSign(value:Boolean) : void
		{
			if ( (_focusSign.visible == false) && (value == true) )
			{
				SoundLoader.playUnitsSelect01();
			}
			_focusSign.visible = value;
		}
		
		public function get battleRole():Number { return _battleRole;}
		
//#####################
// Unit actions.
		/**
		 * Engage unit in a fight; TODO: keep a list of all units in a battle and process the fight
		 * over this list. A unit can defend itself from many enemies, but can attack only one.
		 * @return true if could engage the unit; false if the unit cant fight.
		 */
		public function engage() : Boolean
		{
			if (_engaged == true)
			{
				return false;
			}
			
			stopMove();
			_engaged = true;
			busySign = true;
			
			return true;
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
		
		/**
		 * Start unit movement.
		 */
		public function startMove(path:Vector.<SPFNode>) : void
		{
			if (_engaged)
			{
				trace("Unit is fighting. Can't move right now.");
				return;
			}
			
			if (attackInProgress != true)
			{
				SoundLoader.playUnitMove01();
			}
			
			busySign = true;
			attackInProgress = false;
			moveTimer.stop();
			_move_path = path;
			scheduleMove();
		}
		
		/**
		 * Start unit attack.
		 */
		public function startAttack(path:Vector.<SPFNode>, unit:GameUnit) : void
		{
			if (_engaged)
			{
				trace("Unit is fighting. Can't move right now.");
				return;
			}
			
			SoundLoader.playCharge01();
			
			busySign = true;
			moveTimer.stop();
			attackInProgress = true;
			enemy = unit;
			_move_path = path;
			scheduleMove();
		}

		/**
		 * Schedule next unit movement.
		 */
		public function scheduleMove() : void
		{
			if (_move_path == null)
			{
				// Movement has ended.
				busySign = false;
				return;
			}
			
			_move_to = _move_path.pop();
			
			if (_move_path.length == 0)
			{
				_move_path = null;
			}
			
			// If is the last node and we are in a battle.
			if ( (_move_path == null) && (attackInProgress == true) )
			{
				attackInProgress = false;
				_engaged = true;
				dispatchEvent(new UnitEngageEvent(this, enemy, _move_to.uid));
				return;
			}
			
			moveTimer.delay = ( (Const.MOVE_TIME_1_DAY / _move_time) * Const.DAY_TIME_MS) +  weightFromNode(_move_to);
			moveTimer.repeatCount = 1;
			
			moveTimer.reset();
			moveTimer.start();
		}
		
		/**
		 * Schedule next unit attack.
		 * @param	role Unit will be the attacker or defender.
		 */
		public function scheduleAttack(role:Number) : void
		{
			attackTimer.delay = Const.HALF_DAY_MS;
			attackTimer.repeatCount = 1;
			
			_battleRole = role;
			
			attackTimer.reset();
			attackTimer.start();
		}
		
		public function stopMove() : void
		{			
			moveTimer.stop();
			_move_to = null;
			_move_path = null;
			attackInProgress = false;
			busySign = false;
		}
		
		public function stopAttack() : void
		{			
			attackTimer.stop();
			moveTimer.stop();
			_move_to = null;
			_move_path = null;
			attackInProgress = false;
			_battleRole = 0;
			_engaged = false;
			busySign = false;
		}

//##################################################################################################
// Private functions.
//##################################################################################################
		
//#####################
// Handle Timer Events.
		private function handleTimerComplete_move(e:TimerEvent) : void
		{
			var moveToUID:int = _move_to.uid;
			
			if (_move_path == null)
			{
				// Unit finished moving.
				_move_to = null;
				busySign = false;
			}
			
			dispatchEvent(new UnitMoveEvent(this, moveToUID));
		}
		
		private function handleTimerComplete_attack(e:TimerEvent) : void
		{
			// Attacker.
			if (_battleRole == GameUnit.BATTLE_ROLE_ATTACKER)
			{
				dispatchEvent(new UnitBattleEvent(this, enemy, GameUnit.BATTLE_ROLE_DEFENDER));
			}
			// Defender.
			else
			{
				dispatchEvent(new UnitBattleEvent(this, enemy, GameUnit.BATTLE_ROLE_ATTACKER));
			}
		}
		
		private function handleTimerComplete_ended(e:TimerEvent) : void
		{
			// Check if there is an animation being played.
			if (_swordHitSign.playing || _blockHitSign.playing || _damageSign.playing)
			{
				removeSelfTimer.delay = removeSelfTimerDelay;
				removeSelfTimer.repeatCount = 1;				
				removeSelfTimer.reset();
				removeSelfTimer.start();
			}
			else
			{
				dispatchEvent(new UnitRemoveEvent(this));
			}
		}

//#####################
// Auxiliary functions.
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
		
		/**
		 * What out. If the bonus weight of the node is less than the default weight, the unit verification
		 * in this function may fail.
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
		
		private function set busySign(value:Boolean) : void
		{
			_busySign.visible = value;
		}
		
		public function get move_path():Vector.<SPFNode> 
		{
			if (_move_path != null)
			{
				return _move_path.concat();
			}
			return null;
		}
		
		public function get move_to():SPFNode 
		{
			return _move_to;
		}
		
		public function get engaged():Boolean 
		{
			return _engaged;
		}
	}
	
}