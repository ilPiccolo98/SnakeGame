#ifndef MENU_PRINCIPALE_H
#define MENU_PRINCIPALE_H
#include "Snake_game.h"
#include "Menu_difficolta.h"

namespace Game
{
	class Menu_principale
	{
		public:
			Menu_principale();
			~Menu_principale() =default;
			void run();
		private:
			void loop();
			void input() noexcept;
			void input_w() noexcept;
			void input_s() noexcept;
			void input_enter() noexcept;
			void stampa_scritta() const noexcept;
			void inizia_gioco() noexcept;
			void seleziona_difficolta() noexcept;
			void esci() noexcept;
			bool run_menu;
			static const unsigned int righe_bianche{ 12 };
			unsigned short voce;
			static const std::string scritta;
			Menu_difficolta menu_diff;
			Snake_game game;
	};
}

#endif //MENU_PRINCIPALE_H
