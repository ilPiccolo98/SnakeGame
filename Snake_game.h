#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "Serpente.h"
#include "Griglia_snake.h"
#include "Fruit.h"
#include <string>
#include "Menu_pausa.h"

namespace Game
{
	enum class Keyboard
	{
		KEY_W, KEY_A, KEY_S, KEY_D, KEY_ESC
	};

	class Snake_game
	{
		public:
			Snake_game(unsigned int righe, unsigned int colonne, unsigned short _difficolta);
			~Snake_game() =default;
			void run();
			void set_difficolta(unsigned int _difficolta);
		private:
			void loop();
			void input() noexcept;
			void spawn_fruit() noexcept;
			void update_snake() noexcept;
			void button_w() noexcept;
			void button_s() noexcept;
			void button_a() noexcept;
			void button_d() noexcept;
			void erase_snake() const noexcept;
			void draw_snake() const noexcept;
			void erase_fruit() const noexcept;
			void draw_fruit() const noexcept;
			void erase_elements() const noexcept;
			void draw_elements() const noexcept;
			void eat_fruit() noexcept;
			void draw_punteggio() const noexcept;
			void draw_scritta() const noexcept;
			void check_game_over() noexcept;
			void mess_game_over() const noexcept; 
			void change_color_testa() const noexcept;
			void pause_game() noexcept;
			void reset() noexcept;
			unsigned short difficolta;
			unsigned int punteggio;
			Keyboard key;
			Fruit fruit;
			static const std::string scritta;
			Serpente serpente;
			const Griglia_snake griglia;
			Menu_pausa pausa;
	};

	void hidecursor() noexcept;
	void cursor_position(int x, int y) noexcept;
}

#endif //SNAKE_GAME_H
