#ifndef GAME_PAWNCONTROLLER_H
#define GAME_PAWNCONTROLLER_H

#include "IController.h"

namespace KUDA
{
    class Pawn;

    class PawnController : public IController
    {
        friend class Pawn;

    protected:
        Pawn* controlledPawn = nullptr;

    protected:
        void SetControlledX( float x );

        void SetControlledY( float y );

        void SetControlledDirection( float direction );

    public:
        Pawn& GetControlledPawn();

        virtual ~PawnController() = default;
    };
}


#endif //GAME_PAWNCONTROLLER_H
