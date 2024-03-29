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

#include "hhg-app/app-parser.hpp"
using hhg::iface::io_source;

#include "hhg-app/app-parser-commands.hpp"
using namespace os;

namespace hhg::app
{
inline namespace v1
{

namespace
{

constexpr char APP_TAG[] = "APP-PARSER";

}

app_parser::app_parser(const hhg::iface::io::ptr& io, class error** error) OS_NOEXCEPT
: error(nullptr)
, io(io)
, parser(get_commands(), get_commands_size())
{
	if(singleton)
	{
		if(error)
		{
	        *error = OS_ERROR_BUILD("Only one instance at a time", error_type::OS_EFAULT);
	        OS_ERROR_PTR_SET_POSITION(*error);
		}
		return;
	}

	singleton = this;
}


app_parser::~app_parser() OS_NOEXCEPT
{
	singleton = nullptr;
	run = false;
}

os::exit app_parser::init(class error** error) OS_NOEXCEPT
{

	if(!run)
	{
		run = thread.create(nullptr, this->error) == exit::OK;
	}
	else
	{
		if(error)
		{
			*error = OS_ERROR_BUILD("Thread already run", error_type::OS_EFAULT);
	        OS_ERROR_PTR_SET_POSITION(*error);
		}
		return exit::KO;
	}
	return run ? exit::OK : exit::KO;
}

void app_parser::on_receive(io_source source, const uint8_t data[], uint16_t size) const OS_NOEXCEPT
{
	if(data)
	{
		this->source = source;
		buffer.send_from_isr(data, size, 10_ms, error);
	}
}

void* app_parser_thread_handler(void* arg) OS_NOEXCEPT
{
	string<app_parser::singleton->BUFFER_SIZE> buffer;
	string<app_parser::singleton->RET_SIZE> ret;

	while(app_parser::singleton->run)
	{
		char ch = '\0';
		if(app_parser::singleton->buffer.receive(reinterpret_cast<uint8_t *>(&ch), 1, WAIT_FOREVER))
		{
			buffer += ch;

			auto start = buffer.find(app_parser::STARTER_CHAR);
			auto end = buffer.find("\r\n");
			if (end == nullptr)
			{
				end  = buffer.find("\r");
			}
			if (end == nullptr)
			{
				end  = buffer.find("\n");
			}

			if (start && end)
			{
				error* error = nullptr;
				if(app_parser::singleton->parser.execute(buffer.strstr(buffer.c_str() - start, end - start - 1).c_str(), ret.c_str(), ret.size(), &error) == exit::OK)
				{
					ret += app_parser::NEW_LINE;
					app_parser::singleton->io->transmit(reinterpret_cast<const uint8_t*>(ret.c_str()), ret.length());;
				}
				else
				{
					app_parser::singleton->io->transmit(app_parser::KO, sizeof(app_parser::KO) - 1);
					if(error)
					{
						printf_stack_error(APP_TAG, error);
					}
				}
				buffer.clear();
				ret.clear();
			}
			else if (start == nullptr && end)
			{
				app_parser::singleton->io->transmit(app_parser::KO, sizeof(app_parser::KO) - 1);
				buffer.clear();
				ret.clear();
			}
		}
	}

	app_parser::singleton->thread.exit();

	return nullptr;
}

}
}
