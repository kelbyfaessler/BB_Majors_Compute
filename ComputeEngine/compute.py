###############################################################################
# Compute algorithm ported from C++ to python
###############################################################################

# Algorithm design in python:
#   Allow for function to be called from other python code (passing player list)
#       or as a standalone script (reads player list from file like c++ code)
#   Create class for player (name, cost, birdie avg)
#   Is it possible to have an algorithm that is more efficient than O(n^4)? It 
#       doesn't seem possible because we need to look at all team combinations.
#       unless there is some clever way to somehow only look at the best teams
#       and ignore other combos of players? Maybe this would work if we sorted
#       the player list by birdie avg and iterate from the top down, checking 
#       if a team is less than total cost allowance and if it's a better team
#       than the current 10 best. If it's not, then we can immidiately move to
#       a new combo of players since we know its only going to get worse
#   Is this a version of the knapsack problem without repeats?
#       Is that the 0/1 knapsack problem?
#       Use the 'meet in the middle' algorithm since I have non-integer weights
#       (costs)
#   Search for knapsack problem dynamic programming
#   Might be interesting to run a c++ solution not using dynamic programming 
#       and compare runtimes to the dynamic programming solution

import argparse
import csv
from typing import List
from time import perf_counter

DEFAULT_NUM_TEAMS = 10
TOTAL_ALLOWABLE_COST = 30000

class Player:
    def __init__(self, name: str='', cost: float=0.0, birdie_avg: float=0.0):
        self.name = name
        self.cost = cost
        self.birdie_avg = birdie_avg

class PlayerPair:
    def __init__(self, player1: Player, player2: Player):
        self.player1 = player1
        self.player2 = player2
        self.total_cost = self.player1.cost + self.player2.cost
        self.total_birdie_avg = self.player1.birdie_avg + self.player2.birdie_avg

class PlayerTeam:
    def __init__(self, player1: Player, player2: Player, player3: Player, player4: Player):
        self.player1 = player1
        self.player2 = player2
        self.player3 = player3
        self.player4 = player4
        self.total_cost = ( self.player1.cost + 
                            self.player2.cost + 
                            self.player3.cost + 
                            self.player4.cost)
        self.total_birdie_avg = (self.player1.birdie_avg + 
                                    self.player2.birdie_avg + 
                                    self.player3.birdie_avg + 
                                    self.player4.birdie_avg)    

def calculate_combos(players: List[Player], num_teams: int=None) -> None:
    if num_teams == None:
        num_teams = DEFAULT_NUM_TEAMS

    teams_begin = perf_counter()
    best_teams = []
    player_count = len(players)
    print(f"player count: {player_count}")
    for idx1 in range(0, player_count - 3):
        for idx2 in range(idx1 + 1, player_count - 2):
            for idx3 in range (idx2 + 1, player_count - 1):
                for idx4 in range(idx3 + 1, player_count):
                    player1 = players[idx1]
                    player2 = players[idx2]
                    player3 = players[idx3]
                    player4 = players[idx4]
                    #print("Now considering the following players:")
                    #print_player(player1)
                    #print_player(player2)
                    #print_player(player3)
                    #print_player(player4)
                    team_cost = player1.cost + player2.cost + player3.cost + player4.cost
                    if team_cost < TOTAL_ALLOWABLE_COST:
                        if len(best_teams) < num_teams:
                            #print("Adding team, best teams not filled")
                            best_teams.append(PlayerTeam(player1, 
                                                         player2, 
                                                         player3, 
                                                         player4))
                        else:
                            team_birdie_avg = (player1.birdie_avg + 
                                                player2.birdie_avg + 
                                                player3.birdie_avg + 
                                                player4.birdie_avg)
                            if team_birdie_avg > best_teams[0].total_birdie_avg:
                                #print("Adding better team, best teams filled")
                                best_teams[0] = PlayerTeam(player1, 
                                                            player2, 
                                                            player3, 
                                                            player4)
                        best_teams.sort(key=lambda team: team.total_birdie_avg)

    teams_end = perf_counter()
    print(f"Time to create teams: {teams_end - teams_begin}")
    print("")
    print_teams(best_teams[::-1])

    # pairs1_begin = perf_counter()
    # pairs1_end = perf_counter()
    # print(f"Time to create pairs1: {pairs1_end - pairs1_begin}")

def print_teams(teams: List[PlayerTeam]) -> None:
    for team_idx in range(0, len(teams)):
        team = teams[team_idx]
        print(f"Team {team_idx}: total birdie avg: {team.total_birdie_avg}")
        print(f"\ttotal cost: {team.total_cost}")
        print(f"\t{team.player1.name}")
        print(f"\t{team.player2.name}")
        print(f"\t{team.player3.name}")
        print(f"\t{team.player4.name}")

def print_player(player: Player) -> None:
    print(f"{player.name}, {player.cost}, {player.birdie_avg}")

def calculate_combos_cmd_line(raw_costs_filename: str, num_teams: int) -> None:
    players = []
    partial_players = read_players_from_file(raw_costs_filename, players)
    print("Players with missing data:")
    for player in partial_players:
        print(player.name)
    print("")
    calculate_combos(players, num_teams)

def read_players_from_file(filename: str, players: List[Player]) -> List[Player]:
    with open(filename) as file:
        reader = csv.reader(file, delimiter=',')
        _unused_header = next(reader)
        partial_players = []
        for row in reader:
            if row[0] and row[1] and row[2]:
                players.append(Player(row[0], float(row[1]), float(row[2])))
            elif row[0]:
                if row[1]:
                    partial_players.append(Player(name=row[0], cost=row[1], birdie_avg=None))
                else:
                    partial_players.append(Player(name=row[0], cost=None, birdie_avg=row[2]))
    return partial_players

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog="compute.py", description="Compute best teams for best ball fantasy golf.")
    parser.add_argument("costs_file")
    parser.add_argument("-n", "--num-teams", type=int, help="how many of the best teams are output")
    args = parser.parse_args()
    calculate_combos_cmd_line(args.costs_file, args.num_teams)