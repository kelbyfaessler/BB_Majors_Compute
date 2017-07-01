#pragma once

unsigned long CalculateTeamKey(int player1Id, int player2Id, int player3Id = 0, int player4Id = 0);

void ExtractTwoManIds(unsigned long key, int& idLow, int& idMid);
void ExtractThreeManIds(unsigned long key, int& idLow, int& idMid, int& idHigh);
void SortIdsLowToHigh(int& idLow, int& idMid, int& idHigh);