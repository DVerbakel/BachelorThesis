#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import csv
import argparse

# Specify this program needs an input file through the command line.

parser = argparse.ArgumentParser()
parser.add_argument("filename", help="Input CSV file containing partition.")
args = parser.parse_args()

# Open the input file, read this file, and add it to a dictionary accordingly.

with open(args.filename, 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    dict = {}
    for row in plots:
        if row[0] in dict:
            dict[row[0]].append("(%s x %s)" % (row[2], row[1]))
        else:
            dict[row[0]] = ["(%s x %s)" % (row[2], row[1])]

# Print the latex table.

print('\\begin{table}[H]')
print('\\caption[Short Heading]{}')
print('\\centering')
print('\\begin{tabular}{|l|l|}')
print('\\hline')
print('$\weightcurly$ & \# $N \\times C$ \\\\')
print('\\hline')
for key, value_list in dict.items():
    if key != '0':
        print('$' + key + '$' + ' &')
        for value in value_list:
            print('$' + value + '$')
        print('\\\\')
print('\\hline')
print('\\end{tabular}')
print('\\label{tab:}')
print('\\end{table}')
