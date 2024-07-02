#include "bouncing_pellet.hpp"

#include <raylib.h>
#include <cmath>

#define SPEED_CELL_SIZE_PER_SECOND 3.0

BouncingPellet::BouncingPellet(double start_x, double start_y, ContinuousAngle angle) : Entity(EntityAlignment::Continuous, GridContinuousPosition(start_x, start_y), Movement(AngleType::Continuous, angle, SPEED_CELL_SIZE_PER_SECOND), WallCollisionBehavior::Bounce) {}

void BouncingPellet::Draw(const DrawPosition &grid_tl_pos, double grid_cell_width, double grid_cell_height) {
    GridContinuousPosition &p = std::get<1>(pos);
    DrawCircle((int) (grid_tl_pos.x + p.x * grid_cell_width), grid_tl_pos.y + p.y * grid_cell_height, std::min(grid_cell_width, grid_cell_height) / 2.0, BLUE);
}

void BouncingPellet::Update(int fps) {}

