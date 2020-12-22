#! /usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
axe = fig.add_subplot(111, projection="3d")


pos = np.genfromtxt("positions-500.dat", comments="t")
# pos  = np.random.rand(4, 3)

axe.scatter(pos[:,0], pos[:,1], pos[:,2], s=4)

plt.show()
