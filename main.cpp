/*Compute best best ball team*/

#include "Player.h"

#include <iostream>
#include <fstream>

//forward declarations
void CheckArguments(int argc);
void HandleMissingFileArgument();
void ReadPlayerStats(std::string fileName);

int main(int argc, char* argv[])
{
    CheckArguments(argc);

    std::string statsFile = std::string(argv[1]);
    ReadPlayerStats(statsFile);
}

void CheckArguments(int argc)
{
    if (argc < 1)
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

void ReadPlayerStats(std::string i_fileName)
{    
    std::ifstream statsFile = std::ifstream(i_fileName, std::ios::in);
    if (statsFile.is_open())
    {

        statsFile.close();
    }
    else
    {
        HandleCannotOpenFile();
    }
}

void HandleCannotOpenFile()
{
    std::cout << "Error: cannot open file provided" << std::endl;
    exit(2);
}