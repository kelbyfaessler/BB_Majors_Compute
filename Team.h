#pragma once
#include "Player.h"

class Team
{
public:
    Team();
    Team(Player* p1, Player* p2, Player* p3, Player* p4);
    ~Team();

    void SetPlayers(Player* p1, Player* p2, Player* p3, Player* p4);
    void SetPlayer1(Player* p1);
    void SetPlayer2(Player* p2);
    void SetPlayer3(Player* p3);
    void SetPlayer4(Player* p4);

    float GetCost();

private:
    Player* members[4];
};

struct TeamData
{
    float totalCost;
    float totalBirdieAvg;

    struct TeamData()
    : totalCost(0.0f)
    , totalBirdieAvg(0.0f)
    {};

    struct TeamData(float i_cost, float i_birdieAvg)
    : totalCost(i_cost)
    , totalBirdieAvg(i_birdieAvg)
    {};
};