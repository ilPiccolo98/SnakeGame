#include "Snake_game.h"
#include <Windows.h>
#include <iostream>
#include <stdexcept>
#include <conio.h>

//FUNZIONI PUBBLICHE
//inizializzo i membri
Game::Snake_game::Snake_game(unsigned int righe, unsigned int colonne, unsigned short _difficolta) :
	difficolta{ _difficolta }, punteggio{ 0 }, key{ Keyboard::KEY_D }, fruit{}, serpente{ 1, 1 },
	griglia{ righe, colonne, 5, 40 }, 
	pausa{ griglia.righe_bianche() + 2, griglia.colonne() + griglia.colonne_bianche() + 2 }
{
	spawn_fruit();
}

//starta il gioco
void Game::Snake_game::run()
{
	loop();
	reset();
}

//imposta la difficolta
void Game::Snake_game::set_difficolta(unsigned int _difficolta)
{
	if (_difficolta < 1 || _difficolta > 3)
		throw std::out_of_range{ "valore difficolta non corretto" };
	difficolta = _difficolta;
}

//FUNZIONI PRIVATE
//loop game
void Game::Snake_game::loop()
{
	griglia.stampa();
	draw_scritta();
	hidecursor();
	while (key != Keyboard::KEY_ESC)
	{
		eat_fruit();
		erase_elements();
		input();
		update_snake();
		draw_elements();
		check_game_over();
		Sleep(difficolta * 100);
	}
}

//gestisce l'input del gioco
void Game::Snake_game::input() noexcept
{
	if (_kbhit())
	{
		char c{ static_cast<char>(_getch()) };
		switch (c)
		{
		case 'w':
			if (key != Keyboard::KEY_S)
				key = Keyboard::KEY_W;
			break;
		case 'a':
			if (key != Keyboard::KEY_D)
				key = Keyboard::KEY_A;
			break;
		case 's':
			if (key != Keyboard::KEY_W)
				key = Keyboard::KEY_S;
			break;
		case 'd':
			if (key != Keyboard::KEY_A)
				key = Keyboard::KEY_D;
			break;
		case 27: //ESC
			key = Keyboard::KEY_ESC;
			break;
		case 13: //ENTER
			pause_game();
			break;
		}
	}
}

//genera un nuovo fruit
void Game::Snake_game::spawn_fruit() noexcept
{
	bool b{ true };
	while (b)
	{
		fruit.generate(1, griglia.righe() - 1, 1, griglia.colonne() - 1);
		b = false;
		for (unsigned int i{ 0 }; i != serpente.size(); ++i)
			if (serpente[i].first == fruit.get_riga() && serpente[i].second == fruit.get_colonna())
				b = true;
	}
}

//aggiorna il serpente
void Game::Snake_game::update_snake() noexcept
{
	switch (key)
	{
		case Keyboard::KEY_W:
			button_w();
			break;
		case Keyboard::KEY_S:
			button_s();
			break;
		case Keyboard::KEY_A:
			button_a();
			break;
		case Keyboard::KEY_D:
			button_d();
			break;
	}
}

//pulsante w premuto
void Game::Snake_game::button_w() noexcept
{
	if (serpente.testa().first == 1)
		serpente.set_testa(griglia.righe() - 2, serpente.testa().second);
	else
		serpente.move_up();
}

//pulsante s premuto
void Game::Snake_game::button_s() noexcept
{
	if (serpente.testa().first == griglia.righe() - 2)
		serpente.set_testa(1, serpente.testa().second);
	else
		serpente.move_down();
}

//pulsante a premuto
void Game::Snake_game::button_a() noexcept
{
	if (serpente.testa().second == 1)
		serpente.set_testa(serpente.testa().first, griglia.colonne() - 2);
	else
		serpente.move_left();
}

//pulsante d premuto
void Game::Snake_game::button_d() noexcept
{
	if (serpente.testa().second == griglia.colonne() - 2)
		serpente.set_testa(serpente.testa().first, 1);
	else
		serpente.move_right();
}

//cancella il serpente sullo schermo
void Game::Snake_game::erase_snake() const noexcept
{
	for (unsigned int i{ 0 }; i != serpente.size(); ++i)
	{
		cursor_position(serpente[i].first + griglia.righe_bianche(), serpente[i].second + griglia.colonne_bianche());
		std::cout << '\0';
	}
}

//disegna il serpente sullo schermo
void Game::Snake_game::draw_snake() const noexcept
{
	for (unsigned int i{ 0 }; i != serpente.size(); ++i)
	{
		if(!i)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cursor_position(serpente[i].first + griglia.righe_bianche(), serpente[i].second + griglia.colonne_bianche());
		std::cout << static_cast<char>(254);
	}
}

//cancella il fruit sullo schermo
void Game::Snake_game::erase_fruit() const noexcept
{
	cursor_position(fruit.get_riga() + griglia.righe_bianche(), fruit.get_colonna() + griglia.colonne_bianche());
	std::cout << '\0';
}

//disegna il fruit sullo schermo
void Game::Snake_game::draw_fruit() const noexcept
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cursor_position(fruit.get_riga() + griglia.righe_bianche(), fruit.get_colonna() + griglia.colonne_bianche());
	std::cout << 'o';
}

//cancella fruit e snake sullo schermo
void Game::Snake_game::erase_elements() const noexcept
{
	erase_snake();
	erase_fruit();
}

//disegna fruit e snake sullo schermo
void Game::Snake_game::draw_elements() const noexcept
{
	draw_punteggio();
	draw_fruit();
	draw_snake();
}

//controlla se il serpente ha mangiato il fruit
void Game::Snake_game::eat_fruit() noexcept
{
	if (serpente.testa().first == fruit.get_riga() && serpente.testa().second == fruit.get_colonna())
	{
		++punteggio;
		spawn_fruit();
		serpente.increase();
	}
}

//stampa il punteggio
void Game::Snake_game::draw_punteggio() const noexcept
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cursor_position(3, griglia.colonne_bianche() + 1);
	std::cout << "Il tuo punteggio: " << punteggio;
}

//stampa la scritta
void Game::Snake_game::draw_scritta() const noexcept
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cursor_position(2, 2);
	std::cout << scritta;
}

//controlla se il gioco e' finito
void Game::Snake_game::check_game_over() noexcept
{
	for (unsigned int i{ 1 }; i != serpente.size(); ++i)
		if (serpente.testa() == serpente[i])
		{
			change_color_testa();
			mess_game_over();
			key = Keyboard::KEY_ESC;
		}
}

//visualizza un messaggio se si perde il gioco
void Game::Snake_game::mess_game_over() const noexcept
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cursor_position(griglia.righe() + griglia.righe_bianche() + 2, griglia.colonne_bianche());
	std::cout << "HAI PERSO!\a\n";
	cursor_position(griglia.righe() + griglia.righe_bianche() + 3, griglia.colonne_bianche());
	std::cout << "TI SEI MORSO LA CODA!";
	cursor_position(griglia.righe() + griglia.righe_bianche() + 4, griglia.colonne_bianche());
	std::cout << "Premere un pulsante per continuare";
	_getch();
}

//cambia colore alla testa del serpente
void Game::Snake_game::change_color_testa() const noexcept
{
	cursor_position(serpente.testa().first + griglia.righe_bianche(), serpente.testa().second + griglia.colonne_bianche());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	std::cout << static_cast<char>(254);
}

//mette in pausa il gioco
void Game::Snake_game::pause_game() noexcept
{
	draw_elements();
	if (!pausa.run())
		key = Keyboard::KEY_ESC;
	erase_elements();
}

//resetta i membri interni
void Game::Snake_game::reset() noexcept
{
	serpente.reset(1, 1);
	punteggio = 0;
	spawn_fruit();
	key = Keyboard::KEY_D;
	system("cls");
}

//FUNZIONI HELPER
//nasconde il cursore della console
void Game::hidecursor() noexcept
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//cambia la posizione del cursore console
void Game::cursor_position(int x, int y) noexcept
{
	COORD pos = { y, x };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

const std::string Game::Snake_game::scritta = R"(
       SSSSSS
     SSS     SS
       SSS
         SSS        KKK  KKK
   SS    SSS        KKK KKK
    SSSSSS          KKKK
                    KKKK
    NNNN     NN     KKK KKK
    NN NN    NN     KKK  KKK
    NN  NN   NN
    NN   NN  NN
    NN    NN NN     EEEEEEEE
    NN     NNNN     EEEEEEEE
                    EE
     AAAAAA         EEEEE
    AA    AA        EE
   AA      AA       EEEEEEEE
  AAAAAAAAAAAA      EEEEEEEE
 AA          AA
AA            AA)";