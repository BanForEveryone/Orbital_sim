
import pyvista as pv
import numpy as np
from math import sin, cos
raw_data = np.genfromtxt("results.txt", delimiter=";", names=True)

#create a second array, with x,y,z coordinates

new_data = np.zeros(shape=(5000000,3))


for index,item in enumerate(raw_data["HEIGHT"]):
    new_data[index][0] = raw_data["HEIGHT"][index] * sin(raw_data["THETA"][index]) #z
    new_data[index][1] = raw_data["HEIGHT"][index] * cos(raw_data["THETA"][index])*cos(raw_data["PHI"][index]) #y
    new_data[index][2] = raw_data["HEIGHT"][index] * sin(raw_data["PHI"][index]) * cos(raw_data["THETA"][index]) #x

plt = pv.Plotter()

plt.add_mesh(new_data[::1000])
plt.add_mesh(pv.Sphere(radius=6370e3))
plt.show()