/***************************************************************************
 *
 * PROJECT
 * Copyright (C) 202X  Antonio Salsi <passy.linux@zresa.it>
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

#include "hhg/main.h"
#include "osal/osal.hpp"


#ifdef STM32G474xx
int hhg_main(void)
#else
int main(int argc, char* argv[])
#endif
{


	return static_cast<int>(os::exit::OK);
}