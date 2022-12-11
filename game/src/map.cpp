#include <utility>
#include <vector>
#include "map.h"

Map::Map( std::initializer_list<std::initializer_list<int>> values ) {
    int width = 0;
    int y = 0;
    for ( const auto & row: values ) {
        int x = 0;
        _map.emplace_back();
        for ( auto value: row ) {
            _map[y].push_back( value );
            ++x;
        }
        if (width == 0)
            width = x;
        else if ( width != x )
            throw std::runtime_error("Map has inconsistent widths");
        ++y;
    }
}

Map::Map( std::vector<std::vector<int>> map ) : _map( std::move( map )) {
}

Map* Map::CreateFromFile( const std::string& filePath ) {
    //TODO: Implement reading map from file
    return nullptr;
}

int Map::GetWidth() const {
    return _map[0].size();
}

int Map::GetHeight() const {
    return _map.size();
}

int Map::ValueAtPosition( float x, float y ) const {
    return _map[(int) ( y / 100.f * GetHeight())][(int) ( x / 100.f * GetWidth())];
}

bool Map::IsWall( float x, float y ) const {
    return ValueAtPosition( x, y ) >= 1;
}
