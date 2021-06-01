![logo_bachelor_thesis](https://user-images.githubusercontent.com/77973924/119906067-c4cba700-bf4d-11eb-8367-50f00b4699a4.png)
# Influence of Design on Differential and Linear Propagation Properties of Block Cipher Family Skinny

In this bachelor thesis, the following research question will be answered:
*How do the linear and nonlinear layers in the round function of Skinny interact when it comes to the differential and linear propagation properties?*


## Espresso Algorithm
The folder EspressoAlgorithm holds the input files for the Espresso algorithm and the source code of this algorithm.

### espresso-logic-minimizer

A modern (2017) compiliable re-host of the [Espresso heuristic logic minimizer](https://en.wikipedia.org/wiki/Espresso_heuristic_logic_minimizer).
The original source code comes from the [University of California, Berkeley](https://embedded.eecs.berkeley.edu/pubs/downloads/espresso/index.htm).

### Install

```
$ cd espresso-src
$ make
```

The espresso executable will be located in the `bin` directory. Manual pages are available in the `man` directory. Copy these files to your desired location.
To run the espresso executable with our `skinny64.in` and `skinny128.in` files, these two files should be copied to the directory `bin`.

### Delete

```
$ cd espresso-src
$ make clean
```

This comment will delete the espresso executable and object files.

### Package Availability
This package is [available](https://aur.archlinux.org/packages/espresso-logic/) on the Arch User Repository.
If you would like to package it for your preferred distribution, you can submit a PR to have it listed here.

### License

This is published under the [MIT License](https://opensource.org/licenses/MIT).



## Software Tools
The folder SoftwareTools is based on [the code used for the paper Thinking Outside the Superbox](https://github.com/ongetekend/) written by Nicolas Bordes, Joan Daemen, Daniël Kuijsters and Gilles Van Assche.
In order to run our code we made some small changes to the file `global-common.c` and `global-common.h`.
Note that if my code will be run together with the original code, the following files will need to be changed (renaming of the function `box_weight` to `box_weight32`):
* `spongent-box-weight.c`
* `saturnin-differential-trail-weight-three-rounds.c`
* `saturnin-linear-trail-weight-three-rounds.c`
* `identity-box-weight.c`

Because of dependencies inside the SoftwareTools folder in the [original repository](https://github.com/ongetekend/), we needed to copy the following files as well (next to the modified `global_common.c` and `global_common.h` files):
* `convolution.c`
* `convolution.h`
* `csvparser.c`
* `csvparser.h`
* `table.c`
* `table.h`
* `table_fixed.c`
* `table_fixed.h`
* `walsh_transform.c`
* `walsh_transform.h`

Some CSV files from the [original `data` folder](https://github.com/ongetekend/) are copied inside our `data` folder. This is needed because of the comparison of Skinny against Rijndael, Saturnin, Spongent and Xoodoo in this bachelor thesis.

### Install

```
$ make && make install
```

The executables will be located in the `bin` directory. Running these will make CSV files inside the `data-skinny` directory.

### Delete

```
$ make clean
```

This comment will delete all binaries and object files.

### Prerequisite Libraries

In order to run this code, GMP and NTL are needed.

### Skinny64 Files

The following files are made for Skinny64 (the instance of Skinny having a block size of 64 bits):
* `skinny64-common.c`
  - Depencencies: the file `skinny64-common.h`
  - Input file(s): none
  - Output file(s): none
* `skinny64-common.h`
  - Depencencies: the file `global-common.h`
  - Input file(s): none
  - Output file(s): none
* `skinny64-correlation.c`
  - Depencencies: the files `skinny64-common.h`, `convolution.h` and `walsh-transform.h`
  - Input file(s): none
  - Output file(s): 
    - skinny64-correlation-superbox.txt
* `skinny64-differential-box-weight.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s): 
    - skinny64-differential-box-superbox.txt
    - skinny64-differential-box-full.txt
    - skinny64-artificial-skinny256-differential-box-full.txt
    - skinny64-artificial-skinny384-differential-box-full.txt
* `skinny64-differential-box-weight-2D.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-differential-box-superbox-2D.txt
* `skinny64-differential-clustering.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-differential-clustering-superbox.txt
    - skinny64-differential-clustering-full.txt
* `skinny64-differential-hamming-weight.c`
  - Depencencies: the files `skinny64-lookup-table.c`, `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-differential-hamming-weight.txt
    - skinny64-differential-hamming-weight-full.txt
    - skinny64-artificial-skinny256-differential-hamming-weight-full.txt
    - skinny64-artificial-skinny384-differential-hamming-weight-full.txt
* `skinny64-differential-hamming-weight-2D.c`
  - Depencencies: the files `skinny64-lookup-table.c`, `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-differential-hamming-weight-2D.txt
* `skinny64-differential-probability.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-differential-superbox.txt
    - skinny64-differential-full.txt
    - skinny64-artificial-skinny256-differential-full.txt
    - skinny64-artificial-skinny384-differential-full.txt
* `skinny64-differential-probability-unrounded.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-differential-superbox-unrounded.txt
* `skinny64-differential-trail-weight.c`
  - Depencencies: the files `skinny64-common.h`, `global-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-differential-trail-superbox.txt
    - skinny64-differential-trail-full.txt
    - skinny64-artificial-skinny256-differential-trail-full.txt
    - skinny64-artificial-skinny384-differential-trail-full.txt
* `skinny64-linear-box-weight.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-linear-box-superbox.txt
    - skinny64-linear-box-full.txt
    - skinny64-artificial-skinny256-linear-box-full.txt
    - skinny64-artificial-skinny384-linear-box-full.txt
* `skinny64-linear-box-weight-2D.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-linear-box-superbox-2D.txt
* `skinny64-linear-clustering.c`
  - Depencencies: the files `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-linear-clustering-superbox.txt
    - skinny64-linear-clustering-full.txt
* `skinny64-linear-hamming-weight.c`
  - Depencencies: the files `skinny64-lookup-table.c`, `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-linear-hamming-weight.txt
    - skinny64-linear-hamming-weight-full.txt
    - skinny64-artificial-skinny256-linear-hamming-weight-full.txt
    - skinny64-artificial-skinny384-linear-hamming-weight-full.txt
* `skinny64-linear-hamming-weight-2D.c`
  - Depencencies: the files `skinny64-lookup-table.c`, `skinny64-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-linear-hamming-weight-2D.txt
* `skinny64-linear-trail-weight.c`
  - Depencencies: the files `skinny64-common.h`, `global-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-linear-trail-superbox.txt
    - skinny64-linear-trail-full.txt
    - skinny64-artificial-skinny256-linear-trail-full.txt
    - skinny64-artificial-skinny384-linear-trail-full.txt
* `skinny64-lookup-table.c`
  - Depencencies: none
  - Input file(s): none
  - Output file(s): none
* `skinny64-parse-and-convolve.c`
  - Depencencies: the files `skinny64-common.h`, `convolution.h` and `csvparser.h`
  - Input file(s):
    - skinny64-linear-weight-superbox.txt
  - Output file(s):
    - skinny64-linear-weight-full.txt
    - skinny64-artificial-skinny256-linear-weight-full.txt
    - skinny64-artificial-skinny384-linear-weight-full.txt
* `skinny64-sbox-once`
  - Dependencies: the files `skinny64-common.h`, `convolution.h` and `walsh-transform.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-sbox-once.txt
* `skinny64-sbox-twice`
  - Dependencies: the files `skinny64-common.h`, `convolution.h` and `walsh-transform.h`
  - Input file(s): none
  - Output file(s):
    - skinny64-sbox-twice.txt

### Skinny128 Files

The following files are made for Skinny128 (the instance of Skinny having a block size of 128 bits):
* `skinny128-common.c`
  - Depencencies: the file `skinny128-common.h`
  - Input file(s): none
  - Output file(s): none
* `skinny128-common.h`
  - Depencencies: the file `global-common.h`
  - Input file(s): none
  - Output file(s): none
* `skinny128-differential-box-weight.c`
  - Depencencies: the files `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-differential-box-superbox.txt
    - skinny128-differential-box-full.txt
    - skinny128-artificial-skinny256-differential-box-full.txt
    - skinny128-artificial-skinny384-differential-box-full.txt
* `skinny128-differential-box-weight-2D.c`
  - Depencencies: the files `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s): 
    - skinny128-differential-box-superbox-2D.txt
* `skinny128-differential-clustering.c`
  - Depencencies: the files `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-differential-clustering-superbox.txt
    - skinny128-differential-clustering-full.txt
* `skinny128-differential-hamming-weight.c`
  - Depencencies: the files `skinny128-lookup-table.c`, `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-differential-hamming-weight.txt
    - skinny128-differential-hamming-weight-full.txt
    - skinny128-artificial-skinny256-differential-hamming-weight-full.txt
    - skinny128-artificial-skinny384-differential-hamming-weight-full.txt
* `skinny128-differential-hamming-weight-2D.c`
  - Depencencies: the files `skinny128-lookup-table.c`, `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-differential-hamming-weight-2D.txt
* `skinny128-linear-box-weight.c`
  - Depencencies: the files `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-linear-box-superbox.txt
    - skinny128-linear-box-full.txt
    - skinny128-artificial-skinny256-linear-box-full.txt
    - skinny128-artificial-skinny384-linear-box-full.txt
* `skinny128-linear-box-weight-2D.c`
  - Depencencies: the files `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-linear-box-superbox-2D.txt
* `skinny128-linear-clustering.c`
  - Depencencies: the files `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-linear-clustering-superbox.txt
    - skinny128-linear-clustering-full.txt
* `skinny128-linear-hamming-weight.c`
  - Depencencies: the files `skinny128-lookup-table.c`, `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-linear-hamming-weight.txt
    - skinny128-linear-hamming-weight-full.txt
    - skinny128-artificial-skinny256-linear-hamming-weight-full.txt
    - skinny128-artificial-skinny384-linear-hamming-weight-full.txt
* `skinny128-linear-hamming-weight-2D.c`
  - Depencencies: the files `skinny128-lookup-table.c`, `skinny128-common.h` and `convolution.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-linear-hamming-weight-2D.txt
* `skinny128-lookup-table.c`
  - Depencencies: none
  - Input file(s): none
  - Output file(s): none
* `skinny128-sbox-once`
  - Dependencies: the files `skinny128-common.h`, `convolution.h` and `walsh-transform.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-sbox-once.txt
* `skinny128-sbox-twice`
  - Dependencies: the files `skinny128-common.h`, `convolution.h` and `walsh-transform.h`
  - Input file(s): none
  - Output file(s):
    - skinny128-sbox-twice.txt

### Conversion Files

Some of the output files need to be post-processed in order to give the correct results. The programs we use to post-process these files are:
* `box_partition_to_latex_table.py`
  - Depencencies: the imports `csv` and `argparse`
  - Input file(s): the file given as command line argument
  - Output file(s): none
* `linear_weight_conversion.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - skinny64-correlation-superbox.txt
  - Output file(s):
    - skinny64-linear-weight-superbox.txt
* `sbox_correlation_to_latex_table.py`
  - Depencencies: the imports `csv` and `argparse`
  - Input file(s): the file given as command line argument
  - Output file(s): none

### Plot Files

We use the following Python files to visualize our results:
* `2D_histogram_differential_bit_weight_skinny64.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny64-differential-hamming-weight-2D.txt
  - Output file(s):
    - 2D-differential-bit-weight-skinny64.png
* `2D_histogram_differential_bit_weight_skinny128.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny128-differential-hamming-weight-2D.txt
  - Output file(s):
    - 2D-differential-bit-weight-skinny128.png
* `2D_histogram_differential_box_weight_skinny64.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny64-differential-box-superbox-2D.txt
  - Output file(s):
    - 2D-differential-box-weight-skinny64.png
* `2D_histogram_differential_box_weight_skinny128.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny128-differential-box-superbox-2D.txt
  - Output file(s):
    - 2D-differential-box-weight-skinny128.png
* `2D_histogram_linear_bit_weight_skinny64.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny64-linear-hamming-weight-2D.txt
  - Output file(s):
    - 2D-linear-bit-weight-skinny64.png
* `2D_histogram_linear_bit_weight_skinny128.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny128-linear-hamming-weight-2D.txt
  - Output file(s):
    - 2D-linear-bit-weight-skinny128.png
* `2D_histogram_linear_box_weight_skinny64.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny64-linear-box-superbox-2D.txt
  - Output file(s):
    - 2D-linear-box-weight-skinny64.png
* `2D_histogram_linear_box_weight_skinny128.py`
  - Depencencies: the imports `Axes3D`, `matplotlib.pyplot`, `numpy`, `csv` and `cm`
  - Input file(s):
    - skinny128-linear-box-superbox-2D.txt
  - Output file(s):
    - 2D-linear-box-weight-skinny128.png
* `bit_weight_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - aes-hamming-full.txt
    - saturnin-hamming-full.txt
    - skinny64-artificial-skinny384-differential-hamming-weight-full.txt
    - skinny64-artificial-skinny384-linear-hamming-weight-full.txt
    - skinny128-artificial-skinny384-differential-hamming-weight-full.txt
    - skinny128-artificial-skinny384-linear-hamming-weight-full.txt
    - spongent-hamming-full.txt
    - xoodoo-hamming-partial.txt
    - identity-hamming.full.txt
  - Output file(s):
    - bit_weights.pdf
* `bit_weight_plots_only_skinny.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - skinny64-differential-hamming-weight-full.txt
    - skinny64-linear-hamming-weight-full.txt
    - skinny64-artificial-skinny384-differential-hamming-weight-full.txt
    - skinny64-artificial-skinny384-linear-hamming-weight-full.txt
    - skinny128-differential-hamming-weight-full.txt
    - skinny128-linear-hamming-weight-full.txt
    - skinny128-artificial-skinny384-differential-hamming-weight-full.txt
    - skinny128-artificial-skinny384-linear-hamming-weight-full.txt
    - identity-hamming.full.txt
  - Output file(s):
    - bit\_weights\_only_skinny.pdf
* `bit_weight_superbox_plots.py`
  - Dependencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - aes-hamming-superbox.txt
    - saturnin-hamming-superbox.txt
    - skinny64-differential-hamming-weight.txt
    - skinny64-linear-hamming-weight.txt
    - skinny128-differential-hamming-weight.txt
    - skinny128-linear-hamming-weight.txt
  - Output file(s):
    - bit\_weights_superbox.pdf
* `bit_weight_superbox_plots_only_skinny.py`
  - Dependencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - skinny64-differential-hamming-weight.txt
    - skinny64-linear-hamming-weight.txt
    - skinny128-differential-hamming-weight.txt
    - skinny128-linear-hamming-weight.txt
  - Output file(s):
    - bit\_weights\_superbox\_only_skinny.pdf
* `box_weight_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - aes-box-full.txt
    - saturnin-box-full.txt
    - skinny64-artificial-skinny384-differential-box-full.txt
    - skinny64-artificial-skinny384-linear-box-full.txt
    - skinny128-artificial-skinny384-differential-box-full.txt
    - skinny128-artificial-skinny384-linear-box-full.txt
    - spongent-box-full.txt
    - xoodoo-box-partial.txt
    - identity-box-full.txt
  - Output file(s):
    - box_weights.pdf
* `box_weight_plots_comparison.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s): 
    - aes-box-full.txt
    - saturnin-box-full.txt
    - skinny64-artificial-skinny384-differential-box-full.txt
    - skinny64-artificial-skinny384-linear-box-full.txt
    - skinny128-artificial-skinny384-differential-box-full.txt
    - skinny128-artificial-skinny384-linear-box-full.txt
    - spongent-box-full.txt
    - xoodoo-box-partial.txt
  - Output file(s): 
    - box\_weights_comparison.pdf
* `box_weight_plots_only_skinny.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - skinny64-differential-box-full.txt
    - skinny64-linear-box-full.txt
    - skinny64-artificial-skinny384-differential-box-full.txt
    - skinny64-artificial-skinny384-linear-box-full.txt
    - skinny128-differential-box-full.txt
    - skinny128-linear-box-full.txt
    - skinny128-artificial-skinny384-differential-box-full.txt
    - skinny128-artificial-skinny384-linear-box-full.txt
    - identity-box-full.txt
  - Output file(s): 
    - box\_weights\_only_skinny.pdf
* `box_weight_superbox_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - aes-box-superbox.txt
    - saturnin-box-superbox.txt
    - skinny64-differential-box-superbox.txt
    - skinny64-linear-box-superbox.txt
    - skinny128-differential-box-superbox.txt
    - skinny128-linear-box-superbox.txt
    - spongent-box-superbox.txt
    - identity-box-superbox.txt
  - Output file(s): 
    - box\_weights_superbox.pdf
* `box_weight_superbox_plots_only_skinny.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - skinny64-differential-box-superbox.txt
    - skinny64-linear-box-superbox.txt
    - skinny128-differential-box-superbox.txt
    - skinny128-linear-box-superbox.txt
    - identity-box-superbox.txt
  - Output file(s):
    - box\_weights\_superbox\_only_skinny.pdf
* `differential_trail_weight_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - aes-differential-trail-full.txt
    - saturnin-differential-trail-full.txt
    - skinny64-artificial-skinny384-differential-trail-full.txt
    - spongent-differential-trail-full.txt
    - xoodoo-differential-trail-partial.txt
  - Output file(s):
    - differential\_trail_weights.pdf
* `differential_trail_weight_plots_comparison.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - saturnin-differential-trail-full.txt
    - skinny64-artificial-skinny384-differential-trail-full.txt
    - spongent-differential-trail-full.txt
    - xoodoo-differential-trail-partial.txt
  - Output file(s):
    - differential\_trail\_weights_comparison.pdf
* `differential_trail_weight_superbox_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - aes-differential-trail-superbox.txt
    - saturnin-differential-trail-superbox.txt
    - skinny64-differential-trail-superbox.txt
    - spongent-differential-trail-superbox.txt
  - Output file(s): 
    - differential\_trail\_weights_superbox.pdf
* `differential_unrounded_plots_skinny64.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - skinny64-differential-superbox-unrounded.txt
    - skinny64-differential-trail-superbox.txt
  - Output file(s):
    - differential\_skinny64\_superbox_unrounded.pdf
* `differential_weight_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - saturnin-differential-full.txt
    - skinny64-artificial-skinny384-differential-full.txt
    - spongent-differential-full.txt
    - xoodoo-differential-partial.txt
  - Output file(s):
    - differential_weights.pdf
* `differential_weight_superbox_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - saturnin-differential-superbox.txt
    - skinny64-differential-superbox.txt
    - spongent-differential-superbox.txt
  - Output file(s):
    - differential\_weights_superbox.pdf
* `linear_trail_weight_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s): 
    - aes-linear-trail-full.txt
    - saturnin-linear-trail-full.txt
    - skinny64-artificial-skinny384-linear-trail-full.txt
    - spongent-linear-trail-full.txt
    - xoodoo-linear-trail-partial.txt
  - Output file(s):
    - linear\_trail_weights.pdf
* `linear_trail_weight_plots_comparison.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - saturnin-linear-trail-full.txt
    - skinny64-artificial-skinny384-linear-trail-full.txt
    - spongent-linear-trail-full.txt
    - xoodoo-linear-trail-partial.txt
  - Output file(s): 
    - linear\_trail\_weights_comparison.pdf
* `linear_trail_weight_superbox_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s):
    - aes-linear-trail-superbox.txt
    - saturnin-linear-trail-superbox.txt
    - skinny64-linear-trail-superbox.txt
    - spongent-linear-trail-superbox.txt
  - Output file(s):
    - linear\_trail\_weights_superbox.pdf
* `linear_weight_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s): 
    - saturnin-linear-weight-full.txt
    - skinny64-artificial-skinny384-linear-weight-full.txt
    - spongent-linear-weight-full.txt
    - xoodoo-linear-trail-partial.txt
  - Output file(s): 
    - linear_weights.pdf
* `linear_weight_superbox_plots.py`
  - Depencencies: the imports `math`, `matplotlib.pyplot`, `numpy` and `csv`
  - Input file(s): 
    - saturnin-linear-weight-superbox.txt
    - skinny64-linear-weight-superbox.txt
    - spongent-linear-weight-superbox.txt
  - Output file(s): 
    - linear\_weights_superbox.pdf
* `relation_branch_number_and_round_cost.r`
  - Depencencies: None
  - Input file(s): None
  - Output file(s): 
    - relation\_branch\_number\_and\_round_cost.png

