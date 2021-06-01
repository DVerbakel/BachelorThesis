#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import math
import matplotlib.pyplot as plt
import numpy as np
import csv

# Specify the input files, the style of the marker, the color used for the lines and the label name.

triples = [('../data/aes-box-superbox.txt', 'D-', 'r', 'Rijndael'),
           ('../data/saturnin-box-superbox.txt', 's-', 'b', 'Saturnin'),
           ('../data/skinny64-differential-box-superbox.txt', '<-', '#32CD32', 'Skinny64-dif'),
           ('../data/skinny64-linear-box-superbox.txt', '<-', '#FF69B4', 'Skinny64-lin'),
           ('../data/skinny128-differential-box-superbox.txt', '>-', '#9400D3', 'Skinny128-dif'),
           ('../data/skinny128-linear-box-superbox.txt', '>-', '#87CEFA', 'Skinny128-lin'),
           ('../data/spongent-box-superbox.txt', 'X-', 'y', 'Spongent'),
           ('../data/identity-box-superbox.txt', '*-', 'k', 'Identity (4-bit boxes)')]

# For every file, create two lists: one for the box weight and one for the number of differences/masks.
# After this, open the input file, read this file, fill the two lists accordingly, make a list for the
# full box weights and then plot the cumulative box weight histograms of the superboxes.

for t in triples:
    w = []
    c = []

    with open(t[0], 'r') as csvfile:
        rows = csv.reader(csvfile, delimiter=',')
        for row in rows:
            if int(row[2]) != 0:
                w.append(int(row[0]))
                c.append(float(row[2]))

    missing_pairs = [(x, 0) for x in range(w[0], w[-1]+1) if x not in w]
    full_weights = list(zip(w, c)) + missing_pairs
    full_weights.sort()
    w, c = list(zip(*full_weights))

    plt.plot(w, np.log2(np.cumsum(c)), t[1], label=t[3], color=t[2], drawstyle='steps-post', markersize=2)

# Set the axes and specify the labels of the axes.

plt.xticks(np.arange(0,10,1))
plt.xlim(0, 9)
plt.ylim(0, 35)
plt.xlabel('Box Weight Superbox', fontsize=16)
plt.ylabel('Log2(Number of States)', fontsize=16)

# Set the legend and grid of the plot and save this to the file box_weights_superbox.pdf

plt.legend()
plt.grid(b=True, which='major')
plt.savefig('results/box_weights_superbox.pdf', bbox_inches='tight')

