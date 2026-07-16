#include "third_level.hpp"

#include "fourth_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* ThirdLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::FourthLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	// Стартовый корабль.
	ui_factory->create_ship({15, 25}, 30, 2);
	ui_factory->create_enemy({20, 5}, 3, 2);
	ui_factory->create_flying_enemy({18, 16}, 3, 2, 15);

	// Море с двумя движущимися платформами.
	ui_factory->create_moving_platform({48, 21}, 6, 1, 18);
	ui_factory->create_moving_platform({80, 18}, 6, 1, 22);

	// Островок с прыгающим врагом.
	ui_factory->create_ship({112, 25}, 15, 2);
	ui_factory->create_jumping_enemy({117, 20}, 3, 2);

	// Башня и корабль с охраной.
	ui_factory->create_ship({135, 19}, 8, 8);
	ui_factory->create_flying_enemy({146, 13}, 3, 2, 18);
	ui_factory->create_ship({150, 25}, 25, 2);
	ui_factory->create_enemy({155, 5}, 3, 2);
	ui_factory->create_enemy({163, 5}, 3, 2);
	ui_factory->create_full_box({160, 14}, 5, 3);

	// Финальный подъём по коробке и высокой платформе.
	ui_factory->create_box({185, 16}, 6, 3);
	ui_factory->create_moving_platform({192, 12}, 6, 1, 14);

	// Финиш: последний добавленный статический объект - конец уровня.
	ui_factory->create_ship({215, 20}, 12, 7);
}
