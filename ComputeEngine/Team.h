#pragma once
#include "Player.h"

const int PLAYERS_PER_TEAM = 4;

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

    void SetPlayer(int player_index, Player player);
    void SetPlayers(Player p1, Player p2, Player p3, Player p4);

    int GetNumPlayers();
    Player GetPlayer(int player_index);
    float GetCost() const;
    float GetBirdieAvg() const;

private:
    Player members[PLAYERS_PER_TEAM];
    float cost;
    float birdieAvg;
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
