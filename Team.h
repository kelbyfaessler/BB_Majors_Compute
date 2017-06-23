#pragma once
#include "Player.h"

class Team
{
public:
    Team();
    Team(Player* p1, Player* p2, Player* p3, Player* p4);
    ~Team();
    float GetCost();

private:
    Player* members[4];
};