#ifndef GAME_IPICKUPACTION_H
#define GAME_IPICKUPACTION_H

#include "player.h"

class IPickupAction
{
public:
    virtual ~IPickupAction() = default;
    virtual void InvokeOn( Player& player ) = 0;
};


#endif //GAME_IPICKUPACTION_H
