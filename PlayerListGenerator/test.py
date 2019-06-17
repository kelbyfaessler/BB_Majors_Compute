import csv

def main():
	costsdict = {}
	with open("./costs.csv", "r") as costsfile:
		#read costs
		costslist = []
		reader = csv.DictReader(costsfile)
		for row in reader:
			key = row.pop('Name')
			#print(row)
			
			key = key.replace(".", "")
			if key in costsdict:
				#duplicate row
				pass
			costsdict[key] = row.pop("Cost")
			costslist.append(key)
			
			'''
			'''
		print(costsdict)
		#print(costslist)

if __name__ == "__main__":
	main()