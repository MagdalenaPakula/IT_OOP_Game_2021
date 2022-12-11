#include <cmath>
#include "ray.h"
#include "IMap.h"

KUDA::Ray::Ray( const KUDA::IMap& map, float startX, float startY, float direction ) {
    restrictAngle( direction );
    this->direction = direction;
    float tileSizeX = 100.f / static_cast<float>(map.GetWidth());
    const float tileSizeY = 100.f / static_cast<float>(map.GetHeight());
    const double tangent = tan( direction );
    float tilePosX = floor( startX / tileSizeX ) * tileSizeX;
    const float offsetX = startX - tilePosX;
    float tilePosY = floor( startY / tileSizeY ) * tileSizeY;
    const float offsetY = startY - tilePosY;
    const float tileStepX = direction > M_PI_2 && direction < 3 * M_PI_2 ? -tileSizeX : tileSizeX;
    const float tileStepY = direction > 0 && direction < M_PI ? -tileSizeY : tileSizeY;
    double xStep = tileStepY / tangent;
    double yStep = tileStepX * tangent;
    double xIntercept;
    double yIntercept;
    if ( isLookingRight( direction )) {
        tilePosX += tileSizeX + 0.0001f;
        xStep = abs( xStep );
        if ( !isLookingDown( direction ))
            xIntercept = startX + abs( offsetY / tangent );
        else
            xIntercept = startX + abs(( tileSizeY - offsetY ) / tangent );
    } else {
        tilePosX -= 0.0001f;
        xStep = -abs( xStep );
        if ( !isLookingDown( direction ))
            xIntercept = startX - abs( offsetY / tangent );
        else
            xIntercept = startX - abs(( tileSizeY - offsetY ) / tangent );
    }

    if ( isLookingDown( direction )) {
        tilePosY += tileSizeY + 0.0001f;
        yStep = abs( yStep );
        if ( isLookingRight( direction ))
            yIntercept = startY + abs(( tileSizeX - offsetX ) * tangent );
        else
            yIntercept = startY + abs( offsetX * tangent );
    } else {
        tilePosY -= 0.0001f;
        yStep = -abs( yStep );
        if ( isLookingRight( direction ))
            yIntercept = startY - abs(( tileSizeX - offsetX ) * tangent );
        else
            yIntercept = startY - abs( offsetX * tangent );
    }
    length = INFINITY;

    if ( xStep > -99999999.f && xStep < 99999999.f ) {
        testHorizontalHits( map, startX, startY, direction, tilePosY, tileStepY, xStep, xIntercept );
    }

    if ( yStep > -99999999.f && yStep < 99999999.f ) {
        testVerticalHits( map, startX, startY, direction, tilePosX, tileStepX, yStep, yIntercept );
    }
}

bool KUDA::Ray::isLookingDown( float direction ) {
    return direction > M_PI;
}

bool KUDA::Ray::isLookingRight( float direction ) {
    return direction < M_PI_2 || direction > 3 * M_PI_2;
}

void KUDA::Ray::restrictAngle( float& direction ) {
    while ( direction < 0 ) direction += 2 * M_PI;
    while ( direction > M_PI * 2 ) direction -= 2 * M_PI;
}

void KUDA::Ray::testHorizontalHits( const KUDA::IMap& map,
                                    float startX,
                                    float startY,
                                    float direction,
                                    float tilePosY,
                                    float tileStepY,
                                    double xStep,
                                    double xIntercept ) {
    for ( int i = 0; i < map.GetHeight(); ++i ) {
        auto x = static_cast<float>(xIntercept + i * xStep);
        auto y = static_cast<float>(tilePosY + i * tileStepY);
        if ( x < 0 || x > 100 || y < 0 || y > 100 ) break;
        if ( map.IsWall( x, y )) {
            auto newDistance = static_cast<float>(sqrt( pow( x - startX, 2 ) + pow( y - startY, 2 )));
            if ( newDistance < length ) {
                hitWall = map.ValueAtPosition( x, y );
                endX = x;
                endY = y;
                length = static_cast<float>(sqrt( pow( endX - startX, 2 ) + pow( endY - startY, 2 )));
                if ( !isLookingDown( direction ))
                    lightDirection = South;
                else
                    lightDirection = North;
            }
            return;
        }
    }
}

void KUDA::Ray::testVerticalHits( const KUDA::IMap& map,
                                  float startX,
                                  float startY,
                                  float direction,
                                  float tilePosX,
                                  float tileStepX,
                                  double yStep,
                                  double yIntercept ) {
    for ( int i = 0; i < map.GetHeight(); ++i ) {
        auto x = static_cast<float>(tilePosX + i * tileStepX);
        auto y = static_cast<float>(yIntercept + i * yStep);
        if ( x < 0 || x > 100 || y < 0 || y > 100 ) break;
        if ( map.IsWall( x, y )) {
            auto newDistance = static_cast<float>(sqrt( pow( x - startX, 2 ) + pow( y - startY, 2 )));
            if ( newDistance < length ) {
                hitWall = map.ValueAtPosition( x, y );
                endY = y;
                endX = x;
                length = newDistance;
                if ( isLookingRight( direction ))
                    lightDirection = West;
                else
                    lightDirection = East;
            }
            return;
        }
    }
}
