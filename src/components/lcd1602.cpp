// MIT License
//
// Copyright (c) 2021 Happy GardenPI
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "lcd1602.hpp"

#include <cstdarg>

#include <stdexcept>
using std::runtime_error;

#include <wiringPi.h>
#include <lcd.h>

using hgardenpi::v1::LCD1602;

void LCD1602::init(int lcdRS, int lcdE, int lcd04, int lcd05, int lcd06, int lcd07, int lcdContrast)
{

    handle = lcdInit(rows,
                     colls,
                     4, //bits
                     lcdRS, //LCD_RS
                     lcdE, //LCD_E
                     lcd04, //LCD_04
                     lcd05, //LCD_05
                     lcd06, //LCD_06
                     lcd07, //LCD_07
                     0, 0, 0, 0);

    pinMode(lcdContrast, OUTPUT);
    digitalWrite(lcdContrast, contrastTurnOn);

        print("");

    clear();

    if (handle == -1)
    {
        throw runtime_error("Init error");
    }
}


inline void LCD1602::print(const string &txt) noexcept
{
    ::lcdPuts(handle, txt.c_str());
}

inline void LCD1602::printf(const string &txt, ...) noexcept
{
    va_list(args);
    va_start(args, txt);
    ::lcdPrintf(handle, txt.c_str(), args);
}

inline void LCD1602::print(const uint8_t c) noexcept
{
    ::lcdPutchar(handle, c);
}

inline void LCD1602::home() noexcept
{
    ::lcdHome(handle);
}

inline void LCD1602::clear() noexcept
{
    ::lcdClear(handle);
}

inline void LCD1602::position(int x, int y) noexcept
{
    ::lcdPosition(handle, x, y);
}

inline void LCD1602::display(bool state) noexcept
{
    ::lcdDisplay(handle, state);
}

inline void LCD1602::cursor(bool state) noexcept
{
    ::lcdCursor(handle, state);
}

inline void LCD1602::cursorBlink(bool state) noexcept
{
    ::lcdCursorBlink(handle, state);
}

inline void LCD1602::sendCommand(uint8_t command) noexcept
{
    ::lcdCursorBlink(handle, command);
}
inline void LCD1602::charDef(int index, uint8_t data[8]) noexcept
{
    ::lcdCharDef(handle, index, data);
}

inline void LCD1602::setContrastTurnOn(int contrastTurnOn) noexcept
{
    ::digitalWrite(lcdContrast, contrastTurnOn);
    this->contrastTurnOn = contrastTurnOn;
}