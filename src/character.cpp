#include "character.hpp"

#include <raylib.h>
#include <cmath>

#define SPEED_CELL_SIZE_PER_SECOND 2.0
#define DEFAULT_COMMAND_COOLDOWN_SECONDS 2.0

Character::Character(const GridCellIndex &pos, const Angle &facing_angle) : MoveableEntity(EntityAlignment::Indexed, pos, Movement(AngleType::Wind8, Wind8MovementInfo(Wind8::NoDirection, DrawnMovementStyle::SmoothDrawnSuddenLogic), SPEED_CELL_SIZE_PER_SECOND), WallCollisionBehavior::Clamp), facing_angle(facing_angle), command_cooldown(DEFAULT_COMMAND_COOLDOWN_SECONDS) {}

void Character::Draw(const DrawPosition &grid_tl_pos, float grid_cell_width, float grid_cell_height) {
    GridCellIndex &p = std::get<0>(this->pos);
    DrawCircle((int) (grid_tl_pos.x + ((float)p.x + 0.5) * grid_cell_width), grid_tl_pos.y + ((float)p.y + 0.5) * grid_cell_height, std::min(grid_cell_width, grid_cell_height) / 4.0, GREEN);
}

void Character::Update(int fps) {
    command_cooldown -= 1.0 / fps;
    if (command_cooldown > 0.0)
        return;
    command_cooldown = DEFAULT_COMMAND_COOLDOWN_SECONDS;
    // TODO: this is where it's important to have access to a script manager where we can get the next command and apply it -- maybe we can even have some sort of delay between moves that as a scaling upgrade can be reduced (2 seconds between commands by default and can be lowered down to 1/20 of a second or something for endgame super fast play) and maybe another scaling upgrade to reduce the branching script commands further, even to 0 time so that the character is constantly moving and reacting to its surroundings
    // replace this code eventually

}

