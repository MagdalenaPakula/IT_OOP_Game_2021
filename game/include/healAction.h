#ifndef GAME_HEALACTION_H
#define GAME_HEALACTION_H

#include "IPickupAction.h"

class HealAction : public IPickupAction
{
private:
    int _amount;
public:
    explicit HealAction( int amount );

    void InvokeOn( Player& player ) override;
};


#endif //GAME_HEALACTION_H
