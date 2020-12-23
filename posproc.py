#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

rS = 0
rE = 1000
rr = 50

fig = plt.figure()
axe = fig.add_subplot(111, projection="3d")

# field = "velocities"
field = "positions"
pos = []
for i in range(rS, rE, rr):
    p = np.genfromtxt("./data/{}-{}.csv".format(field,i), comments="t", delimiter=",", skip_header=1)
    pos.append(p)

data = pos

xmax,ymax,zmax = np.max(np.max(data, axis=1), axis=0)
xmin,ymin,zmin = np.min(np.min(data, axis=1), axis=0)

def anim_scats(iters, data, scat):
    # for i in range(data[0].shape[0]):
        # scats[i]._offsets3d = (data[iters][i,0], data[iters][i,1], data[iters][i,2])
    scat = axe.scatter(data[iters][:,0], data[iters][:,1], data[iters][:,2], s=0.02, c="blue")
    return scat

# def update_pos(i):
    # axe.scatter(pos[i][:,0], pos[i][:,1], pos[i][:,2], s=4)
    # return axe

# pos = np.genfromtxt("positions-500.dat", comments="t"
# pos  = np.random.rand(4, 3)

# axe.scatter(pos[10][:,0], pos[10][:,1], pos[10][:,2], s=4)
# scats = [axe.scatter(data[0][i,0], data[0][i,1], data[0][i,2]) for i in range(data[0].shape[0])]

scat = axe.scatter(data[0][:,0], data[0][:,1], data[0][:,2], s=2, c="blue")

axe.set_xlim3d(xmin, xmax)
axe.set_ylim3d(ymin, ymax)
axe.set_zlim3d(zmin, zmax)

ani = animation.FuncAnimation(fig, anim_scats, len(data), fargs=(data, scat), interval=50)

plt.show()
