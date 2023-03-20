#ifndef INCLUDE_TESTS_HPP_
#define INCLUDE_TESTS_HPP_

#include "UIRenderer.hpp"
#include "initializeData.hpp"
#include <numeric>
#include <thread>
#include <chrono>
using namespace std;

void activateRendererTests(UIRenderer &render){
      cout << "ACTIVATING RENDER TESTS" << endl;

      cout << "\n\n1. Header (Visual)\n";
      render.Header("Example Title");

      cout << "2. Progress bar demo: ";
      for (float progress = 0.0f; progress <= 1.0f + std::numeric_limits<float>::epsilon(); progress += 0.1f)
      {
            cout << "\0337"; // DECSC - save cursor
            render.ProgressBar(progress, 10);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "\0338"; // DECRS - restore cursor
      }
      cout << '\n';

      cout << "3. Footer" << endl;
      render.Footer();

      cout << "4. Separator" << endl;
      render.Separator();
}

void activateJSONTests(UIRenderer &render, const string dataPath){
      render.Header("Loading JSON Data Test");
      JSONModule asset = initialize(dataPath, render);

      // Test all values by Cout
      cout << "SAVE_PATH: " << asset.savePath << endl;
      cout << "ARCHIVE_FILE: " << asset.archiveFile << endl;
      cout << "DOWNLOADER:\n" << asset.downloader << endl;
      cout << "DEBUG: " << std::boolalpha << asset.debug << endl;
      cout << "DEFAULT PLAYLIST: " << asset.defaultPlaylist << endl;
      cout << "CHANNELS:\n ";
      for(auto &channel: asset.channels){
            cout << channel << endl;
      }
      render.Footer();
      render.Separator();
}

#endif // INCLUDE_TESTS_HPP_