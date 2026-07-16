#include "fourth_level.hpp"

using biv::FourthLevel;

FourthLevel::FourthLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool FourthLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* FourthLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void FourthLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	// Стартовый корабль: прыгающий враг сторожит выход с корабля.
	ui_factory->create_ship({30, 25}, 20, 2);
	ui_factory->create_jumping_enemy({44, 20}, 3, 2);

	// Длинное море: цепочка узких платформ под охраной летающих врагов.
	ui_factory->create_moving_platform({55, 21}, 4, 1, 15);
	ui_factory->create_flying_enemy({70, 13}, 3, 2, 25);
	ui_factory->create_moving_platform({78, 18}, 4, 1, 15);
	ui_factory->create_flying_enemy({95, 10}, 3, 2, 15);
	ui_factory->create_moving_platform({100, 15}, 4, 1, 12);

	// Крошечный островок, занятый прыгающим врагом.
	ui_factory->create_ship({120, 25}, 8, 2);
	ui_factory->create_jumping_enemy({122, 20}, 3, 2);

	// Высокая башня, вершину которой стережёт летающий враг.
	ui_factory->create_ship({132, 18}, 6, 9);
	ui_factory->create_flying_enemy({140, 12}, 3, 2, 12);

	// Второе море: платформы выше и уже, летун ходит над самой головой.
	ui_factory->create_moving_platform({142, 20}, 4, 1, 16);
	ui_factory->create_moving_platform({165, 16}, 4, 1, 14);
	ui_factory->create_flying_enemy({160, 11}, 3, 2, 30);

	// Финальный остров с тройной охраной.
	ui_factory->create_ship({185, 25}, 20, 2);
	ui_factory->create_enemy({188, 5}, 3, 2);
	ui_factory->create_enemy({193, 5}, 3, 2);
	ui_factory->create_jumping_enemy({198, 20}, 3, 2);

	// Финиш: последний добавленный статический объект - конец уровня.
	ui_factory->create_ship({215, 15}, 10, 12);
}
