/***************************************************************************
 *
 * Hi Happy Garden
 * Copyright (C) 2023/2024 Antonio Salsi <passy.linux@zresa.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***************************************************************************/

#include "hhg-app/appmain.hpp"


namespace hhg::app
{
inline namespace v1
{

namespace
{

constexpr const char APP_TAG[] = "APP MAIN";

}

app_main::app_main(intf::hardware& hardware) OS_NOEXCEPT
: hardware(hardware)
{

}

app_main::~app_main() OS_NOEXCEPT = default;

os::exit app_main::init(error** error) OS_NOEXCEPT
{

	return os::exit::OK;
}

os::exit app_main::fsm_start(error** error) OS_NOEXCEPT
{
	return os::exit::OK;
}


}
}

