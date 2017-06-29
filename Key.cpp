/* Contains global functionality related to player ID's and keys for the dictionary that
   stores teams of players*/
#include "Key.h"

unsigned long CalculateTeamKey(int player1Id, int player2Id, int player3Id, int player4Id)
{
    return (player4Id * 1000000000) + (player3Id * 1000000) + (player2Id * 1000) + player1Id;
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