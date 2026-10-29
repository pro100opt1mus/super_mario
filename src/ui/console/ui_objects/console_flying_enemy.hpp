#pragma once
#include "flying_enemy.hpp"
#include "console_ui_obj_rect_adapter.hpp"
namespace biv {
    class ConsoleFlyingEnemy : public FlyingEnemy, public ConsoleUIObjectRectAdapter {
    public:
        ConsoleFlyingEnemy(const Coord&, int width, int height, float travel, float speed);
        char get_brush() const noexcept override;
    };
}
