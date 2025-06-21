#include <iostream>
#include <string>
#include <dirent.h>   
#include <cstdio>    
#include <cstring>   

#ifdef _WIN32
#define SLASH '\\'
#else
#define SLASH '/'
#endif

int main() {
    std::string directory;
    std::cout << "Enter directory path: ";
    std::getline(std::cin, directory);

    DIR* dp = opendir(directory.c_str());
    if (dp == nullptr) {
        std::cerr << "Cannot open directory.\n";
        return 1;
    }

    dirent* file;
    int index = 0;

    while ((file = readdir(dp)) != nullptr) {
        std::string filename = file->d_name;

        // Skip system entries
        if (filename == "." || filename == "..") continue;

        // renaming original name by a new
        std::string original = directory + SLASH + filename;
        std::string renamed = directory + SLASH + "Image_" + std::to_string(index++) + ".jpg";

        if (std::rename(original.c_str(), renamed.c_str()) != 0) {
            std::perror(("Failed to rename: " + filename).c_str());
        }
    }
    closedir(dp);
    std::cout << "Renaming done.\n";
    return 0;
}
