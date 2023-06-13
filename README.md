# Introduction

This project is developed for Automating different audio tracks that I will be putting to [my playlist](https://www.youtube.com/playlist?list=PLYo4GDM-6t3PgIxb-VyCK6ahNLomxqbJA).

# Table of contents

- [Introduction](#introduction)
- [Table of contents](#table-of-contents)
- [Prerequisite](#prerequisite)
- [What's in the release](#whats-in-the-release)
- [Rules regarding naming for data](#rules-regarding-naming-for-data)

# Prerequisite

To run the python file in data/ - Ensure that you have python3 and natsort library.

To run these files it is necessary to have various run time library that are present with C++. Windows User may find this at [WinLibs](https://winlibs.com/).

# What's in the release

The release file should have the following structure that you can put in any folder where you will be processing.

The code is set up in a way that helps me in creating my own playlist quickly. But options can be adjusted accordingly. Please feel free to create a PR/Issue for improvements.

File Contents:
```text
-- ExecutableFile
-- bin/
      -- ffmpeg.exe
      -- ffplay.exe
      -- ffprobe.exe
      -- yt-dlp.exe
-- data/
      -- archive.links.txt
      -- archive.names.txt
      -- channels.tracked.json
      -- downloader.args.json
      -- executable.opts.json
-- scripts/
      -- generateArchiveNamesFromSrc.py
-- processed/
      // All Data downloaded here 
      // <CREATED BY EXECUTABLE>
-- temp/
      // Stores shell file and other temp files
      // <CREATED BY EXECUTABLE>
```

You may download the executable from [FFMPEG](https://github.com/yt-dlp/FFmpeg-Builds/releases/latest) and [yt-dlp](https://github.com/yt-dlp/yt-dlp-nightly-builds/releases/latest).

# Rules regarding naming for data

To name different locations present in the data must be **Executable Relative**.

Use the program present in data folder itself, as arguments are directly tied to it. Change it at your own risk.

Only downloader arguments are going