# This files main goal is to fill from A source Location. This is the first time script as the next time,
# only the Trie configuration will be used to upgrade the configuration file directly as it is closer to program.
#
# This may not be required in case you are creating your own new playlist. Just start downloading.
#
# To run - python ./scripts/generateArchiveNames.py <folderLocation> <archiveName> at Github Directory level.
#
# Prerequisites - Python3, Natsort

import os
from natsort import os_sorted
import sys

source = sys.argv[1]
files = os.listdir(source)
files = os_sorted(files)
with open(sys.argv[2], mode="w", encoding="utf-8") as f:
    for file in files:
        file = file.removesuffix(".mp3")
        print(file, file=f)
