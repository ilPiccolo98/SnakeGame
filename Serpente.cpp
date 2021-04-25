#include "Serpente.h"

//FUNZIONI PUBLICHE
//inizializzo i membri
Game::Serpente::Serpente(unsigned int riga, unsigned int colonna) : s{ { riga, colonna } }
{
    
}

//sposta di una casella verso l'alto gli elementi
void Game::Serpente::move_up() noexcept
{
    scala_posizione();
    s[0].first -= 1;
}

//sposta di una casella verso il basso gli elementi
void Game::Serpente::move_down() noexcept
{
    scala_posizione();
    s[0].first += 1;
}

//sposta di una casella verso sinistra gli elementi
void Game::Serpente::move_left() noexcept
{
    scala_posizione();
    s[0].second -= 1;
}

//sposta di una casella verso sinistra gli elementi
void Game::Serpente::move_right() noexcept
{
    scala_posizione();
    s[0].second += 1;
}

//ritorna il valore corrispondente all'indice
std::pair<unsigned int, unsigned int>& Game::Serpente::operator[](unsigned int index)
{
    return s[index];
}

//ritorna il valore corrispondente all'indice
const std::pair<unsigned int, unsigned int>& Game::Serpente::operator[](unsigned int index) const
{
    return s[index];
}

//ritorna la lunghezza del serpente
unsigned long long Game::Serpente::size() const noexcept
{
    return s.size();
}

//aumenta la lunghezza del serpente
void Game::Serpente::increase() 
{
    s.push_back( { s[s.size() - 1].first, s[s.size() - 1].second } );
}

//resetta il serpente
void Game::Serpente::reset(unsigned int riga, unsigned int colonna) noexcept
{
    s.clear();
    s.push_back( { riga, colonna } );
}

//ritorna il primo elemento di serpente
std::pair<unsigned int, unsigned int>& Game::Serpente::testa() noexcept
{
    return s[0];
}

//ritorna il primo elemento di serpente const 
const std::pair<unsigned int, unsigned int>& Game::Serpente::testa() const noexcept
{
    return s[0];
}

//setta la posizione della testa
void Game::Serpente::set_testa(unsigned int riga, unsigned int colonna) noexcept
{
    scala_posizione();
    s[0].first = riga;
    s[0].second = colonna;
}

//FUNZIONI PRIVATE
//ogni elemento copia le coordinate del successivo tranne l'ultimo
void Game::Serpente::scala_posizione() noexcept
{
    for(unsigned long long i{s.size() - 1}; i != 0; --i)
        s[i] = s[i - 1];
}