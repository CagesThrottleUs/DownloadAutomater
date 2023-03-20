#ifndef INCLUDE_INITIALIZEDATA_HPP_
#define INCLUDE_INITIALIZEDATA_HPP_

#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<random>
#include<cassert>

#include "json.hpp"
#include "UIRenderer.hpp"

using namespace std;
using json = nlohmann::json;

class Options{
      string name;
      string value;
public:
      Options(string Option, string Value): 
            name(Option),
            value(Value)
      {}
      string command(){
            return name + value;
      }
      friend ostream& operator<<(ostream& os, const Options &opt){
            os << "[\n\tOption: " << opt.name << "\n\tValue: " << opt.value << "\n]";
            return os;
      }
};

class Downloader{
      string exec;
      vector<Options> opt;
public:
      Downloader():
            exec(""),
            opt({})
      {}
      Downloader(string executable, vector<Options> &opts):
            exec(executable),
            opt(opts)
      {}
      string command(){
            string ans = exec + " ";
            for(auto &option : opt){
                  ans += option.command() + " ";
            }
            return ans;
      }
      const string getExec(){
            return exec;
      }
      void setExec(const string exec){
            this->exec = exec;
      }
      void addOption(const Options& option){
            opt.push_back(option);
      }
      friend ostream& operator<<(ostream& os, const Downloader &dw){
            os << "[\n\texec: " << dw.exec << "\n\topt<Vector>: [\n";
            for(auto &options: dw.opt){
                  os << options;
            }
            os << "\n]\n";
            return os;
      }
};

class Channels{
      string name;
      string link;
      short freq;
public:
      Channels(string Name, string Link, short Freq):
            name(Name),
            link(Link),
            freq(Freq)
      {}
      const string getName(){
            return name;
      }
      const string getLink(){
            return link;
      }
      const short getFreq(){
            return freq;
      }
      void setName(const string Name){
            this->name = Name;
      }
      void setLink(const string Link){
            this->link = Link;
      }
      void setFreq(const short Freq){
            this->freq = Freq;
      }
      friend ostream& operator<<(ostream& os, const Channels &ch){
            os << "[\n\tChannel: " << ch.name << "\n\tLink: " << ch.link << "\n\tfreq: " << ch.freq << "\n]";
            return os;
      }
};

struct JSONModule{
      string savePath = "";
      string archiveFile = "";
      bool debug = false;
      string defaultPlaylist = "";
      Downloader downloader{};
      vector<Channels> channels{};
};

void fillChannels(json &data, JSONModule &out){
      // Data in channels of the form of array of json
      auto &arr = data.at("channels");
      string tempName;
      string tempLink;
      short tempFreq;
      for(auto &x: arr){
            x.at("name").get_to(tempName);
            x.at("link").get_to(tempLink);
            x.at("frequency").get_to(tempFreq);
            Channels temp(tempName, tempLink, tempFreq);
            out.channels.push_back(temp);
      }

      // Now Randomize Vector Channels
      random_device rd;
      mt19937 gen{rd()};
      shuffle(out.channels.begin(), out.channels.end(), gen);
}

void fillDownloader(json &data, JSONModule &out){
      auto &obj = data.at("downloader");
      string temp;
      obj.at("executable").get_to(temp);
      out.downloader.setExec(temp);

      auto &arr = obj.at("options");
      for(auto &opts: arr){
            string tempName;
            opts.at("option").get_to(tempName);
            string tempVal;
            opts.at("value").get_to(tempVal);
            Options tempOptions(tempName, tempVal);
            out.downloader.addOption(tempOptions);
      }
      cout << "DONE! " << endl;
}

const JSONModule initialize(const string dataPath, UIRenderer render){
      std::ifstream inFile(dataPath);
      cout << endl << endl;
      cout << "READING File at: " << dataPath << endl;
      json data = json::parse(inFile);

      JSONModule ans;
      cout << "Trying to understand savePath and archiveFile!!" << endl;
      data.at("savePath").get_to(ans.savePath);
      data.at("archiveFile").get_to(ans.archiveFile);
      cout << "Checking if DEBUG mode! ";
      data.at("debug").get_to(ans.debug);
      cout << std::boolalpha << ans.debug << endl;

      string temp = "";
      render.Input("DO YOU WANT TO USE YOUR PLAYLIST? <y/n>: ",temp);

      if(temp == "y"){
            render.Input("PLEASE ENTER PLAYLIST:", ans.defaultPlaylist);
      } else {
            data.at("defaultPlaylist").get_to(ans.defaultPlaylist);
      }

      cout << "Now trying to fill Downloader data" << endl;
      fillDownloader(data, ans);
      cout << "Now trying to fill Channels data" << endl;
      fillChannels(data, ans);

      // Check current Hack
      cout << "Checking if ARCHIVE File match!!" << endl;
      assert(ans.archiveFile == data.at("downloader").at("options").at(11).at("value") && "Please match --download-archive and archiveFile in JSON");
      cout << "DONE!" << endl;

      inFile.close();
      return ans;
}

#endif // INCLUDE_INITIALIZEDATA_HPP_