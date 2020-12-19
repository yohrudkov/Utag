#pragma once

#include <sys/stat.h>
#include <iomanip>
#include <vector>
#include <map>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <istream>
#include <string.h>

#include "Img.h"
#include "Help.h"

typedef struct s_Element {
    TagLib::String album;
    TagLib::String artist;
    TagLib::String comment;
    TagLib::String genre;
    TagLib::String title;
    TagLib::String year;
    TagLib::String track;
    TagLib::String lyrics;

    TagLib::String bitrate;
    TagLib::String sampleRate;
    TagLib::String channels;
    TagLib::String minutes;
    TagLib::String seconds;
}              t_Element;

class Element : public Help{
public:
    Element(std::string path, char *name);
    ~Element();

    void addSongInfo(TagLib::FileRef song);
    void setNewInfo(t_Element new_info);
    void setNewImg(std::string img);
    void lyricsSet(std::string lyrics);
    TagLib::String lyricsGet(void);

    t_Element &getInfo(void);
    TagLib::String &getElemInfo(unsigned int index);
    std::string &getPath(void);
    std::string &getName(void);

private:
    TagLib::FileRef m_info;
    std::string m_path;
    std::string m_name;
    t_Element m_song;
};
