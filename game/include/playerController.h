#ifndef GAME_PLAYERCONTROLLER_H
#define GAME_PLAYERCONTROLLER_H

#include "gameObjectController.h"

class PlayerController : public GameObjectController
{
public:
    explicit PlayerController( const std::weak_ptr<KUDA::Scene>& scene );

    void OnUpdate( int deltaTime ) override;

private:
    void HandleMovement( int deltaTime );

    void HandleRotation( int deltaTime );
};


#endif //GAME_PLAYERCONTROLLER_H
