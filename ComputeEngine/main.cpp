/*Compute best best ball team*/

#include "Player.h"
#include "Team.h"
#include "Key.h"

#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <chrono> //Timers for testing purposes

//forward declarations
void CheckArguments(int argc);
void HandleMissingFileArgument();
void ReadPlayerStats(std::string fileName, std::map<unsigned int, Player>& players);
void ReadPlayerStats(std::string fileName, std::vector<Player>& stats);
std::string ExtractSubstring(std::string& line);
float CalculateBirdieAvg(std::string birdieAvgStr);
void HandleMissingRequiredStats();
void HandleCannotOpenFile();
void CalculateCombinations(std::vector<Player>& players,
    std::priority_queue<Team, std::vector<Team>, greater_than_birdie_avg>& minBirdieAvgQueue);
void Generate2ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData);
void Generate3ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData);
void GenerateBest4ManTeamCombos(std::vector<Player>& players,
    std::map<unsigned long, TeamData>* teamData,
    std::priority_queue<Team, std::vector<Team>, greater_than_birdie_avg>& minBirdieAvgQueue);
void PrintBestCombinations(std::vector<Player>& players,
    std::priority_queue<Team, std::vector<Team>, greater_than_birdie_avg>& results);


typedef std::chrono::steady_clock Clock;

//Constants
const float MAX_TEAM_COST = 30000;
const int MAX_NUM_OUTPUT_TEAMS = 10;
std::string DELIMITER = ",";

int main(int argc, char* argv[])
{
    CheckArguments(argc);

    std::string statsFile = std::string(argv[1]);
    //std::map<unsigned int, Player> players;
    std::vector<Player> players;
    players.reserve(200);
    ReadPlayerStats(statsFile, players);
    std::cout << "Players in array: " << players.size() << std::endl;

    //TEST
    //for (Player player : statsVector)
    //{
    //    std::cout << "--------------------------------------" << std::endl;
    //    std::cout << "Name: " << player.name << std::endl;
    //    std::cout << "Cost: " << player.cost << std::endl;
    //    std::cout << "Birdie Avg: " << player.birdieAvg << std::endl;
    //}
    //std::cout << "--------------------------------------" << std::endl;
    //std::cout << "Name: " << players[87].name << std::endl;
    //std::cout << "ID  : " << players[87].id << std::endl;
    //std::cout << "Cost: " << players[87].cost << std::endl;
    //std::cout << "Birdie Avg: " << players[87].birdieAvg << std::endl;
    //std::cout << "--------------------------------------" << std::endl;
    //std::cout << "Name: " << players[102].name << std::endl;
    //std::cout << "ID  : " << players[102].id << std::endl;
    //std::cout << "Cost: " << players[102].cost << std::endl;
    //std::cout << "Birdie Avg: " << players[102].birdieAvg << std::endl;
    //std::cout << "--------------------------------------" << std::endl;
    //std::cout << "Name: " << players[45].name << std::endl;
    //std::cout << "ID  : " << players[45].id << std::endl;
    //std::cout << "Cost: " << players[45].cost << std::endl;
    //std::cout << "Birdie Avg: " << players[45].birdieAvg << std::endl;
    //std::cout << "--------------------------------------" << std::endl;
    //END TEST

    std::priority_queue<Team, std::vector<Team>, greater_than_birdie_avg> results;

    CalculateCombinations(players, results);
    PrintBestCombinations(players, results);
}

void CheckArguments(int argc)
{
    if (argc < 2)
    {
        HandleMissingFileArgument();
    }
}

void HandleMissingFileArgument()
{
    std::cout << "Error: include stats file as argument" << std::endl;
    std::cout << "Usage: BBMajorsCompute <stats .csv file>" << std::endl;
    exit(1);
}

void ReadPlayerStats(std::string i_fileName, std::map<unsigned int, Player>& players)
{
    std::ifstream statsFile = std::ifstream(i_fileName, std::ios::in);
    if (statsFile.is_open())
    {
        std::string line;
        std::getline(statsFile, line); //header line, throwaway
        unsigned int playerId = 0;
        while (std::getline(statsFile, line))
        {
            std::string name = ExtractSubstring(line);
            std::string costStr = ExtractSubstring(line);
            std::string birdieAvgStr = ExtractSubstring(line);
            if (name != "" && costStr != "")
            {
                float birdieAvg = CalculateBirdieAvg(birdieAvgStr);
                Player player = Player(playerId, name, std::stof(costStr), birdieAvg);
                players.insert(std::pair<unsigned int, Player>(playerId, player));
                ++playerId;
                if (birdieAvg < 0)
                {
                    std::cout << "No birdie average for: " << name << std::endl;
                }
            }
            else
            {
                HandleMissingRequiredStats();
            }
        }
        statsFile.close();
    }
    else
    {
        HandleCannotOpenFile();
    }
}

void ReadPlayerStats(std::string i_fileName, std::vector<Player>& statsVector)
{    
    std::ifstream statsFile = std::ifstream(i_fileName, std::ios::in);
    if (statsFile.is_open())
    {
        std::string line;
        std::getline(statsFile, line); //header line, throwaway
        int playerId = 0;
        while (std::getline(statsFile, line))
        {
            std::string name = ExtractSubstring(line);
            std::string costStr = ExtractSubstring(line);
            std::string birdieAvgStr = ExtractSubstring(line);
            if (name != "" && costStr != "")
            {
                float birdieAvg = CalculateBirdieAvg(birdieAvgStr);
                Player player = Player(playerId, name, std::stof(costStr), birdieAvg);
                statsVector.push_back(player);
                //statsVector.at(playerId) = player;
                ++playerId;
                if (birdieAvg < 0)
                {
                    std::cout << "No birdie average for: " << name << std::endl;
                }
            }
            else
            {
                HandleMissingRequiredStats();
            }
        }
        statsFile.close();
    }
    else
    {
        HandleCannotOpenFile();
    }
}

std::string ExtractSubstring(std::string& line)
{
    std::string substring = "";
    size_t pos = line.find(DELIMITER);
    if (pos != std::string::npos)
    {
        substring = line.substr(0, pos);
        line.erase(0, pos + DELIMITER.length());
    }
    else
    {
        substring = line;
    }
    return substring;
}

float CalculateBirdieAvg(std::string birdieAvgStr)
{
    float birdieAvg = -1.0;
    if (birdieAvgStr != "")
    {
        birdieAvg = std::stof(birdieAvgStr);
    }
    return birdieAvg;
}

void HandleMissingRequiredStats()
{
    std::cout << "Error: Skipping stats row. Missing name or cost" << std::endl;
}

void HandleCannotOpenFile()
{
    std::cout << "Error: cannot open file provided" << std::endl;
    exit(2);
}

//Assume ~150 players, of which 4 must be selected. 150!/146! = 486,246,600 permutations
//486,246,600/4! = 20,260,275 combinations
void CalculateCombinations(std::vector<Player>& players,
    std::priority_queue<Team, std::vector<Team>, greater_than_birdie_avg>& results)
{   
    std::map<unsigned long, TeamData>* teamData = new std::map<unsigned long, TeamData>();
    auto timeBegin2Man = Clock::now();
    Generate2ManTeamCombos(players, teamData);
    auto timeEnd2Man = Clock::now();
    int twoManCombos = teamData->size();
    std::cout << "Two man combos: " << twoManCombos << std::endl;

    auto timeBegin3Man = Clock::now();
    Generate3ManTeamCombos(players, teamData);
    auto timeEnd3Man = Clock::now();
    int threeManCombos = teamData->size() - twoManCombos;
    std::cout << "Three man combos: " << threeManCombos << std::endl;

    

    auto timeBegin4Man = Clock::now();
    GenerateBest4ManTeamCombos(players, teamData, results);
    auto timeEnd4Man = Clock::now();

    std::cout << "Four man combos: " << teamData->size() - (twoManCombos + threeManCombos) << std::endl;
    std::cout << "Total combos: " << teamData->size() << std::endl;
    std::cout << "Best teams size: " << results.size() << std::endl;

    //std::map<unsigned long, TeamData>::iterator it = teamData->find(102087045);
    //if (it != teamData->end())
    //{
    //    TeamData testTeam = it->second;
    //    std::cout << "Total team cost: " << testTeam.totalCost << std::endl;
    //    std::cout << "Total team birdie: " << testTeam.totalBirdieAvg << std::endl;
    //}
    //else
    //{   
    //    std::cout << "Could not find team in map" << std::endl;
    //}

    //TEST TIMERS
    std::chrono::duration<double> time2Man = 
        std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd2Man - timeBegin2Man);
    std::cout << "Generate 2 man teams: " << time2Man.count() << " sec" << std::endl;
    std::chrono::duration<double> time3Man =
        std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd3Man - timeBegin3Man);
    std::cout << "Generate 3 man teams: " << time3Man.count() << " sec" << std::endl;
    std::chrono::duration<double> time4Man =
        std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd4Man - timeBegin4Man);
    std::cout << "Generate 4 man teams: " << time4Man.count() << " sec" << std::endl;
    //END TEST TIMERS
}

void Generate2ManTeamCombos(std::vector<Player>& players, std::map<unsigned long, TeamData>* teamData)
{
    bool outputYet = false;
    for (int idLow = 0; idLow < players.size() - 1; ++idLow)
    {
        for (int idHigh = idLow + 1; idHigh < players.size(); ++idHigh)
        {
            unsigned long key = CalculateTeamKey(idLow, idHigh);
            Player player1 = players.at(idLow);
            Player player2 = players.at(idHigh);
            float teamCost = player1.cost + player2.cost;
            //if (teamData->find(key) == teamData->end())
            //{
                float teamBirdieAvg = player1.birdieAvg + player2.birdieAvg;
                teamData->insert(std::pair<unsigned long, TeamData>(key, TeamData(teamCost, teamBirdieAvg)));
            //}
        }
    }
    //TEST
    //std::map<unsigned long, TeamData>::iterator it = teamData->find(99000);
    //if (it != teamData->end())
    //{
    //    TeamData testTeam = it->second;
    //    std::cout << "Total team cost: " << testTeam.totalCost << std::endl;
    //    std::cout << "Total team birdie: " << testTeam.totalBirdieAvg << std::endl;
    //}
    //else
    //{
    //    std::cout << "Could not find team in map" << std::endl;
    //}
    //END TEST
}

void Generate3ManTeamCombos(std::vector<Player>& players, std::map<unsigned long, TeamData>* teamData)
{
    std::map<unsigned long, TeamData>::iterator it;
    for (it = teamData->begin(); it != teamData->end(); ++it)
    {
        int idLow = -1;
        int idHigh = -1;
        ExtractTwoManIds(it->first, idLow, idHigh);
        TeamData twoManTeamData = it->second;
        for (int idNew = idHigh + 1; idNew < players.size(); ++idNew)
        {
            //SortIdsLowToHigh(id1, id2, id3);
            Player newPlayer = players.at(idNew);
            float teamCost = twoManTeamData.totalCost + newPlayer.cost;
            float teamBirdieAvg = twoManTeamData.totalBirdieAvg + newPlayer.birdieAvg;
            unsigned long key = CalculateTeamKey(idLow, idHigh, idNew);
            teamData->insert(std::pair<unsigned long, TeamData>(key, TeamData(teamCost, teamBirdieAvg)));
        }
    }
}

void GenerateBest4ManTeamCombos(std::vector<Player>& players, 
    std::map<unsigned long, TeamData>* teamData,
    std::priority_queue<Team, std::vector<Team>, greater_than_birdie_avg>& minBirdieAvgQueue)
{
    std::map<unsigned long, TeamData>::iterator it;
    for (it = teamData->begin(); it != teamData->end(); ++it)
    {
        int idLow = -1;
        int idMid = -1;
        int idHigh = -1;
        ExtractThreeManIds(it->first, idLow, idMid, idHigh);
        TeamData threeManTeamData = it->second;
        for (int idNew = idHigh + 1; idNew < players.size(); ++idNew)
        {
            Player newPlayer = players.at(idNew);
            float newTeamCost = threeManTeamData.totalCost + newPlayer.cost;
            if (newTeamCost < MAX_TEAM_COST)
            {
                float newTeamBirdieAvg = threeManTeamData.totalBirdieAvg + newPlayer.birdieAvg;
                TeamData newTeamData = TeamData(newTeamCost, newTeamBirdieAvg);

                if (minBirdieAvgQueue.size() >= MAX_NUM_OUTPUT_TEAMS)
                {
                    if (newTeamBirdieAvg > minBirdieAvgQueue.top().GetBirdieAvg())
                    {
                        minBirdieAvgQueue.pop();
                        Player p1 = players.at(idLow);
                        Player p2 = players.at(idMid);
                        Player p3 = players.at(idHigh);
                        Player p4 = players.at(idNew);
                        Team newTeam = Team(p1, p2, p3, p4, newTeamData);
                        minBirdieAvgQueue.push(newTeam);
                    }
                }
                else
                {
                    //queue is not filled yet. Push team onto queue so it will fill up
                    Player p1 = players.at(idLow);
                    Player p2 = players.at(idMid);
                    Player p3 = players.at(idHigh);
                    Player p4 = players.at(idNew);
                    Team newTeam = Team(p1, p2, p3, p4, newTeamData);
                    minBirdieAvgQueue.push(newTeam);
                }
            }
        }
    }
}

void PrintBestCombinations(std::vector<Player>& players,
    std::priority_queue<Team, std::vector<Team>, greater_than_birdie_avg>& results)
{
    std::stack<Team> printStack;
    while (results.size() > 0)  
    {
        Team team = results.top();
        results.pop();
        printStack.push(team);
    }
    
    std::cout << std::endl;
    std::cout << "==================================== RESULTS ===================================" << std::endl;
    while (printStack.size() > 0)
    {
        Team team = printStack.top();
        std::cout << "Team birdie avg: " << team.GetBirdieAvg() << std::endl;
        std::cout << "Team cost: " << team.GetCost() << std::endl;
        std::vector<Player> sortedPlayers;
        sortedPlayers.push_back(team.GetPlayer1());
        sortedPlayers.push_back(team.GetPlayer2());
        sortedPlayers.push_back(team.GetPlayer3());
        sortedPlayers.push_back(team.GetPlayer4());
        std::sort(sortedPlayers.begin(), sortedPlayers.end(), player_less_than_cost());
        std::vector<Player>::iterator it;
        for (it = sortedPlayers.begin(); it != sortedPlayers.end(); ++it)
        {
            std::cout << "Player: " << std::setw(23) << std::left << it->name;
            std::cout << std::setw(7) << std::right << it->cost;
            std::cout << std::setw(7) << std::right << it->birdieAvg;
            std::cout << std::endl;
        }

        std::cout << "--------------------------------------------" << std::endl;
        
        printStack.pop();
    }
    std::cout << "================================================================================" << std::endl;
}