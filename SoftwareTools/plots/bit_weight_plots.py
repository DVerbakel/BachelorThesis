#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

import math
import matplotlib.pyplot as plt
import numpy as np
import csv

# Specify the input files, the style of the marker, the color used for the lines and the label name.

triples = [('../data/aes-hamming-full.txt', 'D-', 'r', 'Rijndael'),
           ('../data/saturnin-hamming-full.txt', 's-', 'b', 'Saturnin'),
           ('../data/skinny64-artificial-skinny384-differential-hamming-weight-full.txt', '<-', '#32CD32', 'Skinny64-384-dif'),
           ('../data/skinny64-artificial-skinny384-linear-hamming-weight-full.txt', '<-', '#FF69B4', 'Skinny64-384-lin'),
           ('../data/skinny128-artificial-skinny384-differential-hamming-weight-full.txt', '>-', '#9400D3', 'Skinny128-384-dif'),
           ('../data/skinny128-artificial-skinny384-linear-hamming-weight-full.txt', '>-', '#87CEFA', 'Skinny128-384-lin'),
           ('../data/spongent-hamming-full.txt', 'X-', 'y', 'Spongent'),
           ('../data/xoodoo-hamming-partial.txt', 'o-', 'g', 'Xoodoo'),
           ('../data/identity-hamming.full.txt', '*-', 'k', 'Identity')]

# For every file, create two lists: one for the bit weight and one for the number of differences/masks.
# After this, open the input file, read this file, fill the two lists accordingly, make a list for the
# full bit weights and then plot the cumulative bit weight histograms.

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

plt.xticks(np.arange(0,27,2))
plt.xlim(0, 26)
plt.ylim(0, 80)
plt.xlabel('Bit Weight', fontsize=16)
plt.ylabel('Log2(Number of States)', fontsize=16)

# Set the legend and grid of the plot and save this to the file bit_weights.pdf

plt.legend(fontsize = 'small')
plt.grid(b=True, which='major')
plt.savefig('results/bit_weights.pdf', bbox_inches='tight')

