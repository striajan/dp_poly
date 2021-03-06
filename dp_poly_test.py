import numpy as np
import dp_poly as dpp
import matplotlib.pyplot as ppt

pts1 = np.array([[1,1],[3,1],[5,2],[6,3],[7,4],[8,6],[8,8]])
nvert1 = 3
vert1 = dpp.open(pts1, nvert1)

pts2 = np.array([[1,4],[2,2],[4,1],[6,1],[8,2],[9,4],[9,6],[8,8],[6,9],[4,9],[2,8],[1,6]])
nvert2 = 5
vert2 = dpp.close(pts2, nvert2)

pts3 = list()
f = file('points.txt', 'r')
while True:
    ln = f.readline()
    if len(ln) > 0:
        pts3.append([float(c) for c in ln.split()])
    else:
        break
pts3 = np.array(pts3)
nvert3 = 8
vert3 = dpp.close(pts3, nvert3)

print pts1
print vert1
print pts2
print vert2
print pts3
print vert3

ppt.figure(1)
ppt.plot(pts1[:,0], pts1[:,1])
ppt.plot(pts1[vert1,0], pts1[vert1,1])
ppt.figure(2)
ppt.plot(pts2[:,0], pts2[:,1])
ppt.plot(pts2[vert2,0], pts2[vert2,1])
ppt.figure(3)
ppt.plot(pts3[:,0], pts3[:,1])
ppt.plot(pts3[vert3,0], pts3[vert3,1])
ppt.show()
