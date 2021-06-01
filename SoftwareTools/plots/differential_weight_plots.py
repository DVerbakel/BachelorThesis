#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import math
import matplotlib.pyplot as plt
import numpy as np
import csv

# Specify the input files, the style of the marker, the color used for the lines and the label name.

triples = [('../data/saturnin-differential-full.txt', 's-', 'b', 'Saturnin'),
           ('../data/skinny64-artificial-skinny384-differential-full.txt', '<-', '#32CD32', 'Skinny64-384'),
           ('../data/spongent-differential-full.txt', 'X-', 'y', 'Spongent'),
           ('../data/xoodoo-differential-partial.txt', 'o-', 'g', 'Xoodoo')]

# For every file, create two lists: one for the differential weight and one for the number of differences.
# After this, open the input file, read this file, fill the two lists accordingly, make a list for the full
# differential weights and then plot the cumulative restriction weight histograms.

for t in triples:
    w = []
    c = []

    with open(t[0], 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=',')
        for row in plots:
            if int(row[1]) != 0:
                w.append(int(row[0]))
                c.append(float(row[1]))

    missing_pairs = [(x, 0) for x in range(w[0], w[-1]+1) if x not in w]
    full_weights = list(zip(w, c)) + missing_pairs
    full_weights.sort()
    w, c = list(zip(*full_weights))

    plt.plot(w, np.log2(np.cumsum(c)), t[1], label=t[3], color=t[2], drawstyle='steps-post', markersize=2)

# Set the axes and specify the labels of the axes.

plt.xticks(np.arange(0,36,5))
plt.xlim(0, 35)
plt.ylim(0, 80)
plt.xlabel('Differential Weight', fontsize=16)
plt.ylabel('Log2(Number of Differentials)', fontsize=16)

# Set the legend and grid of the plot and save this to the file differential_weights.pdf

plt.legend(fontsize = 'small')
plt.grid(b=True, which='major')
plt.savefig('results/differential_weights.pdf', bbox_inches='tight')

