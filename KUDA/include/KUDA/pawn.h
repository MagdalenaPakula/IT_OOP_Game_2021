#ifndef GAME_PAWN_H
#define GAME_PAWN_H

#include <memory>
#include "actor.h"
#include "pawnController.h"

namespace KUDA
{
    class Pawn : public Actor
    {
        friend class PawnController;

    private:
        std::unique_ptr<PawnController> controller;

    public:
        Pawn( float positionX, float positionY, float direction, std::unique_ptr<PawnController>&& controller );

        PawnController& GetController();
    };
}


#endif //GAME_PAWN_H
