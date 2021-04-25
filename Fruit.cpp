#include "Fruit.h"
#include <cstdlib>
#include <ctime>

//FUNZIONI PUBLICHE
//inizializza i membri
Game::Fruit::Fruit() : fruit{ 0, 0 }
{
    std::srand( std::time(nullptr) );
}

//ritorna il valore di riga
unsigned int Game::Fruit::get_riga() const noexcept
{
    return fruit.first;
}

//ritorna il valore di colonna
unsigned int Game::Fruit::get_colonna() const noexcept
{
    return fruit.second;
}

//genera e imposta con numeri casuali riga e colonna
void Game::Fruit::generate(unsigned int min_riga, unsigned int max_righe, unsigned int min_colonna, unsigned int max_colonne) noexcept 
{
    fruit.first = random(min_riga, max_righe);
    fruit.second = random(min_colonna, max_colonne);
}

//genera e ritorna un numero casuale
int Game::Fruit::random(unsigned int min, unsigned int max) const noexcept
{
    return (std::rand() % (max - 1)) + min;
}

