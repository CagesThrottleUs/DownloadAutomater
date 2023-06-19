//
// Created by CagesThrottleUs on 11-06-2023.
//

#ifndef DOWNLOADAUTOMATER_DOWNLOADER_HPP
#define DOWNLOADAUTOMATER_DOWNLOADER_HPP


#include <string>
#include <vector>

namespace iml{
    class DownloaderArgs{
        std::string option;
        std::string value;
        bool includeOnFail{false};
    public:
        DownloaderArgs(std::string option, std::string value, bool includeOnFail);
        explicit DownloaderArgs();

        // Getters
        [[nodiscard]] auto getOption() const -> const std::string &;
        [[nodiscard]] auto getValue() const -> const std::string &;
        [[nodiscard]] auto isIncludeOnFail() const -> bool;

        // Setters
        void setOption(const std::string &option);
        void setValue(const std::string &value);
        void setIncludeOnFail(bool includeOnFail);

        [[nodiscard]] auto command() const -> std::string;
    };
}  // namespace iml

class Downloader {
    std::string executablePath;
    std::vector<iml::DownloaderArgs> arguments;
    std::vector<iml::DownloaderArgs> badOptions;
    iml::DownloaderArgs freqMatcher;
public:
    explicit Downloader();
    void fill(const std::string& path, int &retStatus);
    auto fullCommand() -> std::string;
    auto fullCommandWithFreqMatcher() -> std::string;
    auto fullCommandSafe() -> std::string;
    auto fullCommandSafeWithFreqMatcher() -> std::string;
};


#endif //DOWNLOADAUTOMATER_DOWNLOADER_HPP
