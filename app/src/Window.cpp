#include "Window.h"
#include "mainwindow.h"

Window::Window(MainWindow *parent, std::string path) {
    m_parent = parent;
    m_dir = path;
    openDir(m_dir, false);
};

Window::~Window() {

};

void Window::changeDir(std::string path, bool rec) {
    m_dir = path;
    m_songs.clear();
    openDir(path, rec);
};

void Window::openDir(std::string path, bool rec) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path.c_str());
    if (!dir) {
        m_parent->printError("Invalid dir path");
        return;
    };
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            auto itr = m_songs.find(path);
            Element new_song(path, entry->d_name);

            if (!new_song.getPath().empty() && (m_songs.empty() || itr == m_songs.end())) {
                std::vector<Element> new_folder;
                new_folder.push_back(new_song);
                m_songs.insert({path, new_folder});
            }
            else if (!new_song.getPath().empty())
                itr->second.push_back(new_song);
            else if (rec && entry->d_type == DT_DIR)
                openDir(fullPath(path, entry->d_name), rec);
        }
    }
    closedir(dir);
};

void Window::sortVector(int flag, std::vector<Element> &list) {
    std::sort(list.begin(), list.end(), [flag](Element elem1, Element elem2) {
        std::string name1 = elem1.getName();
        std::string name2 = elem2.getName();
        if ((flag == BY_NAME && name1.compare(name2) < 0)
            || (flag == BY_TAG && name1.compare(name1.find("."), name1.size(), name2, name2.find("."), name2.size()))
            || (flag == BY_DIR && elem1.getPath().compare(elem2.getPath()) < 0))
            return true;
        return false;
    });
};

std::string &Window::getDirName(void) {
    return m_dir;
};

std::map<std::string, std::vector<Element>> Window::getList(void) {
    return m_songs;
};

std::vector<Element> &Window::getVector(std::string path) {
    return (*m_songs.find(path)).second;
};
