
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

import numpy as np

### function which returns a 3D plot when given a data file
### in appropriate format. Assumed format:
###                            plot title
                               # x-label
                               # y-label
                               # z-label
                               # x-values y-values z(x, y_1) z(x, y_2)...

def ThreeDPlot(filename):
    with open(filename) as h:
        plotTitle=h.readline()
        xlabel=h.readline()         # eats lines
        ylabel=h.readline()
        zlabel=h.readline()
        n_cols = len(h.readline().split("\t"))
    
    x=np.loadtxt(filename, delimiter='\t', unpack=True, skiprows=4, usecols=0)
    y=np.loadtxt(filename, delimiter='\t', unpack=True, skiprows=4, usecols=1)
    Z=np.loadtxt(filename, delimiter='\t', unpack=True, skiprows=4, usecols=np.arange(2,n_cols))
        
    X, Y=np.meshgrid(x, y)
    fig = plt.figure(figsize=(8,6))
    ax = plt.axes(projection='3d')
    ax.plot_surface(X, Y, Z)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.set_zlabel(zlabel)
    plt.title(plotTitle)

ThreeDPlot("dataBSCallTAndS.txt")
ThreeDPlot("dataBSCallTAndK.txt")
ThreeDPlot("dataBSCallTAndV.txt")

ThreeDPlot("dataBSDigitalCallTAndS.txt")
ThreeDPlot("dataBSDigitalCallTAndK.txt")
ThreeDPlot("dataBSDigitalCallTAndV.txt")