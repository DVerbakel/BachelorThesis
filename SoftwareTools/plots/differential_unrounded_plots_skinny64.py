#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import math
import matplotlib.pyplot as plt
import numpy as np
import csv

# Specify the input files, the style of the marker, the color used for the lines and the label name.

triples = [('../data/skinny64-differential-superbox-unrounded.txt', '-', 'r', 'Differentials'), 
	   ('../data/skinny64-differential-trail-superbox.txt', '-', 'b', 'Differential Trails')]

# For the first file, create two lists: one for the differential weight and one for the number of differentials.
# After this, open the input file, read this file, fill the two lists accordingly, make a list for the full
# differential weight and then plot the differentials in the superbox of Skinny64.

w = []
c = []
with open(triples[0][0], 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        if int(row[1]) != 0 and int(row[0]) != 2**16:
            w.append((2**16) / float(row[0]))
            c.append(float(row[1]))
    pairs = list(zip(w, c))
    pairs.sort()
    w, c = list(zip(*pairs))
    plt.plot(np.log2(w), np.log2(np.cumsum(c)), triples[0][1], label=triples[0][3], color=triples[0][2], drawstyle='steps-post', markersize=2)

# For the second file, create two lists: one for the differential trail weight and one for the number of differences.
# After this, open the input file, read this file, fill the two lists accordingly, make a list for the full
# differential trail weight and then plot the differential trails in the superbox of Skinny64.

w = []
c = []
with open(triples[1][0], 'r') as csvfile:
    rows = csv.reader(csvfile, delimiter=',')
    for row in rows:
        if int(row[0]) != 0 and int(row[2]) != 0:
            w.append(int(row[0]))
            c.append(float(row[2]))
    missing_pairs = [(x, 0) for x in range(w[0], w[-1]+1) if x not in w]
    full_weights = list(zip(w, c)) + missing_pairs
    full_weights.sort()
    w, c = list(zip(*full_weights))
    plt.plot(w, np.log2(np.cumsum(c)), triples[1][1], color=triples[1][2], label=triples[1][3], drawstyle='steps-post', markersize=2)

# Set the axes and specify the labels of the axes.

plt.xticks(np.arange(0,24,2))
plt.xlim(0, 24)
plt.ylim(0, 40)
plt.xlabel('Weight', fontsize=16)
plt.ylabel('Log2(Weight Count)', fontsize=16)

# Set the legend and grid of the plot and save this to the file differential_skinny64_superbox_unrounded.pdf

plt.legend(loc='upper left', fontsize = 'small')
plt.title('Skinny64')
plt.grid(b=True, which='major')
plt.savefig('results/differential_skinny64_superbox_unrounded.pdf', bbox_inches='tight')

