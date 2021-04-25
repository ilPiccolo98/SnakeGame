#ifndef GRIGLIA_SNAKE_H
#define GRIGLIA_SNAKE_H
#include "Matrice.h"

namespace Game
{
    class Griglia_snake
    {
        public:
			explicit Griglia_snake(unsigned int righe, unsigned int colonne, unsigned int righe_bianche ={}, unsigned int colonne_bianche = {});
            ~Griglia_snake() =default;
            void stampa() const noexcept;
			unsigned int righe() const noexcept;
			unsigned int colonne() const noexcept;
			unsigned int righe_bianche() const noexcept;
			unsigned int colonne_bianche() const noexcept;
        private:
            void init() noexcept;
			void stampa_righeBianche() const noexcept;
			void stampa_colonneBianche() const noexcept;
			unsigned int spazzi_righe;
			unsigned int spazzi_colonne;
			Standard::Matrix<char> matrix;
    };
}

#endif //GRIGLIA_SNAKE_H
