#pragma once

#include "os_control_settings.hpp"
#include <windows.h>

namespace biv {
	class WindowsControlSettings : public OSControlSettings {
		private:
            CONSOLE_CURSOR_INFO original_cursor{};
            bool cursor_saved = false;
        public:
            ~WindowsControlSettings() override;
            void init() override;
			void set_cursor_start_position() override;
	};
}
