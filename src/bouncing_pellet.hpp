#ifndef BOUNCING_PELLET_HPP
#define BOUNCING_PELLET_HPP

#include "moveable_entity.hpp"

class BouncingPellet : public MoveableEntity {
public:
    BouncingPellet(float start_x, float start_y, float angle);
    void Draw(const DrawPosition &grid_tl_pos, float grid_cell_width, float grid_cell_height) override;
    void Update(int fps) override;
};

#endif // BOUNCING_PELLET_HPP

