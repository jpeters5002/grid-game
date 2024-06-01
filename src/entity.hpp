// abstract class for entities that are able to be drawn on the screen

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "position.hpp"

class Entity {
public:
    virtual void Draw(const DrawPosition &pos) = 0;
    bool marked_for_deletion = false;
};

#endif // ENTITY_HPP

