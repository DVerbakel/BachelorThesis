#!/usr/bin/env python3
# Written by Denise Verbakel

# Specify the needed imports for this program.

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import csv
from matplotlib import cm

# Specify the input data and three empty lists: one for the input linear bit weight, one for 
# the output linear bit weight and one for the number of masks.

input_file = '../data/skinny64-linear-hamming-weight-2D.txt'
input_weight = []
output_weight = []
count = []

# Open the input file, read this file, and fill the three lists accordingly.

with open(input_file, 'r') as csvfile:
    rows = csv.reader(csvfile, delimiter=',')
    for row in rows:
        if int(row[2]) != 0:
            input_weight.append(int(row[0]))
            output_weight.append(int(row[1]))
            count.append(float(row[2]))

# Make a figure, set the three axes and specify the labels of the axes.

fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')
ax.set_xlabel('Input Linear Bit Weight')
ax.invert_xaxis()
ax.set_ylabel('Output Linear Bit Weight')
ax.set_zlabel('Number of Pairs')
ax.set_zticks([0,1,2]) #do not show decimal numbers on the z-axis

# Center the data points to the middle of a bar of the histogram.

x = [weight - 0.5 for weight in input_weight]
y = [weight - 0.5 for weight in output_weight]
hist, xedges, yedges = np.histogram2d(x,y)

# Specify a color scheme for the two-dimensional histograms.

cmap = cm.get_cmap('Blues')
cmap = cmap.reversed()
max_height = np.max(count)
min_height = np.min(count)
rgba = [cmap((k-min_height)/max_height) for k in count]

# Build the two-dimensional histogram.

ax.bar3d(x, y, 0, 1, 1, count, color=rgba, zsort='average')

# Set the title of the plot and save this to the file 2D-linear-bit-weight-skinny64.png

plt.title('Skinny64')
plt.savefig('results/2D-linear-bit-weight-skinny64.png', bbox_inches='tight')

