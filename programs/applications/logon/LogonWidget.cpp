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
	along with GTMOS.  If not, see <https://www.gnu.org/licenses/>.

	Copyright (c) Byteduck 2016-2021. All rights reserved.
*/

#include "LogonWidget.h"
#include <libduck/Log.h>
#include <system_error>

using namespace UI;
using Duck::Log;

LogonWidget::LogonWidget(UI::Window::Ptr& window): BoxLayout(VERTICAL) {
	UI::Label::Ptr display = Label::make("Press Control Alt Delete to login");
	display->set_alignment(UI::CENTER, UI::END);
	display->set_font(UI::pond_context->get_font("gohu-14"));
	display->set_padding({8, 8});
	add_child(display);
	add_child(create_login(window));
}

bool LogonWidget::on_keyboard(Pond::KeyEvent evt){
	bool control = KBD_MOD_CTRL && evt.modifiers;
	bool alt = KBD_MOD_ALT && evt.modifiers;
	if(control && alt){
		char* bptr = (char*)evt.key;
		Log::info(bptr);
	}
	return false;
}

Widget::Ptr LogonWidget::create_login(UI::Window::Ptr& window) {
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