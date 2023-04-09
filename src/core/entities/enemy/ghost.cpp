#include <SFML/Graphics.hpp>
#include <iostream>

#include "enemy.h"

class Ghost : public Enemy {
    private:
        int id;
    public:
        Ghost(TextureManager *textureManager) {
            std::cout << "Ghost created" << std::endl;
            id = rand() % 1000;
        }
        ~Ghost() {
            std::cout << "Ghost destroyed" << std::endl;
        }

        void update(int tick, Level level) override {
            // std::cout << "Ghost updated: " << id << std::endl;
        }
};