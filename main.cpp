/*Compute best best ball team*/

#include "Player.h"

#include <vector>
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

//Constants
std::string DELIMITER = ",";

int main(int argc, char* argv[])
{
    CheckArguments(argc);

    std::string statsFile = std::string(argv[1]);
    std::vector<Player> statsVector;
    statsVector.reserve(200);
    ReadPlayerStats(statsFile, statsVector);

    //TEST
    for (Player player : statsVector)
    {
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Name: " << player.name << std::endl;
        std::cout << "Cost: " << player.cost << std::endl;
        std::cout << "Birdie Avg: " << player.birdieAvg << std::endl;
    }
    //END TEST
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
        while (std::getline(statsFile, line))
        {
            std::string name = ExtractSubstring(line);
            std::string costStr = ExtractSubstring(line);
            std::string birdieAvgStr = ExtractSubstring(line);
            if (name != "" && costStr != "")
            {
                float birdieAvg = CalculateBirdieAvg(birdieAvgStr);
                Player player = Player(name, std::stof(costStr), birdieAvg);
                statsVector.push_back(player);
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