package src.language
{
	
	/**
	 * ...
	 * @author Vitor Rozsa
	 */
	public class PortugueseLanguage extends BaseLanguage
	{
		public function PortugueseLanguage()
		{
			// Main Menu.
			_main_title           = "WARFARE";
			_single_player_button = "Jogar";
			_multiplayer_button   = "Multijogador";
			_credits_button       = "Créditos";
			
			// Game information screen.
			_moveable_str = "Livre";
			_blocked_str = "Bloqueado";
			
			// Timer.
			_of_the_year_str = "do ano";
			_january_str = "Janeiro";
			_february_str = "Fevereiro";
			_march_str = "Março";
			_april_str = "Abril";
			_may_str = "Maio";
			_jun_str = "Junho";
			_july_str = "Julho";
			_august_str = "Agosto";
			_september_str = "Setembro";
			_october_str = "Outubro";
			_november_str = "Novembro";
			_december_str = "Dezembro";
			
			// Units.
			_levy_infantry01_name = "Recruta de infantaria";
			_levy_infantry01_desc = "O recruta de infantaria é um soldado de mílicia. Em geral os \
recrutas de infantaria são aldeões que são forçados a entrar no exército temporariamente para defender seu país ou atender a uma campanha militar.";
			_knight01_name = "Cavaleiro";
			_knight01_desc = "O cavaleiro é uma unidade de combate pesado. É utilizado para ataques velozes e destrutivos.";
			_light_infantry01_name = "Infantaria Leve";
			_light_infantry01_desc = "A infantaria leve é a unidade que compõe o núcleo de qualquer exército. É flexível, forte e rápida.";
			
			// Buildings.
			_village01_name = "Aldeia";
			_village01_desc = "Pequeno povoado rural que vive da subsistência e possui entre centenas e alguns poucos milhares de pessoas.";
			
			// Tiles.
			_grass01_name = "Campina";
			_grass01_desc = "Terreno amplo e de fácil acesso, porém, sem obstáculos naturais para defesa.";
			_mountain01_name = "Montanha";
			_mountain01_desc = "Grande elevação de difícil acesso. Representa um obstáculo natural e intransponível.";
			_river01_name = "Rio";
			_river01_desc = "Curso natural de água. Permite que civilizações se desenvolvam e fornece proteção natural contra perigos.";
			_tree01_name = "Floresta";
			_tree01_desc = "Fonte de recursos para civilizações. Também serve naturalmente como posição estratégica de defesa.";
		}
		
	}
	
}