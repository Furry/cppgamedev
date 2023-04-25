#include "layerreader.h"

#include <string>
#include <fstream>
#include <iostream>

LayerReader::LayerReader(std::string file_name) {
    // Go over all lines in the file
    std::ifstream file(file_name);
    std::string line;
    int y = 0;

    std::cout << "Reading layer file " << file_name << std::endl;
    while (std::getline(file, line)) {
        
        std::cout << "Line: " << line << std::endl;

        // Split line by space, the first split is the color, the second is the tile.
        std::string color = line.substr(0, line.find(" "));
        std::string tile = line.substr(line.find(" ") + 1, line.length());
        // split tile by | and add each slice to an int<vector>
        std::vector<int> tiles;
        std::string delimiter = "|";
        size_t pos = 0;
        std::string token;
        while ((pos = tile.find(delimiter)) != std::string::npos) {
            token = tile.substr(0, pos);
            tiles.push_back(std::stoi(token));
            tile.erase(0, pos + delimiter.length());
        }
        
        // Add the last token after the loop
        tiles.push_back(std::stoi(tile));

        // Add the color and tile to the mapping
        mapping[color] = tiles;

        // Increment the y value
        y++;
    }
}

int LayerReader::getTile(int r, int g, int b, int a) {
    // Construct string from r-g-b-a
    std::string color = std::to_string(r) + "-" + std::to_string(g) + "-" + std::to_string(b);

    // Return the tile if it exists, else -1
    if (mapping.find(color) != mapping.end()) {
        // Print it's length
        // return mapping[color][57 % mapping[color].size()];
        return mapping[color][0];
    } else {
        return -1;
    }
}