#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "entity.hpp"
#include "position.hpp"

#include <variant>

namespace script
{
    class ScriptHandler;
}

class Character : public Entity {
public:
    Character(script::ScriptHandler &script_handler, const GridCellIndex &pos, const Angle &facing_angle);
    void Draw(const DrawPosition &grid_tl_pos, double grid_cell_width, double grid_cell_height) override;
    void Update(int fps) override;
    void QueueNextCommand();
private:
    script::ScriptHandler &script_handler;
    Angle facing_angle;
    double command_cooldown;
    bool command_queued;
};

#endif // CHARACTER_HPP

