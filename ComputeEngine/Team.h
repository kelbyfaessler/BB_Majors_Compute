#pragma once
#include "Player.h"

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

class Team
{
public:
    Team();
    Team(Player p1, Player p2, Player p3, Player p4);
    Team(Player p1, Player p2, Player p3, Player p4, TeamData teamData);
    ~Team();

    void SetPlayers(Player p1, Player p2, Player p3, Player p4);
    void SetPlayer1(Player p1);
    void SetPlayer2(Player p2);
    void SetPlayer3(Player p3);
    void SetPlayer4(Player p4);

    Player GetPlayer1() { return members[0]; };
    Player GetPlayer2() { return members[1]; };
    Player GetPlayer3() { return members[2]; };
    Player GetPlayer4() { return members[3]; };
    float GetCost() const;
    float GetBirdieAvg() const;

private:
    Player members[4];
    float cost;
    float birdieAvg;
    //TeamData totals;
};

struct greater_than_birdie_avg
{
    inline bool operator() (const TeamData& team1, const TeamData& team2)
    {
        return (team1.totalBirdieAvg > team2.totalBirdieAvg);
    }

    inline bool operator() (const Team& team1, const Team& team2)
    {
        return (team1.GetBirdieAvg() > team2.GetBirdieAvg());
    }
};
