#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "entity.hpp"
#include "position.hpp"

#include <variant>

class Character : Entity{
public:
    Character(const GridCellIndex &pos, const Angle &facing_angle);
    void Draw(const DrawPosition &grid_tl_pos, float grid_cell_width, float grid_cell_height) override;
    void Update(int fps) override;
private:
    Angle facing_angle;
    float command_cooldown;
};

#endif // CHARACTER_HPP

