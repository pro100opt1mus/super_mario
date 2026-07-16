#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	// Стартовый корабль.
	ui_factory->create_ship({10, 25}, 50, 2);
	ui_factory->create_full_box({25, 15}, 5, 3);
	ui_factory->create_box({45, 15}, 8, 3);
	ui_factory->create_enemy({30, 5}, 3, 2);
	ui_factory->create_jumping_enemy({52, 20}, 3, 2);

	// Море: движущаяся платформа перевозит Марио на второй корабль.
	ui_factory->create_moving_platform({62, 20}, 8, 1, 20);

	// Второй корабль под охраной летающего врага.
	ui_factory->create_ship({95, 25}, 40, 2);
	ui_factory->create_flying_enemy({100, 15}, 3, 2, 25);
	ui_factory->create_enemy({110, 5}, 3, 2);
	ui_factory->create_full_box({115, 15}, 5, 3);

	// Башня посреди моря.
	ui_factory->create_ship({140, 20}, 8, 7);

	// Третий корабль.
	ui_factory->create_ship({155, 25}, 30, 2);
	ui_factory->create_jumping_enemy({165, 20}, 3, 2);
	ui_factory->create_flying_enemy({150, 12}, 3, 2, 20);

	// Финиш: последний добавленный статический объект - конец уровня.
	ui_factory->create_ship({200, 20}, 12, 7);
}
