#ifndef INCLUDE_UIRENDERER_HPP_
#define INCLUDE_UIRENDERER_HPP_

#include<iostream>
#include<algorithm>
#include<windows.h>
#include<sstream>
#include<string>
#include<cstdint>
#include<chrono>
#include<ctime>
using namespace std;

class UIRenderer{
      COORD coord; // Provide COORD where you want to write
      CONSOLE_SCREEN_BUFFER_INFO csbinfo;
      HANDLE _stdout;

private:
      void updateConsoleBufferInfo(){
            GetConsoleScreenBufferInfo(_stdout, &csbinfo);
      }
public:
      UIRenderer(){
            _stdout = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(_stdout, &csbinfo);
            coord.X = static_cast<short>(csbinfo.dwCursorPosition.X);
            coord.Y = static_cast<short>(csbinfo.dwCursorPosition.Y);
      }

      void Header(const string headerTitle){
            updateConsoleBufferInfo();
            // Create Guard Railings
            string guard = "";
            guard.resize(csbinfo.srWindow.Right);
            fill(guard.begin(), guard.end(), '*');
            guard[0] = '|';
            guard[guard.size()-1] = '|';

            // Print Finally
            cout << guard << endl;
            
            // Determine right center
            const short rightCenter = static_cast<short>(csbinfo.srWindow.Right / 2);

            // String to print header on
            string str = "";
            str.resize(csbinfo.srWindow.Right);
            fill(str.begin(), str.end(), ' ');
            str[0] = '|';
            str[str.size()-1] = '|';

            // Align middle of header and rightCenter
            const short leftHalf = static_cast<short>(headerTitle.length() / 2);
            str.replace(rightCenter - leftHalf, headerTitle.length(), headerTitle);
            cout << str << endl;
            
            cout << guard << endl;
      }

      void ProgressBar(float progress, int columnWidth){
            updateConsoleBufferInfo();
            auto const filledColumns = static_cast<int>(floorf(progress * static_cast<float>(columnWidth)));

            cout << "[";

            if (filledColumns == 0) cout << "."; // left empty
            else cout << "#"; // left filled

            int i = 1;
            while (i++ < min(filledColumns, columnWidth - 1)) cout << "#"; // middle filled

            while (i++ < columnWidth) cout << "."; // middle empty

            if (filledColumns >= columnWidth) cout << "#"; // Right filled
            else cout << "."; // Right empty
            
            cout << "]";

            cout << " | " << int(progress * 100.0f) << '%';

            cout.flush();
      }

      void Footer(){
            updateConsoleBufferInfo();
            string guard = "";
            guard.resize(csbinfo.srWindow.Right);
            fill(guard.begin(), guard.end(), '*');
            guard[0] = '|';
            guard[guard.size()-1] = '|';
            cout << guard << endl;
      }

      void Separator(){
            updateConsoleBufferInfo();
            cout << "\n\n\n";
            string guard = "";
            guard.resize(csbinfo.srWindow.Right);
            fill(guard.begin(), guard.end(), '-');
            auto end = std::chrono::system_clock::now();
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            string ax = string(std::ctime(&end_time));
            guard.replace(guard.size() - ax.length(), ax.length(), string(std::ctime(&end_time)));
            cout << guard << endl;
      }

      void Input(const string text, string &store){
            updateConsoleBufferInfo();
            cout << "\n\n\n";
            string guard = "";
            guard.resize(csbinfo.srWindow.Right);
            fill(guard.begin(), guard.end(), '*');
            guard[0] = '|';
            guard[guard.size() - 1] = '|';


            cout << guard << endl;

            updateConsoleBufferInfo();
            COORD guardPos = csbinfo.dwCursorPosition;
            COORD strPos = guardPos;
            guardPos.Y += 1;
            SetConsoleCursorPosition(_stdout, guardPos);
            cout << guard << endl;

            updateConsoleBufferInfo();
            COORD finalPos = csbinfo.dwCursorPosition;

            SetConsoleCursorPosition(_stdout, strPos);
            cout << text;
            cin >> store;

            SetConsoleCursorPosition(_stdout, finalPos);
      }
      
      void Error(const string text){
            updateConsoleBufferInfo();
            SetConsoleTextAttribute(_stdout, FOREGROUND_RED);
            cout << text << endl;
            SetConsoleTextAttribute(_stdout, csbinfo.wAttributes);
      }
};

#endif // INCLUDE_UIRENDERER_HPP_