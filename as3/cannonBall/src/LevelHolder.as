package src
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 * @usage Hold levels.
	 */
	public class LevelHolder 
	{
		private var levelList:Vector.<Level>;
		
		public function LevelHolder() : void
		{
			levelList = new Vector.<Level>;
		}
		
		/******************************************************************************************/
		/* Public methods */
		/******************************************************************************************/
		
		/**
		 * @usage Add a level into the level holder.
		 * @param	l
		 */
		public function add(l:Level) : void
		{
			levelList.push(l);
		}
		
		/**
		 * @usage Get a level from the level holder.
		 * @param	l
		 */
		public function getLevel() : Level
		{
			return levelList.pop();
		}
		
	}
	
}