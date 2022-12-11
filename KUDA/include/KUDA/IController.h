#ifndef GAME_ICONTROLLER_H
#define GAME_ICONTROLLER_H

namespace KUDA{
    class IController {
    public:
        virtual void OnUpdate(int deltaTime) = 0;
    };
}

#endif //GAME_ICONTROLLER_H
