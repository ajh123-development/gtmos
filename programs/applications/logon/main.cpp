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

#include <libui/libui.h>
#include <libapp/App.h>
#include <csignal>
#include <sys/wait.h>
#include "LogonWidget.h"

using Duck::Log;


//Event handlers

class LogonCallback: public UI::Callback {
public:
    void init() const {
        Log::info("Longon callback started!");
    };

	void loop() const {
		//TODO: read Control Alt Delete
	};
};

void sigchld_handler(int sig) {
	int dummy;
	wait(&dummy);
}

int main(int argc, char** argv, char** envp) {
	if(getpid() != 5) {
		printf("pid != 5. Exiting.\n");
		return -1;
	}

	//Signal handler
	signal(SIGCHLD, sigchld_handler);

	//Init LibUI
	UI::init(argv, envp);

	//Get display dimensions
	auto dims = UI::pond_context->get_display_dimensions();

	//Make window
	auto window = UI::Window::create();
	auto log_widget = LogonWidget::make(window);

	window->set_contents(log_widget);
	window->set_closeable(false);
	window->set_decorated(true);
	window->set_resizable(true);
	window->set_title("Logon");
	window->resize({300, 300});
	window->show();

	UI::Callback* callback = new LogonCallback();
	UI::run(callback);

	return 0;
}