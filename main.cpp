/*Compute best best ball team*/

#include "Player.h"
#include "Team.h"

#include <vector>
#include <map>
#include <iostream>
#include <fstream>

//forward declarations
void CheckArguments(int argc);
void HandleMissingFileArgument();
void ReadPlayerStats(std::string fileName, std::vector<Player>& stats);
std::string ExtractSubstring(std::string& line);
float CalculateBirdieAvg(std::string birdieAvgStr);
void HandleMissingRequiredStats();
void HandleCannotOpenFile();
void CalculateCombinations(std::vector<Player>& playerStats);
void Generate2ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData);
void Generate3ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData);
unsigned long CalculateTeamKey(int player1Id, int player2Id, int player3Id = 0, int player4Id = 0);
void SortIdsLowToHigh(int& idLow, int& idMid, int& idHigh);
void ExtractTwoManIds(unsigned long key, int& id1, int& id2);

//Constants
std::string DELIMITER = ",";

int main(int argc, char* argv[])
{
    CheckArguments(argc);

    std::string statsFile = std::string(argv[1]);
    std::vector<Player> playerStats;
    playerStats.reserve(200);
    ReadPlayerStats(statsFile, playerStats);

    //TEST
    //for (Player player : statsVector)
    //{
    //    std::cout << "--------------------------------------" << std::endl;
    //    std::cout << "Name: " << player.name << std::endl;
    //    std::cout << "Cost: " << player.cost << std::endl;
    //    std::cout << "Birdie Avg: " << player.birdieAvg << std::endl;
    //}
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Name: " << playerStats[87].name << std::endl;
    std::cout << "ID  : " << playerStats[87].id << std::endl;
    std::cout << "Cost: " << playerStats[87].cost << std::endl;
    std::cout << "Birdie Avg: " << playerStats[87].birdieAvg << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Name: " << playerStats[102].name << std::endl;
    std::cout << "ID  : " << playerStats[102].id << std::endl;
    std::cout << "Cost: " << playerStats[102].cost << std::endl;
    std::cout << "Birdie Avg: " << playerStats[102].birdieAvg << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Name: " << playerStats[45].name << std::endl;
    std::cout << "ID  : " << playerStats[45].id << std::endl;
    std::cout << "Cost: " << playerStats[45].cost << std::endl;
    std::cout << "Birdie Avg: " << playerStats[45].birdieAvg << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    //int a = 99;
    //int b = 52;
    //int c = 10;
    //SortIdsLowToHigh(a, b, c);
    //std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    //a = 99;
    //b = 10;
    //c = 52;
    //SortIdsLowToHigh(a, b, c);
    //std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    //a = 52;
    //b = 99;
    //c = 10;
    //SortIdsLowToHigh(a, b, c);
    //std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    //a = 52;
    //b = 10;
    //c = 99;
    //SortIdsLowToHigh(a, b, c);
    //std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    //a = 10;
    //b = 99;
    //c = 52;
    //SortIdsLowToHigh(a, b, c);
    //std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    //a = 10;
    //b = 52;
    //c = 99;
    //SortIdsLowToHigh(a, b, c);
    //std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    //END TEST

    CalculateCombinations(playerStats);
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
    
    Generate2ManTeamCombos(playerStats, teamData);
    //std::cout << "Two man combos: " << teamData->size() << std::endl;
    Generate3ManTeamCombos(playerStats, teamData);
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
}

void Generate2ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData)
{
    bool outputYet = false;
    for (std::vector<Player>::iterator itLow = playerStats.begin(); itLow != playerStats.end() - 1; ++itLow)
    {
        for (std::vector<Player>::iterator itHigh = itLow + 1; itHigh != playerStats.end(); ++itHigh)
        {
            int player1Id = itLow->id;
            int player2Id = itHigh->id;
            //if (!outputYet)
            //{
            //    std::cout << "Low player id : " << itLow->id << std::endl;
            //    std::cout << "High player id: " << itHigh->id << std::endl;
            //    outputYet = true;
            //}
            //if (itLow->id == 0)
            //{
            //    std::cout << "Low player id : " << itLow->id << std::endl;
            //    std::cout << "High player id: " << itHigh->id << std::endl;
            //}
            unsigned long key = CalculateTeamKey(player1Id, player2Id);
            float teamCost = itLow->cost + itHigh->cost;
            //if (teamData->find(key) == teamData->end())
            //{
                float teamBirdieAvg = itLow->birdieAvg + itHigh->birdieAvg;
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

unsigned long CalculateTeamKey(int player1Id, int player2Id, int player3Id, int player4Id)
{
    //if (player1Id == 0 && player2Id == 99)
    //{
    //    std::cout << "Calculated key for test team: " << (player4Id * 1000000000) + (player3Id * 1000000) + (player2Id * 100) + player1Id << std::endl;
    //}
    return (player4Id * 1000000000) + (player3Id * 1000000) + (player2Id * 1000) + player1Id;
}

void Generate3ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData)
{
    std::map<unsigned long, TeamData>::iterator it;
    for (it = teamData->begin(); it != teamData->end(); ++it)
    {
        int id1 = -1;
        int id2 = -1;
        TeamData twoManTeamData = it->second;
        ExtractTwoManIds(it->first, id1, id2);
        for (std::vector<Player>::iterator itNew = playerStats.begin(); itNew != playerStats.end() - 1; ++itNew)
        {
            if (itNew->id != id1 && itNew->id != id2)
            {
                int id3 = itNew->id;

                SortIdsLowToHigh(id1, id2, id3);
                //TEST
                if (id1 == 45 && id2 == 87 && id3 == 102)
                {
                    std::cout << "Found 3 man team" << std::endl;
                }
                //END TEST
                float teamCost = twoManTeamData.totalCost + itNew->cost;
                float teamBirdieAvg = twoManTeamData.totalBirdieAvg + itNew->birdieAvg;
                unsigned long key = CalculateTeamKey(id1, id2, id3);
                teamData->insert(std::pair<unsigned long, TeamData>(key, TeamData(teamCost, teamBirdieAvg)));
            }
        }
    }
}

//id1 will be lesser id value
void ExtractTwoManIds(unsigned long key, int& id1, int& id2)
{
    id1 = key % 1000;
    id2 = key / 1000;
}

//Sorts low to high
void SortIdsLowToHigh(int& idLow, int& idMid, int& idHigh)
{
    int arr[3] = { idLow, idMid, idHigh };
    int temp;
    if (idHigh < idMid)
    {
        temp = idMid;
        idMid = idHigh;
        idHigh = temp;
    }
    if (idMid < idLow)
    {
        temp = idLow;
        idLow = idMid;
        idMid = temp;
    }
    if (idHigh < idMid)
    {
        temp = idMid;
        idMid = idHigh;
        idHigh = temp;
    }
}

void GenerateBest4ManTeamCombos(std::vector<Player>& playerStats, std::map<unsigned long, TeamData>* teamData)
{
    //Make sure to check total cost < 30000 before adding team
}

void PrintBestCombinations()
{

}