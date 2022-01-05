/*
	This file is part of GTMOS.

	GTMOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	GTMOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with duckOS.  If not, see <https://www.gnu.org/licenses/>.

	Copyright (c) ajh123-development 2016-2021. All rights reserved.
*/

#include <libui/libui.h>
#include "SettingsWidget.h"
#include <libduck/Log.h>

App::Info _app_info;

int main(int argc, char** argv, char** envp) {
	UI::init(argv, envp);

	auto app_res = App::Info::from_current_app();
	if (app_res.has_value())
		_app_info = app_res.value();

	auto window = UI::Window::create();

	const Duck::Path path = _app_info.base_path();
	const char* path_str = path.basename().c_str();
	Duck::Log::info("Path at %s", path_str);

	auto dir_widget = SettingsViewWidget::make(path_str);
	window->set_contents(dir_widget);
	window->set_resizable(true);
	window->set_title("Settings");
	window->resize({300, 300});
	window->show();

	UI::run();
}