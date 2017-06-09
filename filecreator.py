"""
Merges data from two sources: 
- Player cost data from the bb majors website (manually saved in csv format locally)
- Birdie stats from pgatour.com
    e.g. http://www.pgatour.com/stats/stat.352.html
Style guide: 
    -https://www.python.org/dev/peps/pep-0008/
Sources:
    -http://stackoverflow.com/questions/17126686/extracting-data-from-html-with-python
Usage:
    1. Create costs.csv from Joe's bb majors website (that has player costs)
    2. Verify STATS_URL is still valid for birdie percentage
    3. Run this python script from command line
        3a. Make sure script is in same directory as costs.csv
"""

import csv
import urllib2
import re
from BeautifulSoup import BeautifulSoup as bsoup

#Birdie Percentage Stat
STATS_URL = "http://www.pgatour.com/stats/stat.352.html"

def main():
    #costs_dict = {}
    with open("./costs.csv", "r") as costs_file:
        #read costs
        costs_dict = create_costs_dict_from_file(costs_file)
        #costs_name_list = create_key_list_from_dict(costs_dict)
        costs_name_list = sorted(costs_dict)

        #read birdie stats
        html = urllib2.urlopen(STATS_URL)
        #use BeautifulSoup to parse html
        soup = bsoup(html)

        '''
        print('')
        print('')
        print('Encoding: ' + soup.originalEncoding)
        '''

        player_rows = soup.findAll('tr', {"id" : re.compile("playerStatsRow(.*)")})
        
        stats_dict = create_stats_dict_from_html(player_rows)
        #stats_name_list = create_key_list_from_dict(stats_dict)
        stats_name_list = sorted(stats_dict)
        

        #search csv for player name. If found, append birdie avg to csv
        #for key in costs_dict.keys():
        #   print ("key: " + key + " value: " + costs_dict[key])
        print('')
        num_matches = calculate_num_matches(costs_name_list, stats_name_list)
        print(num_matches)

        #print_names_from_both_sources(costs_list, stats_list)
        

def create_costs_dict_from_file(costs_file):
    costs_dict = {}
    reader = csv.DictReader(costs_file)
    for row in reader:
        key = row.pop('Name')
        key = key.replace(".", "")
        if key in costs_dict:
            #duplicate row
            pass
        costs_dict[key] = row.pop("Cost")
    #print(costs_dict)
    return costs_dict

def create_key_list_from_dict(dict):
    key_list = []
    for key in dict:
        key_list.append(key)
    return key_list

def create_stats_dict_from_html(player_rows):
    stats_dict = {}
    for player_row in player_rows:
        cells = player_row.findAll('td')
        player_name = cells[2].text
        player_name = player_name.replace("&nbsp;", " ")
        player_name = player_name.replace(".", "")
        if player_name[-4:] == " III":
            player_name = player_name.replace(" III", "")
        birdie_pct_str = cells[4].text
        if player_name in stats_dict:
            #duplicate
            pass
        stats_dict[player_name] = birdie_pct_str
        #print(player_name)
    return stats_dict
        
def print_names_from_both_sources(costs_list, stats_list):
    costs_list.sort()
    stats_list.sort()
    while (stats_list and costs_list):
        if stats_list[0] == costs_list[0]:
            print(stats_list[0] + "\t\t" + costs_list[0])
            stats_list.pop(0)
            costs_list.pop(0)
        elif (stats_list[0] < costs_list[0]):
            print(stats_list[0])
            stats_list.pop(0)
        else:
            print("\t\t\t" + costs_list[0])
            costs_list.pop(0)

def calculate_num_matches(costs_list, stats_list):
    num_matches = 0
    costs_list.sort()
    stats_list.sort()
    while (stats_list and costs_list):
        if stats_list[0] == costs_list[0]:
            num_matches += 1
            stats_list.pop(0)
            costs_list.pop(0)
        elif (stats_list[0] < costs_list[0]):
            stats_list.pop(0)
        else:
            costs_list.pop(0)
    return num_matches

if __name__ == "__main__":
    main()