# profile.py (from http://docs.cython.org/en/latest/src/tutorial/profiling_tutorial.html)

import pstats, cProfile

import compute

cProfile.runctx("compute.calculate_combos_cmd_line('C:/Users/kmfae/Documents/CS_Projects/bbmajors/BBMajorsCompute/ComputeEngine/Release/output.csv', 10)", globals(), locals(), "Profile.prof")

s = pstats.Stats("Profile.prof")
s.strip_dirs().sort_stats("time").print_stats()