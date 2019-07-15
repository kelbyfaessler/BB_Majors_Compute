# distutils: language = c++
# cython: language_level=3

from libcpp.vector cimport vector

from compute_cpp cimport CalculateCombinations2
from compute_cpp cimport Player
from compute_cpp cimport Team

def CalculateCombinationsCpp(players_list):
    #TODO: remove this debug print statement
    print("Inside pyx file before cpp call")
    cdef vector[Player] players_vector
    cdef Player newPlayerCpp
    for pyPlayer in players_list:
        newPlayerCpp.name = pyPlayer.name.encode("UTF-8")
        newPlayerCpp.cost = pyPlayer.cost
        newPlayerCpp.birdieAvg = pyPlayer.birdie_avg
        players_vector.push_back(newPlayerCpp)
    cdef vector[Team] results_vector
    CalculateCombinations2(players_vector, results_vector)

    #For now, print results
    print("==================================== RESULTS ===================================")
    for team in results_vector:
        print(f"Team birdie avg: {team.GetBirdieAvg()}")
        print(f"Team cost: {team.GetCost()}")
        print(f"Player: {team.GetPlayer1()}")
        print(f"Player: {team.GetPlayer2()}")
        print(f"Player: {team.GetPlayer3()}")
        print(f"Player: {team.GetPlayer4()}")
        print("--------------------------------------------")

    #return results_vector       ################# will this work or do I need to explicity convert vector to list?