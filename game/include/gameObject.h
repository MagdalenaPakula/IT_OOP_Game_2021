#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H

#include "KUDA.h"

class GameObject : public KUDA::Pawn
{
protected:
    bool isAlive = true;

public:
    GameObject( float positionX, float positionY, float direction, std::unique_ptr<KUDA::PawnController>&& controller );

    bool IsAlive() const;
};


#endif //GAME_GAMEOBJECT_H
