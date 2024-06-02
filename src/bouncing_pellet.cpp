#include "bouncing_pellet.hpp"

#include <raylib.h>
#include <cmath>

#define SPEED_CELL_SIZE_PER_SECOND 3.0

BouncingPellet::BouncingPellet(float start_x, float start_y, float angle) : MoveableEntity(EntityAlignment::Continuous, GridContinuousPosition(start_x, start_y), angle, WallCollisionBehavior::Bounce) {
    cell_size_per_second = SPEED_CELL_SIZE_PER_SECOND;
}

void BouncingPellet::Draw(const DrawPosition &grid_tl_pos, float grid_cell_width, float grid_cell_height) {
    DrawCircle((int) (grid_tl_pos.x + std::get<1>(pos).x * grid_cell_width), grid_tl_pos.y + std::get<1>(pos).y * grid_cell_height, std::min(grid_cell_width, grid_cell_height) / 2.0, BLUE);
}

void BouncingPellet::Update() {}

