#include "windows_control_settings.hpp"

#include <windows.h>

using biv::WindowsControlSettings;

void WindowsControlSettings::init() {
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	cursor_saved = GetConsoleCursorInfo(handle, &original_cursor) != 0;
    if (!cursor_saved) return;
    structCursorInfo = original_cursor;
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void WindowsControlSettings::set_cursor_start_position() {
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

WindowsControlSettings::~WindowsControlSettings() {
    if (cursor_saved) SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &original_cursor);
}
