#ifndef GAME_GAMEOBJECTCONTROLLER_H
#define GAME_GAMEOBJECTCONTROLLER_H

#include "KUDA.h"

class GameObjectController : public KUDA::PawnController
{
public:
    std::weak_ptr<KUDA::Scene> scene;
    float movementSpeed{ 0.f };
    float rotationSpeed{ 0.f };

    explicit GameObjectController( std::weak_ptr<KUDA::Scene>  scene );
};


#endif //GAME_GAMEOBJECTCONTROLLER_H
