#include "gameObjectController.h"

GameObjectController::GameObjectController( std::weak_ptr<KUDA::Scene> scene ) : scene( std::move( scene )) {}
