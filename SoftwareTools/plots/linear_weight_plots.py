#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import math
import matplotlib.pyplot as plt
import numpy as np
import csv

# Specify the input files, the style of the marker, the color used for the lines and the label name.

triples = [('../data/saturnin-linear-weight-full.txt', 's-', 'b', 'Saturnin'),
           ('../data/skinny64-artificial-skinny384-linear-weight-full.txt', '<-', '#FF69B4', 'Skinny64-384'),
           ('../data/spongent-linear-weight-full.txt', 'X-', 'y', 'Spongent'),
           ('../data/xoodoo-linear-trail-partial.txt', 'o-', 'g', 'Xoodoo')]

# For every file, create two lists: one for the linear approximation weight and one for the number of masks.
# After this, open the input file, read this file, fill the two lists accordingly, make a list for the full
# linear approximation weights and then plot the cumulative correlation weight histograms.

for t in triples:
    linear_trail_weights = []
    number_of_trails = []

    with open(t[0], 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=',')
        for row in plots:
            linear_trail_weights.append(int(row[0]))
            number_of_trails.append(float(row[2]))

    missing_pairs = [(x, 0) for x in range(linear_trail_weights[0], linear_trail_weights[-1]+1) if x not in linear_trail_weights]
    full_weights = list(zip(linear_trail_weights, number_of_trails)) + missing_pairs
    full_weights.sort()
    linear_trail_weights, number_of_trails = list(zip(*full_weights))

    plt.plot(linear_trail_weights, np.log2(np.cumsum(number_of_trails)), t[1], label=t[3], color=t[2], drawstyle='steps-post', markersize=2)

# Set the axes and specify the labels of the axes.

plt.xticks(np.arange(0,36,5))
plt.xlim(0, 35)
plt.ylim(0, 80)
plt.xlabel('Linear Approximation Weight', fontsize=16)
plt.ylabel('Log2(Number of Linear Approximations)', fontsize=16)

# Set the legend and grid of the plot and save this to the file linear_weights.pdf

plt.legend(fontsize = 'small')
plt.grid(b=True, which='major')
plt.savefig('results/linear_weights.pdf', bbox_inches='tight')

