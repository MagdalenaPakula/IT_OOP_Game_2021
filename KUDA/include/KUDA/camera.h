#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <memory>
#include "pawn.h"

namespace KUDA
{
    class Camera
    {
    private:
        float _fieldOfView = 0;
        std::weak_ptr<Pawn> _pawn;
    public:
        explicit Camera( std::weak_ptr<Pawn> pawn, float fieldOfView );

        static Camera* FromDegrees( std::weak_ptr<Pawn> pawn, int fieldOfView );

        [[nodiscard]] float GetFieldOfView() const;

        void SetFieldOfView( float fieldOfView );

        void AttachTo( std::weak_ptr<Pawn> pawn );

        [[nodiscard]] Pawn& GetControlledPawn() const;

        [[nodiscard]] float DistanceTo( const Actor& other ) const;

        [[nodiscard]] float DirectionTo( const Actor& other ) const;
    };
}


#endif //GAME_CAMERA_H
