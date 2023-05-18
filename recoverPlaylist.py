import os

def readFile(file: str):
    finalList = []
    with open(file, 'r') as f:
        records = f.readlines()
        for record in records:
            record = record.split(' ')[-1]
            record = record.removesuffix('\n')
            finalList.append(record)
    return finalList

def splitPlaylist(fullList: list):
    outList = []
    temp = []
    for id in fullList:
        temp.append(id)
        if(temp.__len__() >= 50):
            outList.append(temp)
            temp = []
    outList.append(temp)
    return outList

def generateLinks(urlOrig: str, diffList: list):
    # Generate main list
    finalLinks = []
    for playlist in diffList:
        url = "" + urlOrig
        for id in playlist:
            url += id + ","
        url = url.removesuffix(',')
        finalLinks.append(url)
    return finalLinks

def _main_():
    # Executes read and write
    urlForTemp = "http://www.youtube.com/watch_videos?video_ids="
    fullList = readFile('./recoverPlaylistData.txt')
    differentPlaylists = splitPlaylist(fullList)
    diffLinks = generateLinks(urlForTemp, differentPlaylists)
    for link in diffLinks:
        os.system("start " + link)

_main_()
