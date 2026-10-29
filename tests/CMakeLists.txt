# Reuse the application's source/include inventory without changing its build layout.
get_target_property(game_sources super_mario SOURCES)
get_target_property(game_includes super_mario INCLUDE_DIRECTORIES)
list(FILTER game_sources EXCLUDE REGEX "(^|/)main[.]cpp$")
list(FILTER game_sources EXCLUDE REGEX "/os_controls/")
add_executable(game_tests game_tests.cpp ${game_sources})
target_include_directories(game_tests PRIVATE ${game_includes})
target_compile_features(game_tests PRIVATE cxx_std_14)
add_test(NAME assignment_mechanics COMMAND game_tests)

target_compile_definitions(game_tests PRIVATE REPLAY_DIR="${CMAKE_CURRENT_SOURCE_DIR}/replays")

# Optional Unix integration check: real main and renderer, deterministic keyboard.
# The ordinary super_mario target always uses the real OS keyboard implementation.
if(GAME_TYPE STREQUAL "LinuxConsole")
    get_target_property(console_sources super_mario SOURCES)
    list(REMOVE_ITEM console_sources main.cpp)
    list(FILTER console_sources EXCLUDE REGEX "/linux_keyboard[.]cpp$")
    add_executable(console_replay EXCLUDE_FROM_ALL
        ${CMAKE_SOURCE_DIR}/main.cpp replay_keyboard.cpp ${console_sources})
    target_include_directories(console_replay PRIVATE ${game_includes})
    target_compile_features(console_replay PRIVATE cxx_std_14)
    target_compile_definitions(console_replay PRIVATE LINUX_CONSOLE REPLAY_DIR="${CMAKE_CURRENT_SOURCE_DIR}/replays")
    target_link_libraries(console_replay ncurses pthread)
endif()
