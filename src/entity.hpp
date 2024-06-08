// abstract class for entities that are able to be drawn on the screen

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "position.hpp"
#include <variant>

enum class EntityAlignment {
    Indexed,
    Continuous,
};

class Entity {
public:
    Entity(EntityAlignment alignment, std::variant<GridCellIndex, GridContinuousPosition> pos) : alignment(alignment), pos(pos) {}
    virtual void Draw(const DrawPosition &grid_tl_pos, float grid_cell_width, float grid_cell_height) = 0;
    EntityAlignment alignment;
    std::variant<GridCellIndex, GridContinuousPosition> pos;
    bool marked_for_deletion = false;
};

#endif // ENTITY_HPP

