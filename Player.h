#pragma once
#include <string>

struct Player
{
    int id;
    std::string name;
    float cost;
    float birdieAvg;

    struct Player()
    : name("")
    , cost(0.0f)
    , birdieAvg(0.0f)
    {};

    struct Player(const Player& rhs)
    : id(rhs.id)
    , name(rhs.name)
    , cost(rhs.cost)
    , birdieAvg(rhs.birdieAvg)
    {};

    struct Player(int i_id, const std::string& i_name, float i_cost, float i_birdieAvg)
    : id(i_id)
    , name(i_name)
    , cost(i_cost)
    , birdieAvg(i_birdieAvg)
    {};
};

struct less_than_id
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.id < player2.id);
    }
};

struct greater_than_id
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.id > player2.id);
    }
};

struct player_less_than_cost
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.cost < player2.cost);
    }
};

struct player_greater_than_cost
{
    inline bool operator() (const Player& player1, const Player& player2)
    {
        return (player1.cost > player2.cost);
    }
};