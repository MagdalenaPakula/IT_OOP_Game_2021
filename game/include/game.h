#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "KUDA.h"

class Game : public KUDA::IController
{
public:
    void OnUpdate( int deltaTime ) override;

    void Start();
};


#endif //GAME_GAME_H
