import sys
import random
import copy

# Our programs
import treeSearch
import localSearch
import utilities

random.seed()

def isWorking(points, sol):
	for p in points:
		if not any(utilities.isInside(c, p) for c in sol):
			return False
	return True

def cost(sol, K, C):
	return sum(K + (c[2]**2)*C for c in sol)	

n = 0
for i in range(100):
	points = []
	K = random.randrange(0, 10000)
	C = random.randrange(0, 100)

	for p in range(random.randrange(1, 15)):
		points.append((random.randrange(0, 100), random.randrange(0, 100)))

	#points = [(19, 36), (22, 35), (23, 2), (20, 5), (9, 33), (32, 47), (24, 17), (15, 17), (47, 23), (9, 37), (31, 22), (4, 35)]
	#K = 421
	#C = 43

	local = localSearch.search(copy.deepcopy(points), K, C)
	tree = treeSearch.search(points, K, C)

	if (cost(tree, K, C) > cost(local, K, C)):
		raise Exception('ERREUR')

	if (sorted(local) == sorted(tree) or cost(local, K, C) == cost(tree, K, C)):
		n+=1
		print 'OK'
	else: 
		print 'K : ', K
		print 'C : ', C
		print 'points : ', points
		print
		print 'Tree sol :'
		print sorted(tree)
		print 'Works : ', isWorking(points, tree)
		print 'Cost : ', cost(tree, K, C)
		print
		print 'Local sol :'
		print sorted(local)
		print 'Works : ', isWorking(points, local)
		print 'Cost : ', cost(local, K, C)
		print
		print 'Cost difference : ', cost(local, K, C) - cost(tree, K, C)
		print
print 'Pourcentage of correctness : ', n
