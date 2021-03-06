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

// A program that resizes a file.

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("Missing operands\nUsage: truncate FILE LENGTH\n");
		return 1;
	}

	errno = 0;
	long new_len = strtol(argv[2], NULL, 10);
	if((new_len == 0 && errno != 0) || new_len < 0) {
		printf("Invalid argument\n");
		return errno;
	}

	int res = truncate(argv[1], new_len);
	if(res != -1) return 0;
	perror("truncate");
	return errno;
}
