#include "second_level.hpp"
#include "third_level.hpp"
using biv::SecondLevel;
SecondLevel::SecondLevel(UIFactory* factory) : GameLevel(factory) { init_data(); }
biv::GameLevel* SecondLevel::get_next() {
    if (!next) {
        clear_data();
        next = std::make_unique<ThirdLevel>(ui_factory);
    }
    return next.get();
}
void SecondLevel::init_data() {
    ui_factory->create_mario({39, 22}, 3, 3);
    ui_factory->create_ship({20, 25}, 60, 2);
    ui_factory->create_enemy({56, 23}, 3, 2);
    // Sea gap 80..160: 80 cells, beyond a same-height jump (~39 frames).
    ui_factory->create_moving_platform({76, 25}, 14, 2, 74, 0.5f);
    ui_factory->create_ship({160, 25}, 48, 2);
    ui_factory->create_jumping_enemy({182, 23}, 3, 2);
    ui_factory->create_flying_enemy({202, 16}, 3, 2, 22, 0.3f);
    ui_factory->create_ship({214, 22}, 14, 5);
    ui_factory->create_ship({236, 19}, 14, 8);
    ui_factory->create_exit_ship({260, 22}, 18, 5);
}
