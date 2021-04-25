#include "Menu_difficolta.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "Snake_game.h"
#include <iostream>
#include <Windows.h>

//FUNZIONI PUBBLICHE
//inizializzo i membri
Game::Menu_difficolta::Menu_difficolta() : run_menu{ true }, voce{ 0 }, difficolta{ 3 }
{
	std::srand(std::time(nullptr));
}

//esegue il menu
unsigned short Game::Menu_difficolta::run() noexcept
{
	loop();
	reset();
	system("cls");
	return difficolta;
}

//FUNZIONI PRIVATE
//loop del menu
void Game::Menu_difficolta::loop() noexcept
{
	system("cls");
	stampa_scritta();
	while (run_menu)
	{
		stampa_voci();
		input();
	}
}

//gestisce l'input del menu
void Game::Menu_difficolta::input() noexcept
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
void Game::Menu_difficolta::input_w() noexcept
{
	if (!voce)
		voce = 3;
	else
		--voce;
}

//gestisce l'input s
void Game::Menu_difficolta::input_s() noexcept
{
	if (voce == 3)
		voce = 0;
	else
		++voce;
}

//gestisce l'input enter
void Game::Menu_difficolta::input_enter() noexcept
{
	if (!voce)
		difficolta = 3;
	else if (voce == 1)
		difficolta = 2;
	else if (voce == 2)
		difficolta = 1;
	else
		run_menu = false;
}

//stampa la scritta
void Game::Menu_difficolta::stampa_scritta() const noexcept
{
	hidecursor();
	cursor_position(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (std::rand() % 15) + 1);
	std::cout << scritta;
}

//stampa la scritta facile
void Game::Menu_difficolta::stampa_facile() const noexcept
{
	cursor_position(10, 56);
	if(!voce)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else if(difficolta == 3)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "FACILE";
}

//stampa la scritta media
void Game::Menu_difficolta::stampa_media() const noexcept
{
	cursor_position(12, 56);
	if (voce == 1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else if (difficolta == 2)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "NORMALE";
}

//stampa la scritta difficile
void Game::Menu_difficolta::stampa_difficile() const noexcept
{
	cursor_position(14, 55);
	if (voce == 2)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else if (difficolta == 1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "DIFFICILE";
}

//stampa la scritta esci
void Game::Menu_difficolta::stampa_esci() const noexcept
{
	cursor_position(16, 57);
	if (voce == 3)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "ESCI";
}

//stampa tutte le voci
void Game::Menu_difficolta::stampa_voci() const noexcept
{
	stampa_facile();
	stampa_media();
	stampa_difficile();
	stampa_esci();
}

//resetta i membri 
void Game::Menu_difficolta::reset() noexcept
{
	run_menu = true;
	voce = 0;
}

//scritta snake
const std::string Game::Menu_difficolta::scritta = R"(
                   SSSSSS                                                        SSSSSS 
                 SSS     SS                                                    SSS    SS
                   SSS                                                           SSS
                      SSS        KKK  KKK                                           SSS        KKK  KKK 
                 SS    SSS       KKK KKK                                       SS    SSS       KKK KKK
                  SSSSSS         KKKK                                           SSSSSS         KKKK
                                 KKKK                                                          KKKK
                 NNNN     NN     KKK KKK                                       NNNN     NN     KKK KKK
                 NN NN    NN     KKK  KKK                                      NN NN    NN     KKK  KKK
                 NN  NN   NN     KKK    KKK                                    NN  NN   NN
                 NN   NN  NN                                                   NN   NN  NN
                 NN    NN NN     EEEEEEEE                                      NN    NN NN     EEEEEEEE
                 NN     NNNN     EEEEEEEE                                      NN     NNNN     EEEEEEEE
                                 EE                                                            EE
                  AAAAAA         EEEEE                                            AAAAAA       EEEEE
                 AA    AA        EE                                              AA    AA      EE
                AA      AA       EEEEEEEE                                       AA      AA     EEEEEEEE
               AAAAAAAAAAAA      EEEEEEEE                                      AAAAAAAAAAAA    EEEEEEEE
              AA          AA                                                  AA          AA
             AA            AA                                                AA            AA)";
