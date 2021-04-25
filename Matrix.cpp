#include "Matrix.h"
#include "Matrix_alloc.cpp"
#include <utility>
#include <stdexcept>

//FUNZIONI PUBLICHE
//inizializza i membri interni
template<typename T>
Standard::Matrix<T>::Matrix(unsigned int righe, unsigned int colonne, const T &default_value) : m{ righe, colonne, default_value }
{
    
}

//costruttore di copia
template<typename T>
Standard::Matrix<T>::Matrix(const Matrix &_m) : m( _m.m )
{
    
}

//costruttore di spostamento
template<typename T>
Standard::Matrix<T>::Matrix(Matrix &&_m) : m{ std::move(_m.m) }
{
    
}

//assegnamento per copia
template<typename T>
Standard::Matrix<T>& Standard::Matrix<T>::operator=(const Matrix &_m)
{
    m = _m.m;
    return *this;
}

//assegnamento per spostamento
template<typename T>
Standard::Matrix<T>& Standard::Matrix<T>::operator=(Matrix &&_m)
{
    m = std::move(_m.m);
    return *this;
}

//restituisce il valore di size
template<typename T>
unsigned int Standard::Matrix<T>::size() const noexcept
{
    return m.get_size();
}

//restituisce il valore di righe
template<typename T>
unsigned int Standard::Matrix<T>::righe() const noexcept
{
    return m.get_righe();
}

//restituisce il valore di size
template<typename T>
unsigned int Standard::Matrix<T>::colonne() const noexcept
{
    return m.get_colonne();
}

//ritorna il valore corrispondente alla riga e colonna inserita
template<typename T>
T& Standard::Matrix<T>::value(unsigned int riga, unsigned int colonna)
{
    return m[riga * m.get_colonne() + colonna];
} 

//ritorna il valore corrispondente alla riga e colonna inserita const
template<typename T>
const T& Standard::Matrix<T>::value(unsigned int riga, unsigned int colonna) const
{
    return m[riga * m.get_colonne() + colonna];
} 

//espandi le righe in base al numero inserito
template<typename T>
void Standard::Matrix<T>::espandi_righe(unsigned int righe)
{
    Matrix_alloc<T> temp{ m.get_righe() + righe, m.get_colonne(), T{} };
    for(unsigned int i{0}; i != m.get_size(); ++i)
        temp[i] = m[i];
    m = std::move(temp);
}

//espandi le colonne in base al numero inserito
template<typename T>
void Standard::Matrix<T>::espandi_colonne(unsigned int colonne)
{
    Matrix_alloc<T> temp{ m.get_righe(), m.get_colonne() + colonne, T{} };
    for(unsigned int i{0}, y{0}; i != m.get_size(); ++i, ++y)
    {   
        temp[y] = m[i];
        if( (i + 1) % m.get_colonne() == 0)
            y += colonne;
    }
    m = std::move(temp);
}

//resetta la matrice
template<typename T>
void Standard::Matrix<T>::reset() noexcept
{
    m.reset();
}

//rimuove la riga inserita
template<typename T>
void Standard::Matrix<T>::rimuovi_riga(unsigned int riga)
{
    Matrix_alloc<T> temp{ (m.get_righe()) ? m.get_righe() - 1 : 0, m.get_colonne(), T{} };
    for(unsigned int i{0}, y{0}; y != temp.get_size(); ++i, ++y)
    {
        temp[y] = m[i];
        if(i == riga * m.get_colonne() - 1)
            i += m.get_colonne();
    }
    m = std::move(temp);
}

//rimuove la colonna inserita
template<typename T>
void Standard::Matrix<T>::rimuovi_colonna(unsigned int colonna)
{
    Matrix_alloc<T> temp{ m.get_righe(), (m.get_colonne()) ? m.get_colonne() - 1 : 0, T{} };
    int z{0};
    for(unsigned int i{0}, y{0}; i != m.get_size(); ++i, ++z)
    {
        if(static_cast<unsigned int>(z) != colonna)
        {
            temp[y] = m[i];
            ++y;
        }
        if( (i + 1) % m.get_colonne() == 0)
            z = -1;
    }
    m = std::move(temp);
}

//rimuove l'ultima riga
template<typename T>
void Standard::Matrix<T>::pop_riga() noexcept
{
    rimuovi_riga(m.get_righe() - 1);
}

//rimuove l'ultima colonna
template<typename T>
void Standard::Matrix<T>::pop_colonna() noexcept
{
    rimuovi_colonna(m.get_colonne() - 1);
}

