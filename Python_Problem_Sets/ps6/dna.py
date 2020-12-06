from cs50 import get_int
from cs50 import get_float
from cs50 import get_string
from sys import argv, exit
import csv
import pandas as pd
from csv import reader
import re

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

data = argv[1]
sequence = argv[2]

with open(data, 'r') as read_obj:
    csv_reader = reader(read_obj)
    STR = next(csv_reader)
    # # Check file as empty
    # if STR != None:
    #     # Iterate over each row after the header in the csv
    #     for row in csv_reader:
    #         # row variable is a list that represents a row in csv
    #         print(row)

STR.remove('name')
# print(STR)

file = open(sequence, "r")
sequence = file.read()
file.close()
# print(sequence)

match_count = {}
for i in range(len(STR)):
    substr = STR[i]
    # substr = "AGATC"
    max_substr_count = 0
    groups = re.findall(r'(?:' + re.escape(substr) + r')+', sequence)
    # print(groups)
    if len(groups) == 0:
        largest = 0
    else:
        largest = max(groups, key=len)
        # print(len(largest) // len(substr))
        max_substr_count = (len(largest) / len(substr))
    match_count[STR[i]] = max_substr_count
# print(match_count)

DNA_match = {}

with open(data, 'r') as read_obj:
    csv_reader = reader(read_obj)
    STR = next(csv_reader)
    # Check file as empty
    if STR != None:
        # Iterate over each row after the header in the csv
        for row in csv_reader:
            DNA_match[row[0]] = 0
            # row variable is a list that represents a row in csv
            for i in range(1, len(row)):
                # print(row[i])
                # print(match_count[STR[i]])
                if int(row[i]) != int(match_count[STR[i]]):
                    # print(f"{row[0]} doesn't match")
                    break
                else:
                    # print(f"{row[0]} matched {i} of {len(STR)-1}")
                    DNA_match[row[0]] += 1
# print(DNA_match)

for i in DNA_match:
    if DNA_match[i] == len(STR)-1:
        print(i)
        exit()
print("No match")