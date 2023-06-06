# Download Automater

This project is developed for Automating my downloads for different YouTube Channels. 

Here we basically download and checkout from an online playlist like [Mine](https://www.youtube.com/playlist?list=PLYo4GDM-6t3PgIxb-VyCK6ahNLomxqbJA). This is also matched from a local archive file as supported by the executable.

# Prerequisites

The pre-requisites for running the application:\

1. [yt-dlp](https://github.com/yt-dlp/yt-dlp): Must be taken from releases and kept at a path that is visible from PATH (like C:\Windows).
2. [Updated FFMpeg](https://github.com/yt-dlp/FFmpeg-Builds) - need for conversions from different encodings. Does post-process your downloads.

For compiling the project on your own you definitely need - 

1. [JSON.hpp](https://github.com/nlohmann/json/releases/latest) - Should be placed under ./library in project, please use the latest version
2. [CMake](https://cmake.org/download/) - should 3.26 and above.
3. [clang++](https://github.com/llvm/llvm-project/releases/latest) - This was used to create the executable for the project.
4. C++20 standard.

# Releases

Please find the executable as main.exe and the archival file archive file that can be used together. Along with it we will have data.json which will hold data of different channel to download from.

- main.exe
- args.json
- channels.json
- archive.txt
