#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>

#include "json.hpp"
#include "UIRenderer.hpp"
#include "tests.hpp"
#include "initializeData.hpp"


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

      const bool debug = asset.debug;
      const string defaultPlaylist = asset.defaultPlaylist;
      
      if(debug){
            activateRendererTests(render);
            activateJSONTests(render, dataPath);
            return 0;
      }
      //Check if you want a playlist
      // TODO: Channels all together or not &&& JSON-Scheme
      return 0;
}