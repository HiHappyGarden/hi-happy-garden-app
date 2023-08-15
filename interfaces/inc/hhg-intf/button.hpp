/***************************************************************************
 *
 * Hi Happy Garden Interfaces
 * Copyright (C) 2023  Antonio Salsi <passy.linux@zresa.it>
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

#pragma once

#include "osal/osal.hpp"

namespace hhg::intf
{
inline namespace v1
{

class button
{
public:
    using on_click = void (*)();

    virtual ~button() OS_NOEXCEPT = default;

    virtual bool init(class os::error**) OS_NOEXCEPT = 0;

    virtual void set_on_click(on_click) OS_NOEXCEPT = 0;

    virtual bool get_status(os::error** error) const OS_NOEXCEPT = 0;
};

}
}