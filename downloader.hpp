#ifndef INCLUDE_DOWNLOADER_HPP_
#define INCLUDE_DOWNLOADER_HPP_

#include "initializeData.hpp"
#include <fstream>
#include <algorithm>
#include "UIRenderer.hpp"
#include <thread>
#include <chrono>

using namespace std;

class Utils{
private:
      const unsigned int countLines(const JSONModule &asset){
            std::ifstream inFile(asset.savePath + asset.archiveFile);
            const unsigned int cnt = std::count(std::istreambuf_iterator<char>(inFile),
                              std::istreambuf_iterator<char>(), '\n');
            inFile.close();
            return cnt;
      }
      const string CMD(const JSONModule &asset){
            string cmd = asset.downloader.command();
            cmd = "cd " + asset.savePath + " & " + cmd;
            return cmd;
      }
      void download(string cmd, UIRenderer &render){
            int status = system(cmd.c_str());
            if(status == 1){
                  render.Error("Downloader Error please proceed accordingly!");
                  this_thread::sleep_for(chrono::milliseconds(2500));
            }
      }
      void createPlaylist(const int before, const int after, const JSONModule &asset){
            const int loop = after - before;
            std::ifstream inFile(asset.savePath + asset.archiveFile);
            string temp;
            for (int i = 0; i < before; i++) getline(inFile, temp);

            string command = "http://www.youtube.com/watch_videos?video_ids=";
            for (int i = 0; i < loop; i++)
            {
                  getline(inFile, temp);
                  command += (temp.substr(8)); // Format of Archive - youtube <VIDEO_ID>, so start from 8
                  command += ",";
            }
            command.erase(command.length() - 1); // Cannot end with a ","
            inFile.close();
            command = "start " + command;
            system(command.c_str());
      }
public:
      void downloadPlaylist(const JSONModule &asset, UIRenderer &render){
            render.Header("Now downloading playlist, does not provide error safety");
            const string cmd = CMD(asset) + asset.defaultPlaylist;
            download(cmd, render);
            render.Footer();
            render.Separator();
      }
      void downloadChannels(const JSONModule &asset, UIRenderer &render){
            const vector<Channels> toDownload = asset.channels;
            const auto total = toDownload.size();
            size_t i = 0;
            const unsigned int before = countLines(asset);
            for(auto &channel: toDownload){
                  cout << "\033[2J\033[1;1H";
                  render.ProgressBar((i*1.0f)/(total), 100);
                  cout << " [" << i+1 << "/" << total << "]" << endl;
                  render.Info("Now Downloading: " + channel.getName());
                  const string cmd = CMD(asset) + channel.getLink() + " " + asset.downloader.getFreqMatcher() + " " + to_string(channel.getFreq());
                  download(cmd, render);
                  i++;
            }
            const unsigned int after = countLines(asset);
            createPlaylist(before, after, asset);
      }
};


#endif // INCLUDE_DOWNLOADER_HPP_