import os
from natsort import os_sorted
import sys

location = sys.argv[1]
files = os.listdir(location)
files = os_sorted(files)
with open(sys.argv[2], mode="w", encoding="utf-8") as f:
    for file in files:
        file = file.removesuffix(".mp3")
        print(file)
        print(file, file=f)

# To run - python ./data/generateArchiveNames.py <folderLocation> <archiveName> at Github Directory level.
