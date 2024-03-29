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
from urllib.request import urlopen 
import re
from bs4 import BeautifulSoup as bsoup
from csvcreator import create_csv_from_website_text

#Birdie Percentage Stat
STATS_URL = "http://www.pgatour.com/stats/stat.352.html"

COSTS_INPUT_FILE = "./costs.txt"
COSTS_CSV_FILE = "./costs.csv"
OUTPUT_FILE = "output.csv"

def main():
    create_csv_from_website_text(COSTS_INPUT_FILE, COSTS_CSV_FILE)

    with open(COSTS_CSV_FILE, "r") as costs_file:
        #read costs
        costs_dict = create_costs_dict_from_file(costs_file)
        costs_name_list = sorted(costs_dict)

        #read birdie stats
        html = urlopen(STATS_URL)
        #use BeautifulSoup library to parse html
        soup = bsoup(html)
        player_rows = soup.findAll('tr', {"id" : re.compile("playerStatsRow(.*)")})
        
        stats_dict = create_stats_dict_from_html(player_rows)
        stats_name_list = sorted(stats_dict)
        
        print_total_num_matches(costs_name_list, stats_name_list)
        print_names_from_both_sources(costs_name_list, stats_name_list)

        output_dict = combine_costs_stats(costs_dict, stats_dict)
        create_output_csv(output_dict)
        

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

def create_stats_dict_from_html(player_rows):
    stats_dict = {}
    for player_row in player_rows:
        cells = player_row.findAll('td')
        player_name = cells[2].text
        player_name = player_name.replace("&nbsp;", " ")
        player_name = player_name.replace(".", "")
        player_name = player_name.replace("\n", "")
        if player_name[-4:] == " III":
            player_name = player_name.replace(" III", "")
        birdie_pct_str = cells[4].text
        if player_name in stats_dict:
            #duplicate
            pass
        stats_dict[player_name] = birdie_pct_str
        #print(player_name)
    return stats_dict
      
def combine_costs_stats(costs_dict, stats_dict):
    output_list = []
    for key in costs_dict:
        player_dict = {}
        player_dict['Name'] = str(key)
        player_dict['Cost'] = str(costs_dict[key])
        if key in stats_dict:
            player_dict['Birdie Avg'] = str(stats_dict[key])
        else:
            player_dict['Birdie Avg'] = ''
        output_list.append(player_dict)
    return output_list

def create_output_csv(player_list):
    with open(OUTPUT_FILE, 'w', newline='') as output_file:
        writer = csv.DictWriter(output_file, 
                                fieldnames=['Name', 'Cost', 'Birdie Avg'],
                                delimiter=',')
        writer.writeheader()
        for player in player_list:
            writer.writerow(player)


def print_total_num_matches(costs_name_list, stats_name_list):
    print('')
    num_matches = calculate_num_matches(costs_name_list, stats_name_list)
    print('--------------------------------------------------')
    print('Total number of matches: ' + str(num_matches))
    print('--------------------------------------------------')

#Assumptions: both lists are already sorted
def calculate_num_matches(costs_list, stats_list):
    num_matches = 0
    costs_list.sort()
    stats_list.sort()
    costs_index = 0
    stats_index = 0
    while (stats_index < len(stats_list) and costs_index < len(costs_list)):
        if stats_list[stats_index] == costs_list[costs_index]:
            num_matches += 1
            stats_index += 1
            costs_index += 1
        elif (stats_list[stats_index] < costs_list[costs_index]):
            stats_index += 1
        else:
            costs_index += 1
    return num_matches

#Assumptions: both lists are already sorted
def print_names_from_both_sources(costs_list, stats_list):
    #Print header row
    print('{0:22}{1}'.format(' From Stats' , ' From Costs'))
    print('{0:22}{1}'.format('============', '============'))

    costs_index = 0
    stats_index = 0
    #left_col_width = 22
    while (stats_index < len(stats_list) and costs_index < len(costs_list)):
        if stats_list[stats_index] == costs_list[costs_index]:
            print('{0:22}{1}'.format(stats_list[stats_index], costs_list[costs_index]))
            stats_index += 1
            costs_index += 1
        elif (stats_list[stats_index] < costs_list[costs_index]):
            print(stats_list[stats_index])
            stats_index += 1
        else:
            print('{0:22}{1:}'.format('', costs_list[costs_index]))
            costs_index += 1


if __name__ == "__main__":
    main()