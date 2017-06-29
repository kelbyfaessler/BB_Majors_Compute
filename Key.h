#pragma once

unsigned long CalculateTeamKey(int player1Id, int player2Id, int player3Id = 0, int player4Id = 0);

void ExtractTwoManIds(unsigned long key, int& id1, int& id2);

void SortIdsLowToHigh(int& idLow, int& idMid, int& idHigh);