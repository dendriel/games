package src
{
	import src.stage.MyStage;
	
	/**
	 * @author Vitor Rozsa
	 * @usage Contains stages.
	 */
	public class Level
	{
		private var stageList:Vector.<MyStage>;
		
		public function Level() : void
		{
			stageList = new Vector.<MyStage>;
		}
		
		/******************************************************************************************/
		/* Public methods */
		/******************************************************************************************/
		
		/**
		 * @usage Add a level into the level holder.
		 * @param	l
		 */
		public function add(stg:MyStage) : void
		{
			stageList.push(stg);
		}
		
		/**
		 * @usage Get a level from the level holder.
		 * @param	l
		 */
		public function getStage() : MyStage
		{
			return stageList.pop();
		}
	}
	
}