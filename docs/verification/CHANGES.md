# Изменения относительно db579bf

Все изменения локальны. Новая архитектура вместо преподавательской не вводилась.

| Файл | Зачем и что изменено |
|---|---|
| `README.md` | Добавлены сборка, управление новыми механиками и ссылки на отчёт/обучение; задание сохранено. |
| `docs/DEFENSE_GUIDE_RU.md` | Обучение с основ, реальные диаграммы, карта кода и вопросы к защите. |
| `docs/verification/CHANGES.md` | Этот пофайловый список причин изменений. |
| `docs/verification/STATUS.md` | Проверенный отчёт, команды, результаты, ограничения и оставшиеся человеческие шаги. |
| `docs/verification/baseline-build.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/baseline-configure.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/check-count.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/console-replay-build.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/diagnostic-build.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/final-build.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/final-configure.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/final-tests.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/leaks.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/level1-replay.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/level2-replay.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/level3-replay.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/local-timing-windows.json` | Проверка ближайшего манёвра с вариациями времени. |
| `docs/verification/lsan-unavailable.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/sanitized-final-build.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/sanitized-tests.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/timing-windows.json` | Результаты вариаций времени при неизменном продолжении всей записи. |
| `docs/verification/unix-main-replay.ansi` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/unix-main-replay.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/unix-smoke.ansi` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/unix-smoke.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `docs/verification/windows-configure.log` | Сохранённый фактический журнал или терминальный вывод проверки; трактовка приведена в STATUS.md. |
| `src/CMakeLists.txt` | C++14, CTest и опции диагностик/ASan/UBSan без замены структуры целей. |
| `src/controller/game.cpp` | Снимки кадра, перенос и односторонняя посадка, явный exit, безопасные обходы и снятие регистраций. |
| `src/controller/game.hpp` | Объявлены роли MovingSupport, exit и новые фазы; владение остаётся у фабрики. |
| `src/levels/CMakeLists.txt` | Подключён ThirdLevel. |
| `src/levels/first_level.cpp` | Только явный финиш и unique_ptr для next; исходные координаты/объекты сохранены. |
| `src/levels/game_level.hpp` | Единственный владелец next и виртуальный деструктор цепочки. |
| `src/levels/second_level.cpp` | Новый второй уровень с обязательной переправой и переходом в ThirdLevel. |
| `src/levels/second_level.hpp` | Второй уровень перестал быть финальным. |
| `src/levels/third_level.cpp` | Финальный сложный уровень с тремя переправами, островами, врагами и уступами. |
| `src/levels/third_level.hpp` | Финальный сложный уровень с тремя переправами, островами, врагами и уступами. |
| `src/main.cpp` | Существующий цикл дополнен снимком кадра/посадкой/cleanup; RAII, приоритет смерти и GAME COMPLETE. |
| `src/model/collisionable.cpp` | Реализованы previous geometry и общий относительный критерий контакта сверху. |
| `src/model/collisionable.hpp` | Объявлены снимки геометрии и top-crossing helper. |
| `src/model/game_map.hpp` | Виртуальный деструктор и интерфейс финального сообщения UI. |
| `src/model/map_movable.hpp` | Добавлен дробный move_map_offset(float). |
| `src/model/moving_support.hpp` | Новый небольшой интерфейс previous/current support geometry и deltaX. |
| `src/model/rect.cpp` | Точный getter ширины для float-геометрии. |
| `src/model/rect.hpp` | Объявлен get_width; хранение и округление координат не изменены. |
| `src/model/rect_map_movable_adapter.cpp` | Реализован float offset; A/D используют прежний MAP_STEP. |
| `src/model/rect_map_movable_adapter.hpp` | Объявлен float offset. |
| `src/model/ui_factory.hpp` | Контракт создания новых моделей/exit, отложенной очистки и виртуальный деструктор. |
| `src/objects/CMakeLists.txt` | Подключены три новые модели. |
| `src/objects/enemy.cpp` | Исходное наземное поведение сохранено; stomp переведён на общий критерий. |
| `src/objects/flying_enemy.cpp` | Ограниченный горизонтальный патруль, неизменная высота, препятствия, scroll и общий stomp. |
| `src/objects/flying_enemy.hpp` | Ограниченный горизонтальный патруль, неизменная высота, препятствия, scroll и общий stomp. |
| `src/objects/jumping_enemy.cpp` | Прыжок на месте с исходной физикой, таймер после земли и отдельная обработка потолка. |
| `src/objects/jumping_enemy.hpp` | Прыжок на месте с исходной физикой, таймер после земли и отдельная обработка потолка. |
| `src/objects/mario.cpp` | Точная посадка на moving support с обнулением vertical speed. |
| `src/objects/mario.hpp` | Объявлен land_on; исходная остальная физика сохранена. |
| `src/objects/moving_platform.cpp` | Ship + Movable + MovingSupport: маршрут, фактический deltaX и прокрутка границ. |
| `src/objects/moving_platform.hpp` | Ship + Movable + MovingSupport: маршрут, фактический deltaX и прокрутка границ. |
| `src/os_controls/linux/linux_control_settings.cpp` | Деструктор завершает ncurses через endwin. |
| `src/os_controls/linux/linux_control_settings.hpp` | Объявлен деструктор. |
| `src/os_controls/linux/linux_keyboard.hpp` | Устранено неопределённое начальное значение prev_input. |
| `src/os_controls/os_api/keyboard.hpp` | Виртуальный деструктор для удаления через KeyBoard. |
| `src/os_controls/os_api/os_control_settings.hpp` | Виртуальный деструктор для штатного завершения через базовый тип. |
| `src/os_controls/windows/windows_control_settings.cpp` | Сохраняет и восстанавливает первоначальное состояние курсора. |
| `src/os_controls/windows/windows_control_settings.hpp` | Хранилище состояния курсора и деструктор внутри слоя ОС. |
| `src/ui/console/console_game_map.cpp` | Финальное сообщение через слой отображения. |
| `src/ui/console/console_game_map.hpp` | Объявлен show_game_complete. |
| `src/ui/console/console_ui_factory.cpp` | Создание/регистрация новых классов, типизированное владение, безопасное удаление всех ролей. |
| `src/ui/console/console_ui_factory.hpp` | Типизированные unique_ptr и объявления методов фабрики. |
| `src/ui/console/console_ui_obj.hpp` | Виртуальный деструктор общего полиморфного UI-интерфейса. |
| `src/ui/console/console_ui_obj_rect_adapter.hpp` | Указан override у get_brush для новых и существующих UI-классов. |
| `src/ui/console/ui_objects/CMakeLists.txt` | Подключены четыре новых консольных представления. |
| `src/ui/console/ui_objects/console_exit_ship.cpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `src/ui/console/ui_objects/console_exit_ship.hpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `src/ui/console/ui_objects/console_flying_enemy.cpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `src/ui/console/ui_objects/console_flying_enemy.hpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `src/ui/console/ui_objects/console_jumping_enemy.cpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `src/ui/console/ui_objects/console_jumping_enemy.hpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `src/ui/console/ui_objects/console_moving_platform.cpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `src/ui/console/ui_objects/console_moving_platform.hpp` | Консольное представление новой модели через существующий Rect/UI adapter. |
| `tests/CMakeLists.txt` | Suite без стороннего фреймворка и отдельная необязательная цель console_replay. |
| `tests/game_tests.cpp` | Механики, очистка, exit, рестарты, цепочка 1–3 и диагностика траекторий. |
| `tests/replay_keyboard.cpp` | Только тестовая подстановка записанного ввода для неизменённого main. |
| `tests/replays/level1.inputs` | Воспроизводимая последовательность обычного ввода до настоящего exit соответствующего уровня. |
| `tests/replays/level2.inputs` | Воспроизводимая последовательность обычного ввода до настоящего exit соответствующего уровня. |
| `tests/replays/level3.inputs` | Воспроизводимая последовательность обычного ввода до настоящего exit соответствующего уровня. |
| `tests/run_console_check.py` | Запуск в PTY, проверка вывода/завершения/восстановления режимов терминала. |
