#ifndef _LAYERREADER_H_
#define _LAYERREADER_H_

#include <string>
#include <vector>
#include <iostream>
#include <map>

class LayerReader {
    private:
        std::map<std::string, std::vector<int>> mapping = std::map<std::string, std::vector<int>>();
    
    public:
        LayerReader() {};
        LayerReader(std::string layerPath);
        int getTile(int r, int g, int b, int a);
};

#endif