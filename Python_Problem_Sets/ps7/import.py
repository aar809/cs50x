from sys import argv, exit
import csv
import pandas as pd
from csv import reader
import re
from cs50 import SQL

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

file = argv[1]
# print(file)

db = SQL("sqlite:///students.db")

with open(file, "r") as file:
    reader = csv.DictReader(file)
    # row_count = sum(1 for row in reader)
    # print(row_count)
    for row in reader:
        # print(row)
        # df.append(row)
        name = row["name"].split()
        # print(len(name))
        house = row["house"]
        birth = row["birth"]

        if len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]
            # print(first)
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       first, middle, last, house, birth)
        else:
            first = name[0]
            last = name[1]
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, NULL, ?, ?, ?)",
                       first, last, house, birth)

