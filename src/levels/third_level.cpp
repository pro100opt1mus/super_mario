#include "third_level.hpp"
using biv::ThirdLevel;
ThirdLevel::ThirdLevel(UIFactory* factory) : GameLevel(factory) { init_data(); }
biv::GameLevel* ThirdLevel::get_next() { return nullptr; }
bool ThirdLevel::is_final() const noexcept { return true; }
void ThirdLevel::init_data() {
    ui_factory->create_mario({39, 22}, 3, 3);
    ui_factory->create_ship({20, 25}, 45, 2);
    // Three mandatory crossings, with safe waiting room on each island.
    ui_factory->create_moving_platform({61, 25}, 8, 2, 72, 0.5f);
    ui_factory->create_ship({135, 25}, 22, 2);
    ui_factory->create_jumping_enemy({148, 23}, 3, 2);
    ui_factory->create_moving_platform({153, 25}, 8, 2, 72, 0.6f);
    ui_factory->create_flying_enemy({177, 17}, 3, 2, 26, 0.35f);
    ui_factory->create_ship({227, 25}, 22, 2);
    ui_factory->create_jumping_enemy({240, 23}, 3, 2);
    ui_factory->create_moving_platform({245, 25}, 6, 2, 74, 0.45f);
    ui_factory->create_flying_enemy({274, 16}, 3, 2, 24, 0.4f);
    ui_factory->create_ship({321, 25}, 18, 2);
    ui_factory->create_jumping_enemy({331, 23}, 3, 2);
    ui_factory->create_ship({349, 22}, 9, 5);
    ui_factory->create_ship({369, 18}, 8, 9);
    ui_factory->create_flying_enemy({359, 12}, 3, 2, 18, 0.25f);
    ui_factory->create_exit_ship({393, 22}, 15, 5);
}
