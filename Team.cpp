#include "Team.h"

Team::Team()
    : cost(-1.0), birdieAvg(-1.0)
{
}

Team::Team(Player p1, Player p2, Player p3, Player p4)
: members { p1, p2, p3, p4}
{
    cost = p1.cost + p2.cost + p3.cost + p4.cost;
    birdieAvg = p1.birdieAvg + p2.birdieAvg + p3.birdieAvg + p4.birdieAvg;
}

Team::Team(Player p1, Player p2, Player p3, Player p4, TeamData teamData)
    : members{ p1, p2, p3, p4} 
    , cost(teamData.totalCost)
    , birdieAvg(teamData.totalBirdieAvg)
{
}

Team::~Team()
{

}

void Team::SetPlayers(Player p1, Player p2, Player p3, Player p4)
{
    members[0] = p1;
    members[1] = p2;
    members[2] = p3;
    members[3] = p4;
}

void Team::SetPlayer1(Player p1)
{
    members[0] = p1;
}

void Team::SetPlayer2(Player p2)
{
    members[1] = p2;
}

void Team::SetPlayer3(Player p3)
{
    members[2] = p3;
}

void Team::SetPlayer4(Player p4)
{
    members[3] = p4;
}

float Team::GetCost() const
{
    float retCost = 0.0;
    if (cost > 0.0)
    {
        retCost = cost;
    }
    else
    {
        for (Player player : members)
        {
            retCost += player.cost;
        }
    }
    return retCost;
}

float Team::GetBirdieAvg() const
{
    float retBirdieAvg = 0.0;
    if (birdieAvg > 0.0)
    {
        retBirdieAvg = birdieAvg;
    }
    else
    {
        for (Player player : members)
        {
            retBirdieAvg += player.birdieAvg;
        }
    }
    return retBirdieAvg;
}