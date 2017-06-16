/*Compute best best ball team*/

#include "Player.h"

#include <iostream>

//forward declarations
void ReadPlayerStats(const char* i_fileName);

int main(int argc, char* argv)
{
    if (argc > 1)
    {
        ReadPlayerStats(argv[1]);
    }
    else
    {
        std::cout << "Error: include stats file as argument" << std::endl;
        std::cout << "Usage: BBMajorsCompute <stats .csv file>" << std::endl;
    }

}

void ReadPlayerStats(const char* i_fileName)
{

}