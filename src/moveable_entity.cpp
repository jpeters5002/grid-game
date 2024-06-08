#include "moveable_entity.hpp"

#include <cmath>
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

float angledeg_mirror(bool over_x_axis, float val) {
    if (over_x_axis) {
        return -val;
    } else {
        float unclamped_mirror = ((val - 90.0) * (-1.0)) + 90.0;
        if (unclamped_mirror > 180.0)
            return unclamped_mirror - 360.0;
        else
            return unclamped_mirror;
    }
}

void MoveableEntity::Move(const GridCellIndex &grid_dimensions, int fps) {
    switch (alignment) {
        case EntityAlignment::Indexed: {
            // ASSUMPTION: limit to 1 wind8 movement per frame
            Wind8Movement &w8mov = std::get<0>(movement_angle);
            Wind8Distance dist = Wind8_distance(w8mov.wind8);
            float dist_val = 1.0;
            switch (dist) {
                case Wind8Distance::Zero:
                    assert(!"unreachable");
                    break;
                case Wind8Distance::One:
                    break;
                case Wind8Distance::Sqrt2:
                    dist_val = SQRT2;
                    break;
            }
            float frames_until_move = (dist_val / cell_size_per_second) / fps;
            if (w8mov.frames_since_last_wind8_move >= frames_until_move) {
                GridCellIndex to_add = Wind8_addable_movement(w8mov.wind8);
                GridCellIndex &idx_pos = std::get<0>(this->pos);
                idx_pos.x += to_add.x;
                idx_pos.y += to_add.y;
                // handle boundary cross
                int *vals[2] = {&idx_pos.x, &idx_pos.y};
                int bounds[2] = {grid_dimensions.x, grid_dimensions.y};
                for (int i = 0; i < 2; i++) {
                    if (*vals[i] < 0) {
                        switch (wcb) {
                            case WallCollisionBehavior::Bounce:
                                *vals[i] = -*vals[i] - 1; // minus 1 because the border is "to the left of index 0"
                                w8mov.wind8 = Wind8_mirror(i != 0, w8mov.wind8);
                                break;
                            case WallCollisionBehavior::Clamp:
                                *vals[i] = 0;
                                break;
                            case WallCollisionBehavior::Ignore:
                                break;
                        }
                    }
                    else if (*vals[i] >= bounds[i]) {
                        switch (wcb) {
                            case WallCollisionBehavior::Bounce:
                                *vals[i] = 2 * bounds[i] - *vals[i] - 1;
                                w8mov.wind8 = Wind8_mirror(i != 0, w8mov.wind8);
                                break;
                            case WallCollisionBehavior::Clamp:
                                *vals[i] = bounds[i] - 1;
                                break;
                            case WallCollisionBehavior::Ignore:
                                break;
                        }
                    }
                }
                w8mov.frames_since_last_wind8_move = 0;
                Update();
            } else {
                w8mov.frames_since_last_wind8_move++;
            }
            break;
        }
        case EntityAlignment::Continuous: {
            // TODO: move the entity cell_size_per_second / fps in the direction indicated by std::get<1>(movement_angle), accounting for grid dims
            GridContinuousPosition &cts_pos = std::get<1>(pos);
            float &angle = std::get<1>(movement_angle);
            const float angle_rad = angle * (M_PI/180);
            const float dx = cos(angle_rad) * (cell_size_per_second / fps);
            const float dy = sin(angle_rad) * (cell_size_per_second / fps) * (-1.0); // times -1 because y goes down in CS
            cts_pos.x += dx;
            cts_pos.y += dy;
            // bounds check
            float *vals[2] = {&cts_pos.x, &cts_pos.y};
            const int bounds[2] = {grid_dimensions.x, grid_dimensions.y};
            for (int i = 0; i < 2; i++) {
                if (*vals[i] < 0) {
                    switch (wcb) {
                        case WallCollisionBehavior::Bounce:
                            // TODO: handle multiple bounces in one frame case
                            // TODO: handle the case where crossed tiles are wanted in order (ray casting here we go!)
                            *vals[i] *= -1.0;
                            angle = angledeg_mirror(i != 0, angle);
                            break;
                        case WallCollisionBehavior::Clamp:
                            *vals[i] = 0.0; // TODO: this should maybe be something like 0.3 so that things make sense visually to the player
                            break;
                        case WallCollisionBehavior::Ignore:
                            break;
                    }
                }
                else if (*vals[i] > bounds[i]) {
                    switch (wcb) {
                        case WallCollisionBehavior::Bounce:
                            // TODO: see above "Bounce" todos
                            *vals[i] = bounds[i] * 2 - *vals[i];
                            angle = angledeg_mirror(i != 0, angle);
                            break;
                        case WallCollisionBehavior::Clamp:
                            *vals[i] = bounds[i]; // TODO: this should maybe be something like bounds[i] - 0.3 so that things make sense visually to the player
                            break;
                        case WallCollisionBehavior::Ignore:
                            break;
                    }
                }
            }
            break;
        }
    }
}

