#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import csv
import argparse

# Specify this program needs an input file through the command line.
# Note that it is important to match the instance of Skinny belonging to the input file.
# If we have an input file of Skinny64 and give as second parameter "skinny128" this
# program does not provide correct tables.

parser = argparse.ArgumentParser()
parser.add_argument("filename", help="Input CSV file containing correlation.")
parser.add_argument("skinny64_or_skinny128", help="Instance of Skinny.")
args = parser.parse_args()

# Open the input file, read this file, and add it to a list accordingly.

with open(args.filename, 'r') as csvfile:
    data = csv.reader(csvfile, delimiter=',')
    input_data = []

    if args.skinny64_or_skinny128.lower() == "skinny64":
        divisor = 16
    elif args.skinny64_or_skinny128.lower() == "skinny128":
        divisor = 256
    else:
        print("No known instance of Skinny. Try \"skinny64\" or \"skinny128\".")
        exit()

    for row in data:
        if int(row[0]) != 0 and int(row[1]) != 0:
            input_data.append([int(row[0]) / divisor, int(row[1]), int(row[0])])

# Print the latex table.

print('\\begin{table}[H]')
print('\\caption[Short Heading]{}')
print('\\centering')
print('\\begin{tabular}{|c|c|c|}')
print('\\hline')
print('|Correlation| & Number of linear approximations & $|A-D|$ \\\\')
print('\\hline')
for entry in input_data:
    print('$' + str(entry[0]) + '$ & $' + str(entry[1]) + '$ & $' + str(entry[2]) + '$ \\\\')
print('\\hline')
print('\\end{tabular}')
print('\\label{tab:}')
print('\\end{table}')

