#ifndef MOVEABLE_ENTITY_HPP
#define MOVEABLE_ENTITY_HPP

// abstract class for all moveable objects, which must also be drawable objects

#include "entity.hpp"
#include "position.hpp"

// the "smooth" option is indicated by EntityAlignment::Continuous -- these options specify between how 
enum class DrawnMovementStyle {
    Sudden,
    SmoothDrawnSuddenLogic,
};

enum class WallCollisionBehavior {
    Bounce,
    Clamp,
    Ignore,
};

enum class Wind8 {
    NoDirection,
    U,
    UR,
    R,
    DR,
    D,
    DL,
    L,
    UL,
};
enum class Wind8Distance {
    Zero,
    One,
    Sqrt2,
};
Wind8Distance Wind8_distance(Wind8 val);
static const float SQRT2 = 1.41421356237;
GridCellIndex Wind8_addable_movement(Wind8 val);
Wind8 Wind8_mirror(bool over_x_axis, Wind8 val);
float angledeg_mirror(bool over_x_axis, float val);

class Wind8Movement {
public:
    Wind8Movement() = delete;
    Wind8Movement(Wind8 wind8, DrawnMovementStyle drawn_movement_style) : wind8(wind8), drawn_movement_style(drawn_movement_style), frames_since_last_wind8_move(0) {}
    Wind8 wind8;
    DrawnMovementStyle drawn_movement_style;
    int frames_since_last_wind8_move;
};

class MoveableEntity : public Entity {
public:
    MoveableEntity(EntityAlignment alignment, const std::variant<GridCellIndex, GridContinuousPosition> &pos, const std::variant<Wind8Movement, float> &movement_angle, WallCollisionBehavior wcb) : Entity(alignment, pos), movement_angle(movement_angle), wcb(wcb) {}
    void Move(const GridCellIndex &grid_dimensions, int fps);
    virtual void Update() = 0; // called each time the entity moves
protected:
    std::variant<Wind8Movement, float> movement_angle; // is 0 if Entity::alignment == EntityAlignment::Indexed and 1 otherwise (1 is deg ccw from east)
    WallCollisionBehavior wcb;
    float cell_size_per_second = 0.0; // 0 if not moving currently, obviously
};

#endif // MOVEABLE_ENTITY_HPP

