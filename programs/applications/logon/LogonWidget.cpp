/*
	This file is part of duckOS.

	duckOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	duckOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with duckOS.  If not, see <https://www.gnu.org/licenses/>.

	Copyright (c) Byteduck 2016-2021. All rights reserved.
*/

#include "LogonWidget.h"
#include <libduck/Log.h>
#include <system_error>

using namespace UI;

LogonWidget::LogonWidget(UI::Window::Ptr window) {
	UI::Label::Ptr display = Label::make("0");
	display->set_alignment(UI::CENTER, UI::END);
	display->set_font(UI::pond_context->get_font("gohu-14"));
	display->set_padding({8, 8});
	add_child(display);
	add_child(create_login(window));
}

Widget::Ptr LogonWidget::create_login(UI::Window::Ptr window) {
	auto btn = UI::Button::make("Login");
	btn->on_released = [&] {
		window->hide();

		if(!fork()) {
			char* argv[] = {NULL};
			char* envp[] = {NULL};
			execve("/bin/sandbar", argv, envp);
			exit(-1);
		}
		return true;
	};
	return btn;
}