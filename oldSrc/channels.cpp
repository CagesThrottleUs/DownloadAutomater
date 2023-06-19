//
// Created by CagesThrottleUs on 11-06-2023.
//

#include "badFileNameException.hpp"
#include "channels.hpp"
#include "exitCode.hpp"
#include "json.hpp"
#include "jsonKeyValueNotFoundException.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>

using json = nlohmann::json;

impl::Channel::Channel(
        std::string name,
        std::string link,
        unsigned short freq
) :
    name(std::move(name)),
    link(std::move(link)),
    freq(freq)
{

}

auto impl::Channel::getName() const -> const std::string & {
    return name;
}

auto impl::Channel::getLink() const -> const std::string & {
    return link;
}

auto impl::Channel::getFreq() const -> unsigned short {
    return freq;
}

void impl::Channel::setName(const std::string &name) {
    Channel::name = name;
}

void impl::Channel::setLink(const std::string &link) {
    Channel::link = link;
}

void impl::Channel::setFreq(unsigned int freq) {
    Channel::freq = freq;
}


Channels::Channels() = default;

void Channels::fill(const std::string &path, int &retStatus) {

    const std::filesystem::path dataPath(path);
    if(!std::filesystem::exists(dataPath)){
        retStatus = BadFileName;
        throw BadFileNameException(dataPath.string() + " was NOT FOUND, please enter the correct name!");
    }

    // Start filling data with json
    std::ifstream myFile(path);
    json const data = json::parse(myFile);
    json channelList;

    try {
        // Find Channel Data
        channelList = data.at("channels");
        if(channelList.empty()) {
            std::cout << "Please add some channels";
        }
    } catch(const std::exception& exception){
        std::cout << exception.what() << std::endl;
        retStatus = JsonKeyValueNotFound;
        throw JsonKeyValueNotFoundException(
                "The expected key: channels is missing in following JSON File! " + path
        );
    }

    std::string keyName;
    try{
        for(auto& ele: channelList){
            keyName = "name";
            std::string name;
            ele.at(keyName).get_to(name);
            keyName = "link";
            std::string link;
            ele.at(keyName).get_to(link);
            keyName = "frequency";
            unsigned short freq = 0;
            ele.at(keyName).get_to(freq);
            impl::Channel const temp(name, link, freq);
            allChannels.push_back(temp);
        }

    } catch(const std::exception& exception){
        std::cout << exception.what() << std::endl;
        retStatus = JsonKeyValueNotFound;
        throw JsonKeyValueNotFoundException(
            "The expected key: " + keyName + " is missing in following JSON File! " + path
        );
    }
    myFile.close();
}

void Channels::mix() {
    std::random_device randomDevice;
    std::mt19937_64 engine(randomDevice());
    std::shuffle(allChannels.begin(), allChannels.end(), engine);
}
