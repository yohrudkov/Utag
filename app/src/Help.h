#pragma once

#include <iostream>
#include <string>
#include <algorithm>

class Help {
public:
    static std::string fullPath(std::string path,
                                char *name);
    static bool checkTag(std::string name,
                         std::string cmp);
};
