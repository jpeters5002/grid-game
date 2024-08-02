#ifndef SPACIAL_HPP
#define SPACIAL_HPP

// everything movement and angle related

#include "position.hpp"

#include <cassert>
#include <variant>

typedef double ContinuousAngle;
typedef double SpeedCellSizePerSecond;

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
    U,
    UR,
    R,
    DR,
    D,
    DL,
    L,
    UL,
    NoDirection,
};
constexpr const char *str_from_wind8(Wind8 val) {
    switch (val)
    {
        case Wind8::U:
            return "u";
        case Wind8::UR:
            return "ur";
        case Wind8::R:
            return "r";
        case Wind8::DR:
            return "dr";
        case Wind8::D:
            return "d";
        case Wind8::DL:
            return "dl";
        case Wind8::L:
            return "l";
        case Wind8::UL:
            return "ul";
        case Wind8::NoDirection:
            return "nodirection";
    }
    assert(!"unreachable");
    return "[INVALID ENUM VALUE]";
}
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
static const double SQRT2 = 1.41421356237;
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
    ContinuousAngle GetCts() const;
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

