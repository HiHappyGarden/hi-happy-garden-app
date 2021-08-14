// MIT License
//
// Copyright (c) $year. Happy GardenPI
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
//

//
// Created by Antonio Salsi on 14/08/21.
//

#pragma once

#include "relaymodule.hpp"

namespace hgardenpi
{
    inline namespace v1
    {
        /**
         * @brief Relay module for manage ELEGOO 4 Channel Relay
         */
        class RelayModule4Channel : public RelayModule
        {
        public:

            enum GPIOPin : int
            {
                IN1 = 6,
                IN2 = 10,
                IN3 = 11,
                IN4 = 31,
            };

            /**
             * Create new instance of
             * @param in1 pin of relay 1
             * @param in2 pin of relay 2
             * @param in3 pin of relay 3
             * @param in4 pin of relay 1
             */
            RelayModule4Channel(int in1, int in2, int in3, int in4) noexcept;

            void setRelay(const Station::Ptr &ptr, int status) const noexcept override;

            /**
             * @brief Return the name of object
             * @return std::string name of object
             */
            inline string toString() noexcept override
            {
                return typeid(*this).name();
            }

        public:


        };
    }
}
