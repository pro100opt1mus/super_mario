target_sources(${PROJECT_NAME}
	PRIVATE
		flying_enemy.cpp
		jumping_enemy.cpp
		moving_platform.cpp
		full_box.cpp
		enemy.cpp
		mario.cpp
		money.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
