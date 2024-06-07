#ifndef SPACIAL_HPP
#define SPACIAL_HPP

// everything movement and angle related

#include "position.hpp"

#include <variant>

typedef float ContinuousAngle;
typedef float SpeedCellSizePerSecond;

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
enum class AngleType {
    Wind8,
    Continuous,
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
ContinuousAngle angledeg_mirror(bool over_x_axis, ContinuousAngle val);

class Wind8MovementInfo {
public:
    Wind8MovementInfo() = delete;
    Wind8MovementInfo(Wind8 wind8, DrawnMovementStyle drawn_movement_style) : wind8(wind8), drawn_movement_style(drawn_movement_style), frames_since_last_wind8_move(0) {}
    Wind8 wind8;
    DrawnMovementStyle drawn_movement_style;
    int frames_since_last_wind8_move;
};

class Angle {
public:
    Angle() = delete;
    Angle(AngleType angle_type, const std::variant<Wind8, ContinuousAngle> &angle) : angle_type(angle_type), angle(angle) {}
    AngleType angle_type;
    std::variant<Wind8, ContinuousAngle> angle;
};

class Movement {
public:
    Movement() = delete;
    Movement(AngleType angle_type, const std::variant<Wind8MovementInfo, ContinuousAngle> &angle, SpeedCellSizePerSecond speed = 0.0) : angle_type(angle_type), angle(angle), speed(speed) {}
    AngleType angle_type;
    std::variant<Wind8MovementInfo, ContinuousAngle> angle;
    SpeedCellSizePerSecond speed;
};

#endif // SPACIAL_HPP

