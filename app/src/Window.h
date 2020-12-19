#pragma once

#include <dirent.h>
#include <sys/stat.h>
#include <iterator>

#include "Element.h"

#define BY_NAME 1
#define BY_TAG  2
#define BY_DIR  3

class MainWindow;

class Window : public Help {
public:
    Window(MainWindow *parent,
           std::string path);
    ~Window();

    void changeDir(std::string path,
                   bool rec);
    void openDir(std::string path,
                 bool rec);
    void sortVector(int flag,
                    std::vector<Element> &list);

    std::string &getDirName(void);
    std::map<std::string, std::vector<Element>> getList(void);
    std::vector<Element> &getVector(std::string path);

private:
    MainWindow *m_parent;
    std::string m_dir;
    std::map<std::string, std::vector<Element>> m_songs;
};
