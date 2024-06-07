#ifndef MOVEABLE_ENTITY_HPP
#define MOVEABLE_ENTITY_HPP

// abstract class for all moveable entities, which must also be drawable

#include "entity.hpp"
#include "position.hpp"
#include "spacial.hpp"

class MoveableEntity : public Entity {
public:
    MoveableEntity(EntityAlignment alignment, const std::variant<GridCellIndex, GridContinuousPosition> &pos, const Movement &movement, WallCollisionBehavior wcb) : Entity(alignment, pos), movement(movement), wcb(wcb) {}
    void Move(const GridCellIndex &grid_dimensions, int fps);
    virtual void Update(int fps) = 0; // called each frame
protected:
    Movement movement; // is 0 if Entity::alignment == EntityAlignment::Indexed and 1 otherwise (1 is deg ccw from east)
    WallCollisionBehavior wcb;
    float cell_size_per_second = 0.0; // 0 if not moving currently, obviously
};

#endif // MOVEABLE_ENTITY_HPP

