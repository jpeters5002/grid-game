#ifndef MOVEABLE_ENTITY_HPP
#define MOVEABLE_ENTITY_HPP

// abstract class for all moveable objects, which must also be drawable objects

#include "drawable_object.hpp"
#include "position.hpp"

enum class MovementStyle {
    Smooth,
    Sudden,
    SmoothDrawnSuddenLogic,
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

class MoveableEntity : Entity {
public:
};
    void Move(int fps) final;
    virtual void Update() = 0;
protected:
    Wind8 wind8; // NoDirection if using velocity_angle_deg
    float velocity_angle_deg; // NAN if using wind8 -- range: (-180, 180] where 0 is east and + is ccw
    float cell_size_per_second; // TODO: determine how to handle different screen sizes equally. Perhaps every x and y value in the grid should be in [0, 1], except then there's a conversion between x and y... hmmmmm
};

#endif // MOVEABLE_ENTITY_HPP

