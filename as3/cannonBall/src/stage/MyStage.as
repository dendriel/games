package src.stage
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	import src.CannonBallFactory;
	import src.com.senocular.utils.KeyObject;
	import src.Cannon;
	import src.Const;
	
	/**
	 * @usage Contains levels.
	 * @author Vitor Rozsa
	 */
	public class MyStage extends MovieClip
	{
		// Variables that are customized by the subclasses.
		protected var bgImage:MovieClip;
		protected var cann:Cannon;
		protected var wallHolderList:MovieClip;
		protected var targeHoldertList:MovieClip;
		
		protected var _fieldOriginX:Number;	// movable area origin x.
		protected var _fieldOriginY:Number;	// movable area origin y.
		
		protected var _fieldWidth:Number;	// movable area width;
		protected var _fieldHeight:Number;	// movable area height;
		
		private var cannonBallFactoryR:CannonBallFactory;
		
		public function MyStage()
		{
			cann = new Cannon();
			
			// Create a cannon ball factory.
			cannonBallFactoryR = new CannonBallFactory(this);
			
			// Fill movable area specifications.
			_fieldOriginX = Const.STAGE_DEFAULT_ORIGIN_X;
			_fieldOriginY = Const.STAGE_DEFAULT_ORIGIN_Y;
			_fieldWidth = Const.STAGE_DEFAULT_WIDTH;
			_fieldHeight = Const.STAGE_DEFAULT_HEIGHT;
		}

		/******************************************************************************************/
		/* Public methods */
		/******************************************************************************************/
		/**
		 * @usage Load necessary resources.
		 */
		public function load(key:KeyObject) : void
		{
			// Handle ball hit target event.
			cannonBallFactoryR.addEventListener(Const.EVT_HIT_TARGET, handleHitTarget, false, 0, true);
			cannonBallFactoryR.addEventListener(Const.EVT_BALL_STOPPED, handleBallStopped, false, 0, true);
			
			// Load control objects into cannon.
			cann.load(key, cannonBallFactoryR);
			
			// Handle cannon shoot event.
			cann.addEventListener(Const.EVT_CANNON_SHOOTING, handleCannonShooting, false, 0 , true);
			
			// Add cannon into stage.
			this.addChild(cann);
			
			// Start updateSelf.
			addEventListener(Event.ENTER_FRAME, updateSelf, false, 0, true);
		}
		
		/**
		 * @usage Free allocated resources.
		 */
		public function unload() : void
		{
			// Stop cannon.
			cann.unload();
			cann.removeEventListener(Const.EVT_CANNON_SHOOTING, handleCannonShooting);
			
			// Stop factory.
			cannonBallFactoryR.removeEventListener(Const.EVT_HIT_TARGET, handleHitTarget);
			cannonBallFactoryR.removeEventListener(Const.EVT_BALL_STOPPED, handleBallStopped);
			
			if (this.contains(cann))
			{
				this.removeChild(cann);
			}
			
			// Stop running.
			removeEventListener(Event.ENTER_FRAME, updateSelf);
		}
		
		
		public function getWallHolderList() : MovieClip
		{
			return wallHolderList;
		}
		
		public function getTargetHolderList() : MovieClip
		{
			return targeHoldertList;
		}
				
		public function get fieldOriginX():Number 
		{
			return _fieldOriginX;
		}
		
		public function get fieldOriginY():Number 
		{
			return _fieldOriginY;
		}
		
		public function get fieldWidth():Number 
		{
			return _fieldWidth;
		}
		
		public function get fieldHeight():Number 
		{
			return _fieldHeight;
		}
		
		/******************************************************************************************/
		/* Protected methods */
		/******************************************************************************************/
		
		/**
		 * @usage Draw the stage contents.
		 */
		protected function drawSelf() : void
		{
			// Draw background.
			this.addChild(bgImage);
			
			// Draw walls.
			this.addChild(wallHolderList);
			
			// Draw targets.
			this.addChild(targeHoldertList);
		}
		
		/**
		 * @usage Remove the stage contents.
		 */
		protected function removeSelf() : void
		{
			if (this.contains(bgImage))
			{
				this.removeChild(bgImage);
			}
			
			if (this.contains(wallHolderList))
			{
				this.removeChild(wallHolderList);
			}
		}
		
		/******************************************************************************************/
		/* Private methods */
		/******************************************************************************************/
		/**
		 * @usage Update self.
		 * @param	e
		 */
		private function updateSelf(e:Event) : void
		{
		}
		
		/**
		 * @usage Handle cannon shooting event.
		 * @param	e
		 */
		private function handleCannonShooting(e:Event) : void
		{
			// Prevent cannon from shooting.
			cann.canShoot = false;
			//cann.canShoot = true;
		}
		
		private function handleHitTarget(e:Event) : void
		{
			// Let cannon shot again.
			cann.canShoot = true;
		}
		
		private function handleBallStopped(e:Event) : void
		{
			// Let cannon shot again.
			cann.canShoot = true;
		}
	}
	
}