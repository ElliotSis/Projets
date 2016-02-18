import math
import random

#############
# Utilities #
#############

random.seed()

# NOTES : 
# - A point is pair of floats
# - A circle is a triplets of float (coordinates of center and radius)

# Epsilon for float calculations
_EPSILON = 1e-12

# Euclidian distance between two points
# Returns the euclidian norm whith only one parameter
def distance(p, q = (0.0, 0.0)):
    return math.sqrt((float(q[0]) - float(p[0]))**2 + (float(q[1]) - float(p[1]))**2)

# Checks if a point is inside a circle
def isInside(c, p):
    return distance((c[0], c[1]), p) <= float(c[2]) + _EPSILON

# Expected radius of an enclosing circle given the center and the covered points
def expectedRadius(c, points):
	return max(distance(c,p) for p in points)

# Checks if a circle is valid
def isValid(circle, points):
	return all(isInside(circle, p) for p in points)

# Return the best integer conversion of the float smallest enclosing circle
def smallestEnclosingCircleInt(points):
	x, y, r = smallestEnclosingCircle(points)

	if (int(x) == x and int(y) == y):
		return (x, y, max(int(math.ceil(r)), 1))

	if r == 0.0:
		return (int(x), int(y), 1)
	
	center = (int(x), int(y))
	radius = max(int(math.ceil(expectedRadius(center, points))), 1)

	#for xInt in range(int(x)-int(math.ceil(math.log(r))), int(x)+int(math.ceil(math.log(r)))+1):
	#	for yInt in range(int(y)-int(math.ceil(math.log(r))), int(y)+int(math.ceil(math.log(r)))+1):
	for xInt in range(int(x)-1, int(x)+2):
		for yInt in range(int(y)-1, int(y)+2):
			c = (xInt, yInt)
			rc = int(math.ceil(expectedRadius(c, points)))
	    	if (1 <= rc < radius):
	        	center = c
	        	radius = rc

	return (center[0], center[1], radius)

# Smallest enclosing circle
# Incremental randomized algorithm
# Runs in expected O(n) time
def smallestEnclosingCircle(points):
	# Conversion to float + shuffle (randomized algorithm in order to achieve O(n) expected time)
	randPoints = [(float(z[0]), float(z[1])) for z in points]
	random.shuffle(randPoints)

	# Edge cases
	if (len(randPoints) < 1): return None
	if (len(randPoints) == 1): return (randPoints[0][0], randPoints[0][1], 0.0)

	# Init : let's assume the smallest enclosing circle is the one made with the first two points
	c = _smallestEnclosingCircleTwoPoints(randPoints[0], randPoints[1])

	# Recompute the circle when needed
	for i in range(2, len(randPoints)):
		if not isInside(c, randPoints[i]):
			c = _smallestEnclosingCircleOneBoundaryPoint(randPoints[0:i], randPoints[i])
	return c

# Smallest enclosing circle when one point is known to be on the boundary
def _smallestEnclosingCircleOneBoundaryPoint(points, p):
	# Shuffle again
	randPoints = points
	random.shuffle(randPoints)

	# Same process
	c = _smallestEnclosingCircleTwoPoints(randPoints[0], p)

	for i in range(1, len(randPoints)):
		if not isInside(c, randPoints[i]):
			c = _smallestEnclosingCircleTwoBoundaryPoints(randPoints[0:i], p, randPoints[i])
	return c

# Smallest enclosing circle when two points are known to be on the boundary
def _smallestEnclosingCircleTwoBoundaryPoints(points, p, q):
	# Shuffle again
	randPoints = points
	random.shuffle(randPoints)

	# Same process
	c = _smallestEnclosingCircleTwoPoints(p, q)
	
	for i in range(len(randPoints)):
		if not isInside(c, randPoints[i]):
			c = _smallestEnclosingCircleThreePoints(p, q, randPoints[i])
	return c

# Smallest enclosing circle for two points
def _smallestEnclosingCircleTwoPoints(p, q):
	# Center is the middle of those two points, radius is the distance from those points divided by 2
    return ( (p[0] + q[0]) / 2.0 , (p[1] + q[1]) / 2.0 , distance(p,q) / 2.0)

# Smallest enclosing circle for three points
def _smallestEnclosingCircleThreePoints(p, q, z):
	sides = sorted([(distance(p, q), p, q), (distance(q, z), q, z), (distance(p, z), p, z)])
	
	# Pythagore
	d = sides[2][0]**2 - (sides[0][0]**2 + sides[1][0]**2)

	# If the triangle is acute, we just return the circumcircle
	# Note : it's ACUTE, not cute
	# Please do not ask it out on a date, that would be weird
	# (We won't comment on the possible puns for circumcircle)
	if (d < 0.0 + _EPSILON):
		return _circumcircle(p, q, z)
	else:
		return _smallestEnclosingCircleTwoPoints(sides[2][1], sides[2][2])

# Circumcirle of a triangle
def _circumcircle(p, q, z):
    d = (p[0]*(q[1] - z[1]) + q[0]*(z[1] - p[1]) + z[0]*(p[1] - q[1])) * 2.0
    if (d == 0.0): return None
    x = ((distance(p)**2)*(q[1] - z[1]) + (distance(q)**2)*(z[1] - p[1]) + (distance(z)**2)*(p[1] - q[1])) / d
    y = ((distance(p)**2)*(z[0] - q[0]) + (distance(q)**2)*(p[0] - z[0]) + (distance(z)**2)*(q[0] - p[0])) / d
    return (x, y, distance(p, (x,y)))