#ifndef SERPENTE_H
#define SERPENTE_H
#include <vector>
#include <utility>

namespace Game
{
    class Serpente
    {
        public:
            explicit Serpente(unsigned int riga, unsigned int colonna);
            ~Serpente() =default;
            void move_up() noexcept;
            void move_down() noexcept;
            void move_left() noexcept;
            void move_right() noexcept;
            void increase();
            std::pair<unsigned int, unsigned int>& testa() noexcept;
            const std::pair<unsigned int, unsigned int>& testa() const noexcept;
            void set_testa(unsigned int riga, unsigned int colonna) noexcept;
            std::pair<unsigned int, unsigned int>& operator[](unsigned int index);
            const std::pair<unsigned int, unsigned int>& operator[](unsigned int index) const;
            unsigned long long size() const noexcept;
            void reset(unsigned int riga, unsigned int colonna) noexcept;
        private:
            void scala_posizione() noexcept;
            std::vector<std::pair<unsigned int, unsigned int>> s;
    };
}

#endif //SERPENTE_H

