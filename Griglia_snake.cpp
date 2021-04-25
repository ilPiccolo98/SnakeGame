#include "Griglia_snake.h"
#include <iostream>
#include <windows.h>
#include <iomanip>

//FUNZIONI PUBLICHE
//inizializza i membri
Game::Griglia_snake::Griglia_snake(unsigned int righe, unsigned int colonne, unsigned int righe_bianche, unsigned int colonne_bianche) 
	: matrix{ righe, colonne }, spazzi_righe{ righe_bianche }, spazzi_colonne{ colonne_bianche }
{
    init();
}

//stampa la griglia
void Game::Griglia_snake::stampa() const noexcept
{
	stampa_righeBianche();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	for (unsigned int i{ 0 }; i != matrix.righe(); ++i)
	{
		stampa_colonneBianche();
		for (unsigned int y{ 0 }; y != matrix.colonne(); ++y)
			std::cout << matrix.value(i, y);
		std::cout << '\n';
	}
}

//ritorna il valore di righe
unsigned int Game::Griglia_snake::righe() const noexcept
{
	return matrix.righe();
}

//ritorna il valore di colonne
unsigned int Game::Griglia_snake::colonne() const noexcept
{
	return matrix.colonne();
}

//ritorna il valore di spazzi righe
unsigned int Game::Griglia_snake::righe_bianche() const noexcept
{
	return spazzi_righe;
}

//ritorna il valore di spazzi colonne
unsigned int Game::Griglia_snake::colonne_bianche() const noexcept
{
	return spazzi_colonne;
}

//FUNZIONI PRIVATE
//inizializza la griglia
void Game::Griglia_snake::init() noexcept
{
    for(unsigned int i{0}; i != matrix.righe(); ++i)
        for(unsigned int y{0}; y != matrix.colonne(); ++y)
        {
            if(i == 0 || i == matrix.righe() - 1)
				matrix.value(i, y) = static_cast<char>(205);
            else if(y == 0 || y == matrix.colonne() - 1)
				matrix.value(i, y) = static_cast<char>(206);
            else
				matrix.value(i, y) = '\0';
        }
}

//stampa delle righe nuove a seconda del valore di spazzi righe
void Game::Griglia_snake::stampa_righeBianche() const noexcept
{
	for (unsigned int i{ 0 }; i != spazzi_righe; ++i)
		std::cout << '\n';
}

//stampa delle righe nuove a seconda del valore di spazzi colonne
void Game::Griglia_snake::stampa_colonneBianche() const noexcept
{
	for (unsigned int i{ 0 }; i != spazzi_colonne; ++i)
		std::cout << ' ';
}


