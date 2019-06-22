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
            #Remove last item if it's '+' since these tend to be copy/pasted from bb majors site
            if items[-1] == '+':
                del items[-1]
            #Remove everything at end of line until numeric player cost is encountered
            while items and not items[-1].isnumeric():
                del items[-1]
            #Merge all names into single string, remove existing names from list and put full name in front
            full_name = " ".join(items[:-1])
            del items[:-1]
            items.insert(0, full_name)

            #write to file
            if len(items) >= 2:
                writer.writerow(items)

# if __name__ == "__main__":
# 	main()