#ifndef FRUIT_H
#define FRUIT_H
#include <utility>

namespace Game
{
    class Fruit 
    {
        public:
            explicit Fruit();
            ~Fruit() =default;
            unsigned int get_riga() const noexcept;
            unsigned int get_colonna() const noexcept;
			void generate(unsigned int min_riga, unsigned int max_righe, unsigned int min_colonna, unsigned int max_colonne) noexcept;
        private:
            int random(unsigned int min, unsigned int max) const noexcept;
            std::pair<unsigned int, unsigned int> fruit;
    };
}

#endif //FRUIT_H
