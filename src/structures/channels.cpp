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

#include "channels.hpp"
#include "../exceptions/badUrlForm.hpp"
#include "../exceptions/fileNotFound.hpp"
#include "../external/json.hpp"
#include "../utils/constants.hpp"
#include "../utils/miscFunctions.hpp"
#include <algorithm>
#include <fstream>
#include <random>
#include <utility>

using json = nlohmann::json;

/**
 * @brief The default constructor that will fill the details from the user
 * @param name The string that describe the Channel Name
 * @param link The link to the video channel
 * @param freq The value of Frequency for downloading file
 * @author Lakshya
 */
data::impl::Channel::Channel(
    std::string name,
    std::string link,
    uint8_t freq
) :
    name(std::move(name)),
    link(std::move(link)),
    freq(freq)
{

}

/**
 * @brief A simple getter function that returns the name of channel
 * @return A string reference for the name
 */
auto data::impl::Channel::getName() const -> const std::string & {
    return name;
}

/**
 * @brief A simple getter function that returns the web link.
 * @details IT IS LEFT ON USER TO CHECK IF THE LINK IS VALID OR NOT
 * @return A string reference to link.
 */
auto data::impl::Channel::getLink() const -> const std::string & {
    return link;
}

/**
 * @brief A simple getter function that returns the frequency.
 * @return The frequency variable as an 8-bit integer
 */
auto data::impl::Channel::getFreq() const -> uint8_t {
    return freq;
}

/**
 * @brief Set the name of Channel to be downloaded
 * @param name The string that will be name
 */
void data::impl::Channel::setName(const std::string &name) {
    this->name = name;
}

/**
 * @brief This will set the web link for the data.
 * @details It is left to the user to ensure that the string is actually a web link before hand.
 * @param link The string containing weblink
 */
void data::impl::Channel::setLink(const std::string &link) {
    this->link = link;
}

/**
 * @brief A simple setter to set frequency.
 * @param freq Must be a @c uint8_t
 */
void data::impl::Channel::setFreq(uint8_t freq) {
    this->freq = freq;
}

/**
 * @brief A default constructor to create the object.
 */
data::Channels::Channels() = default;

/**
 * @brief This function will actually mix the different channel
 * @author Lakshya
 * @cite https://en.cppreference.com/w/cpp/algorithm/random_shuffle
 */
void data::Channels::mix() {
    std::random_device randomDevice;
    std::mt19937_64 engine(randomDevice());
    std::shuffle(all.begin(), all.end(), engine);
}

/**
 * @brief This function developed will directly fill the various different properties of channels to its members
 * @param path The path to the json file that holds channel information
 * @param code The exitcode to return in case of bad ending.
 * @throws FileNotFoundException when the path file does not exist
 * @throws JsonicExceptions for all json related error
 * @throws BadURLFormException when the URLs are not of proper form
 */
void data::Channels::fill(const std::string &path, ExitCode &code) {
    if(!FileNotFoundException::checkIfFileExists(path)){
        std::string msg;
        mainDriver::appendMessagesForLog(msg,
                                         "Exception Created - File does not exist!");
        mainDriver::appendMessagesForLog(msg,
                                         "Created at the time to fill channels details.");
        mainDriver::appendMessagesForLog(msg,
                                         "Updated exit code to - " +
                                         std::to_string(static_cast<int>(ExitCode::RETURN_FILE_NOT_FOUND)));
        mainDriver::logUsingSourceLocation(msg);
        code = ExitCode::RETURN_FILE_NOT_FOUND;
        throw FileNotFoundException("The following file was not found - " + path);
    }

    std::ifstream configForChannels(path);
    json const data = mainDriver::parseJsonFile(configForChannels, code);
    configForChannels.close();

    std::string keyname = "channels";
    std::vector<std::string> subKeyName = {"name", "link", "frequency"};

    json const temp = mainDriver::accessJsonByKey(data, constants::CONFIG_KEY_NAMES.at(keyname), code);
    for(const auto& ele: temp){
        std::string val = mainDriver::accessJsonByKey(ele, subKeyName[0], code).get<std::string>();
        data::impl::Channel channel("", "", 0);
        channel.setName(val);
        val = mainDriver::accessJsonByKey(ele, subKeyName[1], code).get<std::string>();
        if(!BadURLFormException::CheckForURLForm(val)){
            std::string msg;
            code = ExitCode::RETURN_BAD_URL_FORMAT;
            mainDriver::appendMessagesForLog(msg,
                                             "Exception Created - THE URL was Malformed");
            mainDriver::appendMessagesForLog(msg,
                                             "Setting up Exit Code - " +
                                             std::to_string(static_cast<int>(code)));
            throw BadURLFormException("The following URL had Bad Format - " + val);
        }
        channel.setLink(val);
        uint8_t const freq = mainDriver::accessJsonByKey(ele, subKeyName[2], code).get<uint8_t>();
        channel.setFreq(freq);
        all.push_back(channel);
    }

    keyname = "";
    subKeyName = {};

    code = ExitCode::RETURN_OK; // Fin
}
