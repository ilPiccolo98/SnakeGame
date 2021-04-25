#include "Matrix.h"

//FUNZIONI PUBLICHE
//inizializza i membri
template<typename T>
Standard::Matrix_alloc<T>::Matrix_alloc(unsigned int _righe, unsigned int _colonne, const T &default_value) : righe{ _righe }, 
    colonne{ _colonne }, sz{ righe * colonne }, a{ }, array{ (sz != 0) ? a.allocate(sz) : nullptr }
{
    init(default_value);
}

//costruttore di copia
template<typename T>
Standard::Matrix_alloc<T>::Matrix_alloc(const Matrix_alloc &m) : righe{ m.righe }, colonne{ m.colonne }, sz{ m.sz }, a{ m.a }, 
    array{ a.allocate(sz) } 
{
    init();
    copy_array(m.array, array, m.sz);
}

//costruttore di spostamento
template<typename T>
Standard::Matrix_alloc<T>::Matrix_alloc(Matrix_alloc &&m) : righe{ m.righe }, colonne{ m.colonne }, sz{ m.sz }, a{ m.a },
    array{ m.array }
{
    m.righe = 0;
    m.colonne = 0;
    m.sz = 0; 
    m.array = nullptr;
}

//distruttore
template<typename T>
Standard::Matrix_alloc<T>::~Matrix_alloc()
{
    reset();
}

//assegnamento per copia
template<typename T>
Standard::Matrix_alloc<T>& Standard::Matrix_alloc<T>::operator=(const Matrix_alloc &m)
{
    if(this != &m)
    {
        reset();
        righe = m.righe;
        colonne = m.colonne;
        sz = m.sz;
        array = a.allocate(sz);
        init();
        copy_array(m.array, array, sz);
    }        
    return *this;
}

//assegnamento per spostamento
template<typename T>
Standard::Matrix_alloc<T>& Standard::Matrix_alloc<T>::operator=(Matrix_alloc &&m)
{
    if(this != &m)
    {
        reset();
        righe = m.righe;
        colonne = m.colonne;
        sz = m.sz;
        array = m.array;
        m.righe = 0;
        m.colonne = 0;
        m.sz = 0;
        m.array = nullptr;
    }        
    return *this;
}

//cancella l'array e tutti i suoi elementi
template<typename T>
void Standard::Matrix_alloc<T>::reset() noexcept
{
    if(array != nullptr)
    {
        sz = righe = colonne = 0;
        destroy_elements(sz);
        a.deallocate(array, sz);
        array = nullptr;
    }
}

//ritorna l'elemento corrispondente alla posizione inserita
template<typename T>
T& Standard::Matrix_alloc<T>::operator[](unsigned int index)
{
    check(index);
    return array[index];
}

//ritorna l'elemento corrispondente alla posizione inserita const
template<typename T>
const T& Standard::Matrix_alloc<T>::operator[](unsigned int index) const
{
    check(index);
    return array[index];
}

//ritorna il valore di sz
template<typename T>
unsigned int Standard::Matrix_alloc<T>::get_size() const noexcept
{
    return sz;
}

//ritorna il valore di righe
template<typename T>
unsigned int Standard::Matrix_alloc<T>::get_righe() const noexcept
{
    return righe;
}

//ritorna il valore di colonne
template<typename T>
unsigned int Standard::Matrix_alloc<T>::get_colonne() const noexcept
{
    return colonne;
}


//FUNZIONI PRIVATE
//inizializza l'array
template<typename T>
void Standard::Matrix_alloc<T>::init(const T &value)
{
    unsigned int i{ 0 };
    T *temp{ array };
    try
    {
        for(i = 0; i != sz; ++i, ++temp)
        {
            a.construct(temp);
            *temp = value;
        }
    }
    catch(const std::exception&)
    {
        destroy_elements(i);
        throw;
    }
}

//cancella ai numero inserito degli elemeti dell'array
template<typename T>
void Standard::Matrix_alloc<T>::destroy_elements(unsigned int size)
{
    T *temp{ array };
    for(unsigned int i{0}; i != size; ++i, ++temp)
        a.destroy(temp);
}

//controlla l'indice inserito
template<typename T>
void Standard::Matrix_alloc<T>::check(unsigned int index) const
{
    if(index >= sz)
        throw std::out_of_range{ "intervallo troppo alto" };
}

//FUNZIONI HELPER
//copia il contenuto di un array in un'altro
template<typename T>
void Standard::copy_array(T *sorgente, T *destinazione, unsigned int size_sorgente)
{
    for(unsigned int i{0}; i != size_sorgente; ++i)
        destinazione[i] = sorgente[i];
}



