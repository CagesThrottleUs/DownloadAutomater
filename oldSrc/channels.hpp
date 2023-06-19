//
// Created by CagesThrottleUs on 11-06-2023.
//

#ifndef DOWNLOADAUTOMATER_CHANNELS_HPP
#define DOWNLOADAUTOMATER_CHANNELS_HPP


#include <string>
#include <vector>

namespace impl {
    class Channel{
        std::string name;
        std::string link;
        unsigned short freq;
    public:
        Channel(std::string name, std::string link, unsigned short freq);
        //Getters
        [[nodiscard]] auto getName() const -> const std::string &;
        [[nodiscard]] auto getLink() const -> const std::string &;
        [[nodiscard]] auto getFreq() const -> unsigned short;

        //Setters
        void setName(const std::string &name);
        void setLink(const std::string &link);
        void setFreq(unsigned int freq);
    };
}  // namespace impl


class Channels {
    std::vector<impl::Channel> allChannels;
public:
    explicit Channels();
    void fill(const std::string& path, int &retStatus);
    void mix();
};


#endif //DOWNLOADAUTOMATER_CHANNELS_HPP
