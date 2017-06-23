#include "Team.h"

Team::Team()
{
    for (Player* player : members)
    {
        player = nullptr;
    }
}

Team::Team(Player* p1, Player* p2, Player* p3, Player* p4)
{
    members[0] = p1;
    members[1] = p2;
    members[2] = p3;
    members[3] = p4;
}

Team::~Team()
{

}

float Team::GetCost()
{
    float cost = 0.0;
    for (Player* player : members)
    {
        if (player != nullptr)
        {
            cost += player->cost;
        }
    }
    return cost;
}