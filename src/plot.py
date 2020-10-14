import matplotlib.pyplot as plt
import numpy as np


def plot(xmin, xmax, zmin, zmax,numpoints, data):
    x = np.linspace(xmin, xmax, numpoints);
    z = np.linspace(zmin, zmax, numpoints);
    plt.figure();
    plt.contourf(x,z,data);
    plt.show();
plot(-3e-4,3e-4, -3e-4, 3e-4, 5, np.ones((5,5)))
