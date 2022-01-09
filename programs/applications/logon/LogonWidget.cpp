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
#include <libduck/Config.h>
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

Widget::Ptr LogonWidget::create_login(UI::Window::Ptr& window) {
	auto btn = UI::Button::make("Login");
	btn->on_released = [&] {
		window->hide();

		//Read config file
		auto cfg_res = Duck::Config::read_from("/etc/init.conf");
		if(cfg_res.is_error()) {
			Log::crit("Failed to read /etc/init.conf: ", strerror(errno));
			exit(errno);
		}
		auto& cfg = cfg_res.value();

		std::string exec = cfg["init"]["exec"];
		std::stringstream exec_stream(exec);

		if(!fork()) {
			//Split arguments from exec command
			std::vector<std::string> args;
			std::string arg;
			while(std::getline(exec_stream, arg, ' '))
				args.push_back(arg);

			//Convert c++ string vector into cstring array
			const char* c_args[args.size() + 1];
			for(auto i = 0; i < args.size(); i++)
				c_args[i] = args[i].c_str();
			c_args[args.size()] = NULL;

			char* env[] = {NULL};

			//Execute the command
			execve(c_args[0], (char* const*) c_args, env);
			exit(-1);
		}
		return true;
	};
	return btn;
}