#ifndef MENU_DIFFICOLTA_H
#define MENU_DIFFICOLTA_H
#include <string>

namespace Game
{
	class Menu_difficolta
	{
		public:
			Menu_difficolta();
			~Menu_difficolta() =default;
			unsigned short run() noexcept;
		private:
			void loop() noexcept;
			void input() noexcept;
			void input_w() noexcept;
			void input_s() noexcept;
			void input_enter() noexcept;
			void stampa_scritta() const noexcept;
			void stampa_facile() const noexcept;
			void stampa_media() const noexcept;
			void stampa_difficile() const noexcept;
			void stampa_esci() const noexcept;
			void stampa_voci() const noexcept;
			void reset() noexcept;
			bool run_menu;
			unsigned short voce;
			unsigned short difficolta;
			static const unsigned int righe_bianche{ 21 };
			static const std::string scritta;
	};
}

#endif //MENU_DIFFICOLTA_H
