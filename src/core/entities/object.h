
#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>

struct ObjectData {
    bool solid;
    bool visible;
    bool collidable;
    
    // meta
    int health;
    int maxHealth;
    std::vector<int> textureStates;
};

class Object {
    private:
        ObjectData data;
    public:
        Object();
        ObjectData getData();
        void render(sf::RenderWindow* window);
};
#endif