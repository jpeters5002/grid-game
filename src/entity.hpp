// abstract class for entities that are able to be drawn on the screen

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "position.hpp"
#include <variant>
#include "spacial.hpp"

enum class EntityAlignment {
    Indexed,
    Continuous,
};

class Entity {
public:
    Entity(EntityAlignment alignment, std::variant<GridCellIndex, GridContinuousPosition> pos, const Movement &movement = Movement(AngleType::Continuous, std::variant<Wind8MovementInfo, ContinuousAngle>(0.0f), 0.0), WallCollisionBehavior wcb = WallCollisionBehavior::Ignore) : alignment(alignment), pos(pos), movement(movement), wcb(wcb) {}
    virtual void Draw(const DrawPosition &grid_tl_pos, double grid_cell_width, double grid_cell_height) = 0;
    void Move(const GridCellIndex &grid_dimensions, int fps);
    virtual void Update(int fps) = 0; // called each frame
    EntityAlignment alignment;
    std::variant<GridCellIndex, GridContinuousPosition> pos;
    bool marked_for_deletion = false;
protected:
    Movement movement;
    WallCollisionBehavior wcb;
};

#endif // ENTITY_HPP

