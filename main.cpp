/*Compute best best ball team*/

#include "Player.h"
#include "Team.h"
#include "Key.h"

#include <vector>
#include <map>
#include <iostream>
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
void CalculateCombinations(std::vector<Player>& playerStats);
void Generate2ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData);
void Generate3ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData);

typedef std::chrono::steady_clock Clock;

//Constants
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
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Name: " << players[87].name << std::endl;
    std::cout << "ID  : " << players[87].id << std::endl;
    std::cout << "Cost: " << players[87].cost << std::endl;
    std::cout << "Birdie Avg: " << players[87].birdieAvg << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Name: " << players[102].name << std::endl;
    std::cout << "ID  : " << players[102].id << std::endl;
    std::cout << "Cost: " << players[102].cost << std::endl;
    std::cout << "Birdie Avg: " << players[102].birdieAvg << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Name: " << players[45].name << std::endl;
    std::cout << "ID  : " << players[45].id << std::endl;
    std::cout << "Cost: " << players[45].cost << std::endl;
    std::cout << "Birdie Avg: " << players[45].birdieAvg << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    //END TEST

    CalculateCombinations(players);
    //PrintBestCombinations();
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
void CalculateCombinations(std::vector<Player>& playerStats)
{   
    std::map<unsigned long, TeamData>* teamData = new std::map<unsigned long, TeamData>();
    auto timeBegin2Man = Clock::now();
    Generate2ManTeamCombos(playerStats, teamData);
    auto timeEnd2Man = Clock::now();
    int twoManCombos = teamData->size();
    std::cout << "Two man combos: " << twoManCombos << std::endl;

    auto timeBegin3Man = Clock::now();
    Generate3ManTeamCombos(playerStats, teamData);
    auto timeEnd3Man = Clock::now();
    std::cout << "Three man combos: " << teamData->size() - twoManCombos << std::endl;
    std::cout << "Total combos: " << teamData->size() << std::endl;

    //GenerateBest4ManTeamCombos();

    std::map<unsigned long, TeamData>::iterator it = teamData->find(102087045);
    if (it != teamData->end())
    {
        TeamData testTeam = it->second;
        std::cout << "Total team cost: " << testTeam.totalCost << std::endl;
        std::cout << "Total team birdie: " << testTeam.totalBirdieAvg << std::endl;
    }
    else
    {
        std::cout << "Could not find team in map" << std::endl;
    }

    //TEST TIMERS
    std::chrono::duration<double> time2Man = 
        std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd2Man - timeBegin2Man);
    std::cout << "Generate 2 man teams: " << time2Man.count() << " sec" << std::endl;
    std::chrono::duration<double> time3Man =
        std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd3Man - timeBegin3Man);
    std::cout << "Generate 3 man teams: " << time3Man.count() << " sec" << std::endl;
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
        TeamData twoManTeamData = it->second;
        ExtractTwoManIds(it->first, idLow, idHigh);
        for (int idNew = idHigh + 1; idNew < players.size(); ++idNew)
        {
            //SortIdsLowToHigh(id1, id2, id3);
            //TEST
            /*if (id1 == 45 && id2 == 87 && id3 == 102)
            {
                std::cout << "Found 3 man team" << std::endl;
            }*/
            //END TEST
            Player newPlayer = players.at(idNew);
            float teamCost = twoManTeamData.totalCost + newPlayer.cost;
            float teamBirdieAvg = twoManTeamData.totalBirdieAvg + newPlayer.birdieAvg;
            unsigned long key = CalculateTeamKey(idLow, idHigh, idNew);
            teamData->insert(std::pair<unsigned long, TeamData>(key, TeamData(teamCost, teamBirdieAvg)));
        }
    }
}





void GenerateBest4ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData)
{
    //Make sure to check total cost < 30000 before adding team
}

void PrintBestCombinations()
{

}