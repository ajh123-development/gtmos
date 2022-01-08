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

#pragma once

#include <libui/widget/layout/BoxLayout.h>
#include <libui/widget/Button.h>
#include <libui/widget/Label.h>

class LogonWidget: public UI::BoxLayout {
public:
	WIDGET_DEF(LogonWidget)

	UI::Widget::Ptr create_login();

private:
	LogonWidget(UI::Window::Ptr window);
};
