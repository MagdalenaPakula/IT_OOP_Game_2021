#include <cmath>
#include "camera.h"

auto vectorLength( sf::Vector2f v ) {
    return sqrt( pow( v.x, 2 ) + pow( v.y, 2 ));
}

KUDA::Camera::Camera( std::weak_ptr<Pawn> pawn, float fieldOfView ) : _pawn( std::move( pawn )),
                                                                      _fieldOfView( fieldOfView ) {
}

KUDA::Camera* KUDA::Camera::FromDegrees( std::weak_ptr<Pawn> pawn, int fieldOfView ) {
    return new Camera( std::move( pawn ), static_cast<float>(( fieldOfView * M_PI / 180.f )));
}

float KUDA::Camera::GetFieldOfView() const {
    return _fieldOfView;
}

void KUDA::Camera::SetFieldOfView( float fieldOfView ) {
    _fieldOfView = fieldOfView;
}

void KUDA::Camera::AttachTo( std::weak_ptr<Pawn> pawn ) {
    _pawn = std::move( pawn );
}

KUDA::Pawn& KUDA::Camera::GetControlledPawn() const {
    auto pawn = _pawn.lock();
    if ( pawn == nullptr )
        throw std::runtime_error( "Camera has no pawn" );

    return *pawn;
}

float KUDA::Camera::DistanceTo( const KUDA::Actor& other ) const {
    auto pawn = _pawn.lock();
    if ( pawn == nullptr )
        throw std::runtime_error( "Camera has no pawn" );

    return static_cast<float>(sqrt( pow( pawn->GetPositionX() - other.GetPositionX(),
                                         2 ) + pow( pawn->GetPositionY() - other.GetPositionY(), 2 )));
}

float KUDA::Camera::DirectionTo( const KUDA::Actor& other ) const {
    auto pawn = _pawn.lock();
    if ( pawn == nullptr )
        throw std::runtime_error( "Camera has no pawn" );

    float dy = pawn->GetPositionY() - other.GetPositionY();
    float dx = (other.GetPositionX() - pawn->GetPositionX());
    auto directionToOther = atan( dy / dx );
    auto result = pawn->GetDirection() - directionToOther;

    if (other.GetPositionX() < pawn->GetPositionX())
        result += M_PI; // Don't know why, but it fixes it

    while (result > M_PI) result -= 2 * M_PI;
    while (result < -M_PI) result += 2* M_PI;
    return result;
}
