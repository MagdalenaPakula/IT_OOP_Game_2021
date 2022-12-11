#ifndef GAME_ENEMYCONTROLLER_H
#define GAME_ENEMYCONTROLLER_H

#include <memory>
#include "gameObjectController.h"
#include "IPathFinder.h"

class EnemyController : public GameObjectController
{
public:
    std::shared_ptr<IPathFinder> pathFinder {nullptr};

public:
    explicit EnemyController( const std::weak_ptr<KUDA::Scene>& scene );

    EnemyController( const std::weak_ptr<KUDA::Scene>& scene, const std::shared_ptr<IPathFinder>& pathFinder );

    void OnUpdate( int deltaTime ) override;
};


#endif //GAME_ENEMYCONTROLLER_H
