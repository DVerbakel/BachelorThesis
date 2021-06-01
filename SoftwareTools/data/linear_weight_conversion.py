#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import math
import matplotlib.pyplot as plt
import numpy as np
import csv

# Specify the input data and two empty lists: one for the linear approximation weight and one for 
# the number of linear approximations.

input_file = ['../data/skinny64-correlation-superbox.txt', 32, '../data/skinny64-linear-weight-superbox.txt']
w = []
c = []

# Open the input file, read this file, and fill the two lists accordingly.

with open(input_file[0], 'r') as csvfile:
    rows = csv.reader(csvfile, delimiter=',')
    for row in rows:
        if int(row[0]) != 0 and int(row[1]) != 0:
            w.append(input_file[1] - np.log2(float(row[0])**2))
            c.append(int(row[1]))

# Round the linear approximation weight and reverse both lists.

w = [int(round(x)) for x in w]
w.reverse()
c.reverse()

# Order the output data, so the (w,c) pairs, by increasing value of w and also by increasing value of c.

weight = 0
ordered_c = []
temp_c = []

for i in range(0,len(w)):
    if w[i] != weight:
        weight = w[i]
        ordered_c.append(temp_c)
        temp_c = []
    temp_c.append(c[i])

ordered_c.append(temp_c)
ordered_c = [sorted(x) for x in ordered_c]
ordered_c = [item for sublist in ordered_c for item in sublist]

output_data = list(zip(w,ordered_c))

# Write the output data to the file skinny64-linear-weight-superbox.txt and close the input file.
# Data: (linear approximation weight, number of linear approximations)
f = open(input_file[2], 'w')
for entry in output_data:
    final_entry = str(entry)
    final_entry = final_entry[1:len(final_entry)-1]
    final_entry = final_entry.replace(' ', '') + '\n'
    f.write(final_entry)
f.close()

