import math

from utilities import *

# Class Antenna
# Represents an Antenna
# - Coordinates
# - Radius
# - Enclosed points
class Antenna:
    # When an antenna is created, we first enclose only one point
    def __init__(self, point):
        self.center = point
        self.radius = 1
        self.points = []
        self.addPoint(point)

    def equals(self, antenna):
        return self.center == antenna.center and self.radius == antenna.radius and set(self.points) == set(antenna.points)

    # Adds a point to the antenna
    def addPoint(self, point):
        self.points.append(point)
        if (not isInside((self.center[0], self.center[1], self.radius), point)):
            x, y, self.radius = smallestEnclosingCircleInt(self.points)
            self.center = (x, y)

    # Cost of the antenna
    def cost(self, K, C):
        return K + C*((self.radius)**2)

    def show(self):
        print '\tAntenna :'
        print '\t\tCenter :', self.center 
        print '\t\tRadius :', self.radius
        print '\t\tPoints covered :', self.points 