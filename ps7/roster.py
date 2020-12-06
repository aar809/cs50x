from sys import argv, exit
import csv
import pandas as pd
from csv import reader
import re
from cs50 import SQL

if len(argv) != 2:
    print("Usage: python roster.py Gryffindor")
    exit(1)

house = argv[1]
# print(house)

db = SQL("sqlite:///students.db")
rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)
for i in rows:
    if i['middle'] == None:
        print(f"{i['first']} {i['last']}, born {i['birth']}")
    else:
        print(f"{i['first']} {i['middle']} {i['last']}, born {i['birth']}")