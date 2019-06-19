###############################################################################
# Functions to convert text copy/pasted from bb majors website into csv file
###############################################################################

import csv

# Assumes website player costs has been copy/pasted from bb majors website into
# a costs.txt file in local dir
def create_csv_from_website_text(raw_costs_filename, output_filename):
    with open(raw_costs_filename, "r") as raw_costs_file, open(output_filename, "w", newline='') as output_file:
    #with open(raw_costs_filename, "r") as raw_costs_file:
        writer = csv.writer(output_file, delimiter=',')
        writer.writerow(['Name', 'Cost'])
        for line in raw_costs_file:
            items = line.split()
            if len(items) >= 3:
                items[0] = items[0] + ' ' + items[1]
                items[1] = items[2]
            if len(items) >= 2:
                writer.writerow(items[0:2])

# if __name__ == "__main__":
# 	main()