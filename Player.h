#pragma once
#include <string>

struct Player
{
    std::string name;
    float cost;
    float birdieAvg;

    struct Player()
    : name("")
    , cost(0.0f)
    , birdieAvg(0.0f)
    {};

    struct Player(const std::string& i_name, float i_cost, float i_birdieAvg)
    : name(i_name)
    , cost(i_cost)
    , birdieAvg(i_birdieAvg)
    {};
};

struct less_than_cost
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.cost < player2.cost);
    }
};

struct greater_than_cost
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.cost > player2.cost);
    }
};

struct less_than_birdie_avg
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.birdieAvg < player2.birdieAvg);
    }
};

struct greater_than_birdie_avg
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.birdieAvg > player2.birdieAvg);
    }
};