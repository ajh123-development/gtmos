/*
    This file is part of duckOS.
    
    duckOS and GTMOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    duckOS and GTMOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with duckOS and GTMOS.  If not, see <https://www.gnu.org/licenses/>.
    
    Copyright (c) Byteduck 2016-2020. All rights reserved.
*/

#include <csignal>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
#include <cstring>
#include <cstdlib>
//#include <libduck/Config.h>
#include <sstream>
#include <vector>

// The init system for duckOS and GTMOS.

#include <libduck/Log.h>

using Duck::Log;

int main(int argc, char** argv, char** envp) {
	if(getpid() != 1) {
		printf("pid != 1. Exiting.\n");
		return -1;
	}

	system("chown 0 0 /bin/logon");
	system("chmod 4555 /bin/logon");
	
	setsid();
	Log::success("Welcome to GTMOS!");

	// //Read config file
	// auto cfg_res = Config::read_from("/etc/init.conf");
	// if(cfg_res.is_error()) {
	// 	Log::crit("Failed to read /etc/init.conf: ", strerror(errno));
	// 	exit(errno);
	// }
	// auto& cfg = cfg_res.value();

	std::string exec = "/bin/pond";//cfg["init"]["exec"];
	std::stringstream exec_stream(exec);

	//Execute the program given by the exec key in the config
	pid_t pid = fork();
	if(pid == 0) {
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

		Log::err("Failed to execute ", exec, ": ", strerror(errno));
	}

	//Wait for all child processes
	while(1) {
		pid_t pid = waitpid(-1, NULL, 0);
		if(pid < 0 && errno == ECHILD) break; //All child processes exited
	}

	Log::info("All child processes exited. Goodbye!");

	return 0;
}