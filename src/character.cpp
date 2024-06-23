#include "character.hpp"

#include <raylib.h>
#include <cmath>

#define SPEED_CELL_SIZE_PER_SECOND 2.0
#define DEFAULT_COMMAND_COOLDOWN_SECONDS 2.0

Character::Character(const GridCellIndex &pos, const Angle &facing_angle) : Entity(EntityAlignment::Indexed, pos, Movement(AngleType::Wind8, Wind8MovementInfo(Wind8::NoDirection, DrawnMovementStyle::SmoothDrawnSuddenLogic), SPEED_CELL_SIZE_PER_SECOND), WallCollisionBehavior::Clamp), facing_angle(facing_angle), command_cooldown(DEFAULT_COMMAND_COOLDOWN_SECONDS) {}

void Character::Draw(const DrawPosition &grid_tl_pos, float grid_cell_width, float grid_cell_height) {
    GridCellIndex &p = std::get<0>(this->pos);
    DrawPosition dp((int) (grid_tl_pos.x + ((float)p.x + 0.5) * grid_cell_width), (int) (grid_tl_pos.y + ((float)p.y + 0.5) * grid_cell_height), DrawPositionType::Center);
    float radius = std::min(grid_cell_width, grid_cell_height) / 4.0;
    DrawCircle(dp.x, dp.y, radius, GREEN);
    ContinuousAngle ang_rad = this->facing_angle.GetCts() * (M_PI/180);
    Vector2 helper_point = {(radius / 4) * cos(ang_rad), (radius / 4) * sin(ang_rad)}; // point to help get the two points within the circle
    Vector2 triangle_points[3] = {
        {dp.x + radius * 1.5 * cos(ang_rad), dp.y + (-1) * radius * 1.5 * sin(ang_rad)},
        {dp.x + helper_point.x + (radius * 3 / 4) * cos(ang_rad + (M_PI / 2)), dp.y + (-1) * (helper_point.y + (radius * 3 / 4) * sin(ang_rad + (M_PI / 2)))},
        {dp.x + helper_point.x + (radius * 3 / 4) * cos(ang_rad - (M_PI / 2)), dp.y + (-1) * (helper_point.y + (radius * 3 / 4) * sin(ang_rad - (M_PI / 2)))},
    };
    DrawTriangle(triangle_points[0], triangle_points[1], triangle_points[2], GREEN);
}

void Character::Update(int fps) {
    command_cooldown -= 1.0 / fps;
    if (command_cooldown > 0.0)
        return;
    command_cooldown = DEFAULT_COMMAND_COOLDOWN_SECONDS;
    // DEBUG CODE:
    Wind8 &w8 = std::get<0>(facing_angle.angle);
    switch (w8) {
        case Wind8::U:
            w8 = Wind8::UR;
            break;
        case Wind8::UR:
            w8 = Wind8::R;
            break;
        case Wind8::R:
            w8 = Wind8::DR;
            break;
        case Wind8::DR:
            w8 = Wind8::D;
            break;
        case Wind8::D:
            w8 = Wind8::DL;
            break;
        case Wind8::DL:
            w8 = Wind8::L;
            break;
        case Wind8::L:
            w8 = Wind8::UL;
            break;
        case Wind8::UL:
            w8 = Wind8::U;
            break;
    }
    // END DEBUG CODE
    // TODO: this is where it's important to have access to a script manager where we can get the next command and apply it -- maybe we can even have some sort of delay between moves that as a scaling upgrade can be reduced (2 seconds between commands by default and can be lowered down to 1/20 of a second or something for endgame super fast play) and maybe another scaling upgrade to reduce the branching script commands further, even to 0 time so that the character is constantly moving and reacting to its surroundings
    // replace this code eventually

}

