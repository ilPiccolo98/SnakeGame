#include "Menu_principale.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

//FUNZIONI PUBBLICHE
//inizializza i membri
Game::Menu_principale::Menu_principale() : run_menu{ true }, voce{ 0 }, menu_diff{}, game{ 20, 40, 3 }
{
	std::srand(std::time(nullptr));
}

//esegue il menu
void Game::Menu_principale::run()
{
	loop();
	system("cls");
}

//FUNZIONI PRIVATE
//loop game
void Game::Menu_principale::loop()
{
	system("cls");
	while (run_menu)
	{
		stampa_scritta();
		Sleep(35);
		inizia_gioco();
		seleziona_difficolta();
		esci();
		input();
	}
}

//gestisce l'input del menu
void Game::Menu_principale::input() noexcept
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

//gestisce input dopo aver premuto w
void Game::Menu_principale::input_w() noexcept
{
	if (voce == 0)
		voce = 2;
	else
		--voce;
}

//gestisce input dopo aver premuto w
void Game::Menu_principale::input_s() noexcept
{
	if (voce == 2)
		voce = 0;
	else
		++voce;
}

//gestisce input dopo aver premuto enter
void Game::Menu_principale::input_enter() noexcept
{
	if (voce == 0)
	{
		system("cls");
		game.run();
	}
	else if (voce == 1)
	{
		voce = 0;
		game.set_difficolta(menu_diff.run());
	}
	else
		run_menu = false;
}

//stampa la scritta
void Game::Menu_principale::stampa_scritta() const noexcept
{
	hidecursor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (std::rand() % 15) + 1);
	cursor_position(2, 0);
	std::cout << scritta;
}

//stampa la prima voce
void Game::Menu_principale::inizia_gioco() noexcept
{
	if(!voce)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cursor_position(righe_bianche + 3, 52);
	std::cout << "GIOCA NUOVA PARTITA";
}

//stampa la seconda voce
void Game::Menu_principale::seleziona_difficolta() noexcept
{
	if (voce == 1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cursor_position(righe_bianche + 5, 47);
	std::cout << "SELEZIONA LIVELLO DIFFICOLTA'";

}

//stampa la terza voce
void Game::Menu_principale::esci() noexcept
{
	if (voce == 2)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cursor_position(righe_bianche + 7, 59);
	std::cout << "ESCI";
}

//scritta snake
const std::string Game::Menu_principale::scritta = R"(
                       SSSSSSSS     NNNNN        NNN          AAAAAA          KKK    KKK  EEEEEEEEEEE
                      SSS     SSS   NNN NN       NNN         AAA  AAA         KKK   KKK   EEEEEEEEEEE
                     SSS       SSS  NNN  NN      NNN        AAA    AAA        KKK  KKK    EEE
                      SSS           NNN   NN     NNN       AAAAAAAAAAAA       KKK KKK     EEE
                        SSS         NNN    NN    NNN      AAAAAAAAAAAAAA      KKKKKK      EEEEEEE
                          SSS       NNN     NN   NNN     AAA          AAA     KKK KKK     EEE 
                SSS         SSS     NNN      NN  NNN    AAA            AAA    KKK  KKK    EEE
                 SSS      SSS       NNN       NN NNN   AAA              AAA   KKK   KKK   EEEEEEEEEEE
                    SSSSSSS         NNN        NNNNN  AAA                AAA  KKK    KKK  EEEEEEEEEEE)";