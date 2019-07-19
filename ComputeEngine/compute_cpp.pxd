from libcpp.vector cimport vector
from libcpp.string cimport string

cdef extern from "Key.cpp":
    pass

cdef extern from "Player.h":
    struct Player:
        string name
        float cost
        float birdieAvg

cdef extern from "Team.cpp":
    pass

cdef extern from "Team.h":
    cdef cppclass Team:
        Team() except +
        Player GetPlayer1()
        Player GetPlayer2()
        Player GetPlayer3()
        Player GetPlayer4()
        float GetCost() const
        float GetBirdieAvg() const


cdef extern from "main.cpp":
    void CalculateCombinations2(vector[Player]& players, vector[Team]& results, int numTeams)