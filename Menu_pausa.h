#ifndef MENU_PAUSA_H
#define MENU_PAUSA_H

namespace Game
{
	class Menu_pausa
	{
		public:
			Menu_pausa(unsigned int _pos_riga, unsigned int _pos_colonna);
			~Menu_pausa() =default;
			bool run();
		private:
			void loop();
			void input() noexcept;
			void input_w() noexcept;
			void input_s() noexcept;
			void input_enter() noexcept;
			void stampa_pausa() const noexcept;
			void stampa_continua() const noexcept;
			void stampa_esci() const noexcept;
			void cancella_pausa() const noexcept;
			void cancella_continua() const noexcept;
			void cancella_esci() const noexcept;
			void cancella_voci() const noexcept;
			void stampa_voci() const noexcept;
			void reset() noexcept;
			bool run_menu;
			bool continua_game;
			unsigned short voce;
			unsigned int pos_riga;
			unsigned int pos_colonna;
	};
}

#endif //MENU_PAUSA
