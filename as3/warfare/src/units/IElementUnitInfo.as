package src.units
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public interface IElementUnitInfo 
	{
		function get soldiers_max() : int;
		function get soldiers() : int;
		function get soldiers_injuried() : int;
		function get health_max() : int;
		function get health() : int;
		function get attack() : int;
		function get defense() : int;
		function get distance() : int;
		function get move_time() : int;
		function get recruit_cost() : int;
	}
	
}