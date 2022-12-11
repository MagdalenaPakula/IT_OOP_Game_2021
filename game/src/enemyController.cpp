#include "enemyController.h"

void EnemyController::OnUpdate( int deltaTime ) {
}

EnemyController::EnemyController( const std::weak_ptr<KUDA::Scene>& scene ) : GameObjectController( scene ) {}

EnemyController::EnemyController( const std::weak_ptr<KUDA::Scene>& scene,
                                  const std::shared_ptr<IPathFinder>& pathFinder ) : GameObjectController( scene ),
                                                                                     pathFinder( pathFinder ) {}
