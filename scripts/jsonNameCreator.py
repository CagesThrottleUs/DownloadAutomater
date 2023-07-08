# This python program aims to create a temporary json file that will be used to rename the post downloaded files.
# The created json file would then be utilized with a JS/HTTPS localhost to allow for rename according to host rules.
#
# To run the file -
#       python ./scripts/jsonNameCreator.py <source folder> <output file name with correct path> from GitHub directory
#
# Prerequisites -
#   Python3 Natsort

import os
from natsort import os_sorted
import sys
import json

source = sys.argv[1]
files = os.listdir(source)
files = os_sorted(files)
with open(sys.argv[2], mode="w", encoding="utf-8") as f:
    x = {"configuration": []}
    for file in files:
        size = os.path.getsize(source + "/" + file)
        file = file.removesuffix(".mp3")  # Format - {%id}FullName and %id is a6QqkEsGxNY (11 chars)
        temp = {"id": file[1:12], "name": file[13:], "rename": "", "size": size}
        x["configuration"].append(temp)
    content = json.dumps(x, ensure_ascii=False, indent=4)
    f.write(content)
