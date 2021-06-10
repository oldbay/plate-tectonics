#!/usr/bin/python3

import platec
import numpy
from matplotlib import pyplot as plt
import matplotlib.animation as animation


seed = 3
width = 512
height = 512
sea_level = 0.65
erosion_period = 30
folding_ratio = 0.02
aggr_overlap_abs = 1000000
aggr_overlap_rel = 0.33
cycle_count = 6
num_plates = 6

p = platec.create(
    seed,
    width,
    height,
    sea_level,
    erosion_period,
    folding_ratio,
    aggr_overlap_abs,
    aggr_overlap_rel,
    cycle_count,
    num_plates,
)

def platec_iter():
    while platec.is_finished(p) == 0:
        platec.step(p)
        arr = numpy.array(platec.get_heightmap(p)).reshape(height, width)
        yield arr

fig = plt.figure()
im = plt.imshow(platec_iter().__next__())

def updatefig(*args):
    im.set_array(platec_iter().__next__())
    return [im]

ani = animation.FuncAnimation(fig, updatefig, interval=50, blit=True)

plt.colorbar()
plt.show()

platec.destroy(p)
