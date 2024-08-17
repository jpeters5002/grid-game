#include "spacial.hpp"

#include <cassert>

Wind8Distance Wind8_distance(Wind8 val) {
    switch (val) {
        case Wind8::NoDirection:
            return Wind8Distance::Zero;
        case Wind8::U:
        case Wind8::R:
        case Wind8::D:
        case Wind8::L:
            return Wind8Distance::One;
        case Wind8::UR:
        case Wind8::DR:
        case Wind8::DL:
        case Wind8::UL:
            return Wind8Distance::Sqrt2;
    }
    assert(!"unreachable");
    return Wind8Distance::Zero;
}

GridCellIndex Wind8_addable_movement(Wind8 val) {
    switch (val) {
        case Wind8::NoDirection:
            return GridCellIndex(0, 0);
        case Wind8::U:
            return GridCellIndex(0, -1);
        case Wind8::UR:
            return GridCellIndex(1, -1);
        case Wind8::R:
            return GridCellIndex(1, 0);
        case Wind8::DR:
            return GridCellIndex(1, 1);
        case Wind8::D:
            return GridCellIndex(0, 1);
        case Wind8::DL:
            return GridCellIndex(-1, 1);
        case Wind8::L:
            return GridCellIndex(-1, 0);
        case Wind8::UL:
            return GridCellIndex(-1, -1);
    }
    assert(!"unreachable");
    return GridCellIndex(0, 0);
}

Wind8 Wind8_mirror(bool over_x_axis, Wind8 val) {
    if (over_x_axis) {
        switch (val) {
            case Wind8::NoDirection:
                return Wind8::NoDirection;
            case Wind8::U:
                return Wind8::D;
            case Wind8::UR:
                return Wind8::DR;
            case Wind8::R:
                return Wind8::R;
            case Wind8::DR:
                return Wind8::UR;
            case Wind8::D:
                return Wind8::U;
            case Wind8::DL:
                return Wind8::UL;
            case Wind8::L:
                return Wind8::L;
            case Wind8::UL:
                return Wind8::DL;
        }
    } else {
        switch (val) {
            case Wind8::NoDirection:
                return Wind8::NoDirection;
            case Wind8::U:
                return Wind8::U;
            case Wind8::UR:
                return Wind8::UL;
            case Wind8::R:
                return Wind8::L;
            case Wind8::DR:
                return Wind8::DL;
            case Wind8::D:
                return Wind8::D;
            case Wind8::DL:
                return Wind8::DR;
            case Wind8::L:
                return Wind8::R;
            case Wind8::UL:
                return Wind8::UR;
        }
    }
    assert(!"unreachable");
    return Wind8::NoDirection;
}

double angledeg_mirror(bool over_x_axis, double val) {
    if (over_x_axis) {
        return -val;
    } else {
        double unclamped_mirror = ((val - 90.0) * (-1.0)) + 90.0;
        if (unclamped_mirror > 180.0)
            return unclamped_mirror - 360.0;
        else
            return unclamped_mirror;
    }
}

ContinuousAngle Angle::GetCts() const {
    switch (angle_type) {
        case AngleType::Wind8:
            switch (std::get<0>(angle)) {
                case Wind8::NoDirection:
                    assert(!"GetCts called on Wind8::NoDirection");
                    return 0.0;
                case Wind8::U:
                    return 90.0;
                case Wind8::UR:
                    return 45.0;
                case Wind8::R:
                    return 0.0;
                case Wind8::DR:
                    return -45.0;
                case Wind8::D:
                    return -90.0;
                case Wind8::DL:
                    return -135.0;
                case Wind8::L:
                    return 180.0;
                case Wind8::UL:
                    return 135.0;
            }
        case AngleType::Continuous:
            return std::get<1>(angle);
    }
    assert(!"unreachable");
    return 0.0;
}
