#include "console_exit_ship.hpp"
using biv::ConsoleExitShip;
ConsoleExitShip::ConsoleExitShip(const Coord& pos, int w, int h) : Ship(pos, w, h) {}
char ConsoleExitShip::get_brush() const noexcept { return '+'; }
