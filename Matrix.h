#ifndef MATRIX_H
#define MATRIX_H
#include <memory>

namespace Standard
{
    //si occupa della allocazione, costruzione, distruzione e deallocazione della matrice
    template<typename T>
    class Matrix_alloc
    {
        public:
            Matrix_alloc(unsigned int _righe, unsigned int _colonne, const T &deafult_value);
            Matrix_alloc(const Matrix_alloc &m);
            Matrix_alloc(Matrix_alloc &&m);
            ~Matrix_alloc();
            Matrix_alloc& operator=(const Matrix_alloc &m);
            Matrix_alloc& operator=(Matrix_alloc &&m);
            void reset() noexcept;
            T& operator[](unsigned int index);
            const T& operator[](unsigned int index) const;
            unsigned int get_size() const noexcept;
            unsigned int get_righe() const noexcept;
            unsigned int get_colonne() const noexcept;
        private:
            void init(const T &value ={});
            void destroy_elements(unsigned int size);
            void check(unsigned int index) const;
            unsigned int righe;
            unsigned int colonne;
            unsigned int sz;
            std::allocator<T> a;
            T *array;
    };
    
    template<typename T>
    class Matrix
    {
        public:
            Matrix(unsigned int righe ={}, unsigned int colonne ={}, const T &default_value ={});
            Matrix(const Matrix &m);
            Matrix(Matrix &&m);
            ~Matrix() =default;
            Matrix& operator=(const Matrix &m);
            Matrix& operator=(Matrix &&m);
            unsigned int size() const noexcept;
            unsigned int righe() const noexcept;
            unsigned int colonne() const noexcept;
            T& value(unsigned int riga, unsigned int colonna);
            const T& value(unsigned int riga, unsigned int colonna) const;
            void espandi_righe(unsigned int righe);
            void espandi_colonne(unsigned int colonne);
            void reset() noexcept;
            void rimuovi_riga(unsigned int colonna);
            void rimuovi_colonna(unsigned int colonna);
            void pop_riga() noexcept;
            void pop_colonna() noexcept;
        private:
            Matrix_alloc<T> m;
    };
    
    template<typename T>
    void copy_array(T *sorgente, T *destinazione, unsigned int size_sorgente);
}

#endif //MATRIX_H