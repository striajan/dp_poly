import numpy as np
import dppoly as dpp

pts1 = np.array([[1,1],[3,1],[5,2],[6,3],[7,4],[8,6],[8,8]])
nvert1 = 3

print pts1
print 'open:', dpp.open(pts1, nvert1)
print 'close:', dpp.close(pts1, nvert1)

pts2 = np.array([[1,4],[2,2],[4,1],[6,1],[8,2],[9,4],[9,6],[8,8],[6,9],[4,9],[2,8],[1,6]])
nvert2 = 5

print pts2
print 'open:', dpp.open(pts2, nvert2)
print 'close:', dpp.close(pts2, nvert2)
