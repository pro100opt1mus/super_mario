// Test-only implementation of the existing OS keyboard interface. The production
// main.cpp, models, controller and Unix renderer are linked without modification.
#include "linux_keyboard.hpp"
#include <fstream>
#include <string>

namespace {
    int level = 1;
    int remaining = 0;
    char action = 's';
    std::ifstream inputs;
    void open_level() {
        inputs.close(); inputs.clear(); remaining = 0;
        if (level <= 3) inputs.open(std::string(REPLAY_DIR)+"/level"+std::to_string(level)+".inputs");
    }
}
biv::UserInput biv::LinuxKeyboard::get_user_input() {
    if (remaining == 0 && !(inputs >> action >> remaining)) return UserInput::EXIT;
    --remaining;
    if(action=='d') return UserInput::MAP_LEFT;
    if(action=='a') return UserInput::MAP_RIGHT;
    if(action=='j') return UserInput::MARIO_JUMP;
    return UserInput::NO_INPUT;
}
void biv::LinuxKeyboard::on() { if (!inputs.is_open()) open_level(); }
void biv::LinuxKeyboard::off() { ++level; open_level(); }
