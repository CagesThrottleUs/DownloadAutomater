#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>

#include "json.hpp"
#include "UIRenderer.hpp"
#include "initializeData.hpp"
#include "downloader.hpp"

using namespace std;
using json = nlohmann::json;

const string dataPath = "./data.json";

int main(){
      UIRenderer render;

      render.Header("Loading Information from JSON");
      // Now learn options to loads
      const JSONModule asset = initialize(dataPath, render);
      render.Footer();
      render.Separator();

      // ADd download playlist first with Match
      render.Header("Downloading playlist against archive");

      Utils util; 
      util.downloadPlaylist(asset, render);
      render.Footer();
      render.Separator();


      string ch;
      render.Input("Do you want to download from channels? <y/n>: ", ch);


      if(ch == "y"){
            render.Header("Downloading playlists and matching with archive");
            util.downloadChannels(asset, render);
            render.Footer();
            render.Separator();
      } else {
            // end's the program
      }
      return 0;
}