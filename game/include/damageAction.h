#ifndef GAME_DAMAGEACTION_H
#define GAME_DAMAGEACTION_H

#include "IPickupAction.h"

class DamageAction : public IPickupAction
{
private:
    int _amount;
public:
    explicit DamageAction( int amount );

    void InvokeOn( Player& player ) override;
};


#endif //GAME_DAMAGEACTION_H
