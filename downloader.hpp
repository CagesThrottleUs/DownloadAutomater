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
      int download(string cmd, UIRenderer &render){
            int status = system(cmd.c_str());
            if(status == 1){
                  render.Error("Downloader Error please proceed accordingly!");
                  this_thread::sleep_for(chrono::milliseconds(2500));
            }
            return status;
      }
      void createPlaylist(const int before, const int after, const JSONModule &asset){
            const int loop = after - before;
            std::ifstream inFile(asset.savePath + asset.archiveFile);
            string temp;
            for (int i = 0; i < before; i++) getline(inFile, temp);

            vector<string> videos;
            for (int i = 0; i < loop; i++)
            {
                  getline(inFile, temp);
                  videos.push_back(temp.substr(8)); // Format of Archive - youtube <VIDEO_ID>, so start from 8
            }

            inFile.close();

            // break into multiple of 25 and execute
            /* Maximum size of a playlist can be 50 */
            vector<vector<string>> divVideos = SplitVector(videos, (videos.size() / 50)); 
            for(auto &dividedVideos: divVideos){
                  launchPlaylist(dividedVideos);
            }
      }
      void launchPlaylist(vector<string> &videos){
            string command = "http://www.youtube.com/watch_videos?video_ids=";
            for(auto &video: videos){
                  command += video;
                  command += ",";
            }
            command.erase(command.length() - 1); // Cannot end with a ","
            command = "start " + command;
            system(command.c_str());
      }
      void saveFailed(vector<string> &failed, const JSONModule &asset){
            ofstream out(asset.savePath + "failedChannels.txt");
            for(auto &fails: failed){
                  out << "Channel: " << fails << endl;
            }
            out.close();
      }
      /**
       * @brief This function would split vector of any type in almost equal lengths,
       * such that we get at most n in each split vector.
       * 
       * @tparam T automatically guessed or can be manually passed
       * @param vec The big vector to split
       * @param n Total number of vectors to be created
       * @return std::vector<std::vector<T>> out
       */
      template<typename T>
      std::vector<std::vector<T>> SplitVector(const std::vector<T>& vec, size_t n) {
            std::vector<std::vector<T>> outVec;

            size_t length = vec.size() / n;
            size_t remain = vec.size() % n;

            size_t begin = 0;
            size_t end = 0;

            for (size_t i = 0; i < std::min(n, vec.size()); ++i)
            {
                  end += (remain > 0) ? (length + !!(remain--)) : length;

                  outVec.push_back(std::vector<T>(vec.begin() + begin, vec.begin() + end));

                  begin = end;
            }

            return outVec;
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
            vector<string> failed;
            for(auto &channel: toDownload){
                  cout << "\033[2J\033[1;1H";
                  render.ProgressBar((i*1.0f)/(total), 100);
                  cout << " [" << i+1 << "/" << total << "]" << endl;
                  render.Info("Now Downloading: " + channel.getName());
                  const string cmd = CMD(asset) + channel.getLink() + " " + asset.downloader.getFreqMatcher() + " " + to_string(channel.getFreq());
                  int status = download(cmd, render);
                  if(status == 1) failed.push_back(channel.getName());
                  i++;
            }
            const unsigned int after = countLines(asset);
            createPlaylist(before, after, asset);
            saveFailed(failed, asset);
      }
};


#endif // INCLUDE_DOWNLOADER_HPP_