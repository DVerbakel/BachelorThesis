#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import math
import matplotlib.pyplot as plt
import numpy as np
import csv

# Specify the input files, the style of the marker, the color used for the lines and the label name.

triples = [('../data/saturnin-linear-weight-superbox.txt', 's-', 'b', 'Saturnin'),
           ('../data/skinny64-linear-weight-superbox.txt', '<-', '#FF69B4', 'Skinny64'),
           ('../data/spongent-linear-weight-superbox.txt', 'X-', 'y', 'Spongent')]

# For every file, create two lists: one for the linear approximation weight and one for the number of masks.
# After this, open the input file, read this file, fill the two lists accordingly, make a list for the full
# linear approximation weights and then plot the cumulative correlation weight histograms of the superboxes.

for t in triples:
    linear_trail_weights = []
    number_of_trails = []

    with open(t[0], 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=',')
        for row in plots:
            linear_trail_weights.append(int(row[0]))
            number_of_trails.append(float(row[1]))

    missing_pairs = [(x, 0) for x in range(linear_trail_weights[0], linear_trail_weights[-1]+1) if x not in linear_trail_weights]
    full_weights = list(zip(linear_trail_weights, number_of_trails)) + missing_pairs
    full_weights.sort()
    linear_trail_weights, number_of_trails = list(zip(*full_weights))

    plt.plot(linear_trail_weights, np.log2(np.cumsum(number_of_trails)), t[1], label=t[3], color=t[2], drawstyle='steps-post', markersize=2)

# Set the axes and specify the labels of the axes.

plt.xticks(np.arange(0,22,2))
plt.xlim(0, 21)
plt.ylim(0, 35)
plt.xlabel('Linear Approximation Weight Superbox', fontsize=16)
plt.ylabel('Log2(Number of Linear Approximations)', fontsize=16)

# Set the legend and grid of the plot and save this to the file linear_weights_superbox.pdf

plt.legend(fontsize = 'small')
plt.grid(b=True, which='major')
plt.savefig('results/linear_weights_superbox.pdf', bbox_inches='tight')

