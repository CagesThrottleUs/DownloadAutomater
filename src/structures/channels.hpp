//
// Created by CagesThrottleUs on 27-06-2023.
//

// MIT License
//
// Copyright (c) 2023-present Lakshya and other contributors
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

/**
 * @file structures/channels.hpp
 * @brief This file describes the channels from JSON file and holds them together
 * while also providing close data structure.
 */

#ifndef STRUCTURES_CHANNELS_HPP
#define STRUCTURES_CHANNELS_HPP

#include "../utils/exitCode.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace data {

    /**
     * @brief This namespace is not meant to be directly used and just hold internal details.
     * @namespace impl
     * @author Lakshya
     * @cite https://stackoverflow.com/a/14093458/13496837
     */
    namespace impl{
        /**
         * @brief A class that describes the individual channels to be used,
         * @author Lakshya
         */
        class Channel{
            /**
             * @brief The name of the channel as recorded
             * @author Lakshya
             */
            std::string name;

            /**
             * @brief The channel web link.
             * @details it is left on User to check before hand that the link is a valid web link
             * @author Lakshya
             */
            std::string link;

            /**
             * @brief An 8-bit unsigned integer that will hold frequency.
             * @details It is expected that the user will not download more than <RANGE OF UINT8_T> at a time.
             * @author Lakshya
             */
            uint8_t freq;
        public:
            Channel(std::string name, std::string link, uint8_t freq);

            //Getters
            [[nodiscard]] auto getName() const -> const std::string &;
            [[nodiscard]] auto getLink() const -> const std::string &;
            [[nodiscard]] auto getFreq() const -> uint8_t ;

            //Setters
            void setName(const std::string &name);
            void setLink(const std::string &link);
            void setFreq(uint8_t freq);
        };
    } // namespace impl

    /**
     * @brief This is the class that holds all the content for channel.
     */
    class Channels {
        /**
         * @brief This vector will hold all the different Channel properties.
         */
        std::vector<impl::Channel> all;
    public:
        Channels();
        void mix();
        void fill(const std::string& path, ExitCode& code);
    };

} // namespace data

#endif //STRUCTURES_CHANNELS_HPP
