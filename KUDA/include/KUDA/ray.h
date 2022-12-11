#ifndef GAME_RAY_H
#define GAME_RAY_H


namespace KUDA
{
    class IMap;

    class Ray
    {
    public:
        enum Direction
        {
            North,
            East,
            South,
            West
        };
    public:
        float endX;
        float endY;
        int hitWall;
        Direction lightDirection;
        float direction;
        float length;
    public:
        explicit Ray( const IMap& map, float startX, float startY, float direction );

    private:
        static bool isLookingDown( float direction );

        static bool isLookingRight( float direction );

        static void restrictAngle( float& direction );

        void testHorizontalHits( const IMap& map,
                                 float startX,
                                 float startY,
                                 float direction,
                                 float tilePosY,
                                 float tileStepY,
                                 double xStep,
                                 double xIntercept );

        void testVerticalHits( const IMap& map,
                               float startX,
                               float startY,
                               float direction,
                               float tilePosX,
                               float tileStepX,
                               double yStep,
                               double yIntercept );
    };
}


#endif //GAME_RAY_H
