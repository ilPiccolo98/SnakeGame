#include "Menu_pausa.h"
#include <conio.h>
#include "Snake_game.h"
#include <Windows.h>
#include <iostream>

//FUNZIONI PUBLICHE
//inizializza i membri
Game::Menu_pausa::Menu_pausa(unsigned int _pos_riga, unsigned int _pos_colonna) : run_menu{ true },
	continua_game{ true }, voce{ 0 }, pos_riga{ _pos_riga }, pos_colonna{ _pos_colonna }
{

}

//esegue il menu
bool Game::Menu_pausa::run()
{
	loop();
	cancella_voci();
	reset();
	return continua_game;
}

//FUNZIONI PRIVATE
//loop menu
void Game::Menu_pausa::loop()
{
	while (run_menu)
	{
		stampa_voci();
		input();
	}
}

//gestisce l'input del menu
void Game::Menu_pausa::input() noexcept
{
	if (_kbhit())
	{
		char c{ static_cast<char>(_getch()) };
		switch (c)
		{
			case 'w':
				input_w();
				break;
			case 's':
				input_s();
				break;
			case 13: //ENTER
				input_enter();
				break;
		}
	}
}

//gestisce l'input w
void Game::Menu_pausa::input_w() noexcept
{
	if (!voce)
		voce = 1;
	else
		--voce;
}

//gestisce l'input s
void Game::Menu_pausa::input_s() noexcept
{
	if (voce == 1)
		voce = 0;
	else
		++voce;
}

//gestisce l'input enter
void Game::Menu_pausa::input_enter() noexcept
{
	run_menu = false;
	if (!voce)
		continua_game = true;
	else
		continua_game = false;
}

//stampa la scritta gioco in pausa
void Game::Menu_pausa::stampa_pausa() const noexcept
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cursor_position(pos_riga, pos_colonna + 9);
	std::cout << "Gioco in pausa!";
}

//stampa la scritta continua
void Game::Menu_pausa::stampa_continua() const noexcept
{
	if(!voce)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cursor_position(pos_riga + 1, pos_colonna + 12);
	std::cout << "Continua";
}

//stampa la scritta esci
void Game::Menu_pausa::stampa_esci() const noexcept
{
	if (voce == 1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cursor_position(pos_riga + 2, pos_colonna + 14);
	std::cout << "Esci";
}

//cancella la scritta pausa
void Game::Menu_pausa::cancella_pausa() const noexcept
{
	cursor_position(pos_riga, pos_colonna + 9);
	std::cout << "               ";
}

//cancella la scritta continua
void Game::Menu_pausa::cancella_continua() const noexcept
{
	cursor_position(pos_riga + 1, pos_colonna + 12);
	std::cout << "        ";
}

//cancella la scritta esci
void Game::Menu_pausa::cancella_esci() const noexcept
{
	cursor_position(pos_riga + 2, pos_colonna + 14);
	std::cout << "    ";
}

//cancella tutte le scritte
void Game::Menu_pausa::cancella_voci() const noexcept
{
	cancella_pausa();
	cancella_continua();
	cancella_esci();
}

//stampa tutte le voci
void Game::Menu_pausa::stampa_voci() const noexcept
{
	stampa_pausa();
	stampa_continua();
	stampa_esci();
}

//resetta i membri
void Game::Menu_pausa::reset() noexcept
{
	voce = 0;
	run_menu = true;
}
