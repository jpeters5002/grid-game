#include "moveable_entity.hpp"

#include <cmath>
#include <cassert>

void MoveableEntity::Move(const GridCellIndex &grid_dimensions, int fps) {
    switch (alignment) {
        case EntityAlignment::Indexed: {
            // ASSUMPTION: limit to 1 wind8 movement per frame
            assert(movement.angle_type == AngleType::Wind8);
            Wind8MovementInfo &w8mov = std::get<0>(movement.angle);
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
            float frames_until_move = (dist_val / movement.speed) / fps;
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
            } else {
                w8mov.frames_since_last_wind8_move++;
            }
            break;
        }
        case EntityAlignment::Continuous: {
            assert(movement.angle_type == AngleType::Continuous);
            GridContinuousPosition &cts_pos = std::get<1>(pos);
            float &angle = std::get<1>(movement.angle);
            const float angle_rad = angle * (M_PI/180);
            const float dx = cos(angle_rad) * (movement.speed / fps);
            const float dy = sin(angle_rad) * (movement.speed / fps) * (-1.0); // times -1 because y goes down in CS
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

