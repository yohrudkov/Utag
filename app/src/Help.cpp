#include "Help.h"

std::string Help::fullPath(std::string path, char *name) {
    std::string fullPath = path;

    if (path.back() != '/')
        fullPath += "/";
    fullPath += name;
    return fullPath;
};

bool Help::checkTag(std::string name, std::string cmp) {
    std::string sub = name.substr(name.size() - 3);
    std::transform(sub.begin(), sub.end(), sub.begin(), ::toupper);
    if (sub == cmp)
        return true;
    return false;
}
