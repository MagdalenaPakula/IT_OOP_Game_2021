#ifndef GAME_IMAP_H
#define GAME_IMAP_H

namespace KUDA
{
    class IMap{
    public:
        virtual ~IMap() = default;

    public:
        [[nodiscard]] virtual int GetWidth() const = 0;

        [[nodiscard]] virtual int GetHeight() const = 0;

        [[nodiscard]] virtual int ValueAtPosition( float x, float y ) const = 0;

        [[nodiscard]] virtual bool IsWall( float x, float y ) const = 0;
    };
}

#endif //GAME_IMAP_H
