/***************************************************************************
 *
 * Hi Happy Garden
 * Copyright (C) 2023/2024  Antonio Salsi <passy.linux@zresa.it>
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

#include "hhg-driver/hardware.hpp"
#include "hhg-driver/os-config.hpp"
#include "pico/pico-uart.hpp"
#include "pico/pico-time.hpp"
#include "pico/pico-fs-io.hpp"

using namespace os;
using namespace hhg::iface;

namespace hhg::driver
{
inline namespace v1
{

namespace
{

constexpr const char APP_TAG[] = "HARDWARE";

}

hardware::hardware(class error** error) OS_NOEXCEPT
: time(new hhg::driver::pico_time)
, uart(new hhg::driver::pico_uart)
, fsio(new hhg::driver::pico_fsio(static_cast<uint32_t>(0), static_cast<uint32_t>(0)  ))
{
    if(time.get() == nullptr && error)
    {
        *error = OS_ERROR_BUILD("io(new hhg::driver::stm32_timer) no mem.", error_type::OS_ENOMEM);
        OS_ERROR_PTR_SET_POSITION(*error);
        return;
    }

    if(uart.get() == nullptr && error)
	{
        *error = OS_ERROR_BUILD("io(new hhg::driver::pico_uart) no mem.", error_type::OS_ENOMEM);
        OS_ERROR_PTR_SET_POSITION(*error);
        return;
    }

    if(fsio.get() == nullptr && error)
	{
        *error = OS_ERROR_BUILD("io(new hhg::driver::stm32_fsio) no mem.", error_type::OS_ENOMEM);
        OS_ERROR_PTR_SET_POSITION(*error);
        return;
    }

}

os::exit hardware::init(error** error) OS_NOEXCEPT
{
	OS_LOG_INFO(APP_TAG, "Init OS Config");
	if(os_config_init() == os::exit::KO)
	{
		return exit::KO;
	}
	OS_LOG_INFO(APP_TAG, "Init OS Config - OK");

    OS_LOG_INFO(APP_TAG, "Init Time");
    auto time_init = reinterpret_cast<hhg::iface::time_init *>(time.get());
    if(time_init == nullptr)
    {
        if(error && *error)
        {
            *error = OS_ERROR_APPEND(*error, " reinterpret_cast<hhg::iface::time_init *>(time.get()) fail.", error_type::OS_EFAULT);
            OS_ERROR_PTR_SET_POSITION(*error);
        }
        return exit::KO;
    }
    if(time_init->init(error) == exit::KO)
    {
        if(error && *error)
        {
            *error = OS_ERROR_APPEND(*error, "io::init() fail.", error_type::OS_EFAULT);
            OS_ERROR_PTR_SET_POSITION(*error);
        }
        return exit::KO;
    }
    OS_LOG_INFO(APP_TAG, "Init Time - OK");

	OS_LOG_INFO(APP_TAG, "Init UART");
	if(uart->init(error) == exit::KO)
	{
		if(error && *error)
		{
	        *error = OS_ERROR_APPEND(*error, "io::init() fail.", error_type::OS_EFAULT);
	        OS_ERROR_PTR_SET_POSITION(*error);
		}
		return exit::KO;
	}
	OS_LOG_INFO(APP_TAG, "Init UART - OK");

	OS_LOG_INFO(APP_TAG, "Init FS IO");
	if(fsio->init(error) == exit::KO)
	{
		if(error && *error)
		{
	        *error = OS_ERROR_APPEND(*error, "fsio::init() fail.", error_type::OS_EFAULT);
	        OS_ERROR_PTR_SET_POSITION(*error);
		}
		return exit::KO;
	}
	OS_LOG_INFO(APP_TAG, "Init FS IO - OK");

	return exit::OK;
}

const string<128>& hardware::get_info() OS_NOEXCEPT
{
	static string<128> ret;

	return ret;
}


const string<128>& hardware::get_version() OS_NOEXCEPT
{
	static string<128> ret;

	return ret;
}


}
}

