#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <initializer_list>
#include <string>
#include <vector>
#include "KUDA/IMap.h"

class Map : public KUDA::IMap
{
private:
    std::vector<std::vector<int>> _map;
public:
    Map(std::initializer_list<std::initializer_list<int>> values);

    Map( std::vector<std::vector<int>> map );

    static Map* CreateFromFile(const std::string& filePath);

    int GetWidth() const override;

    int GetHeight() const override;

    int ValueAtPosition( float x, float y ) const override;

    bool IsWall( float x, float y ) const override;
};
#endif //GAME_MAP_H
