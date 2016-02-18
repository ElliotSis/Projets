import sys
import math
import random
import time
import utilities

random.seed()

# Return the cost of an antena or r radius
def evaluating(C, K, r):
	return K + C * r**2

# OLD CODE WITH BARYCENTER
# # Return the barycenter from a list of point, rounded
# def barycenter(li):
# 	x = 0
# 	y = 0
# 	for t in li:
# 		x = x + t[0]/float(len(li))
# 		y = y + t[1]/float(len(li))
# 	return int(round(x)), int(round(y))

# # Return min radius from the circle which have all points in l into it
# def getRadius(l, bary):
# 	res = 0
# 	for p in l:
# 		aux = (p[0]-bary[0])**2 + (p[1]-bary[1])**2
# 		if aux > res:
# 			res = aux
# 	return int(math.ceil(math.sqrt(res))) if res > 0.0 else 1

# # Get bary + radius (useful)
# def getBaryAndRadius(l):
# 	bary = barycenter(l)
# 	return bary, getRadius(l, bary)

# Get best circle + radius (useful)
def getBestCircle(l):
	return utilities.smallestEnclosingCircleInt(l)

# Return the fusion of 2 list
def fusion(l1, l2):	
	fusionned = l1[:-1] + l2[:-1]
	fusionned.append(getBestCircle(fusionned))
	return [fusionned]

# Return the fission with first list with i elements
def fission(l, i):
	l1 = l[:i]
	l2 = l[i:len(l)-1]
	l1.append(getBestCircle(l1))
	l2.append(getBestCircle(l2))
	return [l1, l2]

# Function to call at the beggining to compute all min circles
# Format : [p0, p1, ..., pn, (x, y, radius)]
def cirlceInitCompute(subSets):
	for l in subSets:
		l.append(getBestCircle(l))

# Get the cost of each antenna in a list
def getCost(l, C, K):
	res = []
	for b in l:
		res.append(evaluating(C, K, b[-1][-1]))
	return res

# Get the total cost as an int
def getTotalCost(l, C, K):
	res = 0
	for b in l:
		res = res + evaluating(C, K, b[-1][-1])
	return res

# Fusion of subSets[i1] and subSets[i2]
def actionFusion(subSets, i1, i2):
	l1 = subSets[i1][:]
	l2 = subSets[i2][:]
	del subSets[i1]
	del subSets[i2-1]
	return subSets + fusion(l1, l2)

# Fission of subSets[i] from index j
def actionFission(subSets, i, j):
	l = subSets[i]
	del subSets[i]
	return subSets + fission(l, j)

# Return True if a fission is possible in the subset
def isFissionPossible(subSets):
	res = False
	for l in subSets:
		res = res or len(l) > 2
	return res

# Return a list with all the index where the fission is possible
def getIndexFissionPossible(subSets):
	res = []
	i = 0
	for l in subSets:
		if len(l) > 2:
			res.append(i)
		i = i+1
	return res

# Random subdivision of a set of positions
def randomInit(lp):
	res = []
	if(len(lp) == 1):
		return [[lp[0],(lp[0][0], lp[0][1], 1)]]
	while(len(lp) != 0):
		#Size of the subSet
		size = random.randint(1, len(lp))
		aux = []
		while(size != 0):
			#index of the picked point
			i = random.randint(0, len(lp)-1)
			aux.append(lp[i])
			del lp[i]
			size = size - 1
		res.append(aux)
	cirlceInitCompute(res)
	return res

# Function to reduce the temperature every kStep to lambaT purcent
def reducingT(T, lambdaT, k, kStep):
	return T*lambdaT if (k % kStep == 0) else T

# Return True if accepted, else False
# diffE is the difference between the 2 energies and T the current temperature
def accepted(diffE, T):
	if(diffE < 0):
		return True
	else:
		return math.exp(-float(diffE)/float(T)) > random.random()

# Simulate the Annealing with :
#	-subSets : The initial subSet
#	-T0 : Initial Temperature
#	-lambdaT : Decreasing parameter for T
#	-kStep : number of steps at T=const (set 1 if decrreasing T at each step)
#	-kSameCost : number of steps at the same cost before random restart
#	-kMax : Number max of steps before stopping
#	-C : Weight of the radius of the antenna
#	-K : Weight of an antenna (by itself) 
#
#	@return : List of antena covering all the points and their respective radius
def simulatedAnnealing(Positions, T0, lambdaT, kStep, kSameCost, kMax, C, K):
	savePositions = Positions[:]
	subSets = randomInit(Positions)
	Positions = savePositions[:]
	T = T0
	#Definition for random restart and save best configurations
	maxSameCost = kSameCost
	currCost = 0
	saveCost = 0
	saveRes = subSets[:]
	countSameCost = 0
	#If only one point, break
	if len(savePositions) == 1:
		return subSets
	for k in range(kMax):
		aux = []
		save = subSets[:]
		#Fusion < 0.5 or fission > 0.5 ?
		isFusion = False
		isFission = False
		if len(subSets) == 1:
			isFission = True
		elif not(isFissionPossible(subSets)):
			isFusion = True
		else:
			choice = random.random()
			isFusion = choice < 0.5
			isFission = not(isFusion)
		if(isFusion):
			i1 = random.randint(0, len(subSets)-1)
			i2 = random.randint(0, len(subSets)-1)
			while i2 == i1:
				i2 = random.randint(0, len(subSets)-1)
			if(i2 < i1):
				i1, i2 = i2, i1
			aux = actionFusion(subSets, i1, i2)
		elif(isFission):
			temp = getIndexFissionPossible(subSets)
			i = temp[random.randint(0, len(temp)-1)]
			j = random.randint(1, len(subSets[i])-2)
			aux = actionFission(subSets, i, j)
		else:
			#Only one point
			break
		if(accepted(getTotalCost(aux, C, K) - getTotalCost(save, C, K), T)):
			subSets = aux[:]
		else:
			subSets = save[:]
		T = reducingT(T, lambdaT, k, kStep)
		#Random restart
		currCost = getTotalCost(subSets, C, K)
		if currCost != saveCost:
			countSameCost = 0
			saveCost = currCost
			if(getTotalCost(subSets, C, K) < getTotalCost(saveRes, C, K)):
				saveRes = subSets[:]
		else:
			countSameCost = countSameCost + 1
			if(countSameCost == maxSameCost):
				countSameCost = 0
				savePositions = Positions[:]
				subSets = randomInit(Positions)
				Positions = savePositions[:]
	return saveRes


#--------RANDOM GENERATOR OF POINTS ----
def randomPoints(n, xMax, yMax):
	res = []
	for i in range(n):
		res.append((random.randint(0, xMax), random.randint(0,yMax)))
	return res

#The function to call
def search(Positions, K, C, verbose = False):
	if verbose:
		print "points = " + str(Positions) + '\n'
	T0 = 10
	lambdaT = 0.99
	kStep = 5
	kMax = 10000
	kSameCost = 15
	#If there is no points, no need to do anything
	if len(Positions) == 0:
		res = []
	else:
		res = simulatedAnnealing(Positions, T0, lambdaT, kStep, kSameCost, kMax, C, K)
	if verbose:
		print "Final decomposition : " + str(res) + '\n'
	antennas = []
	for b in res:
		antennas.append((float(b[-1][0]), float(b[-1][1]), float(b[-1][2])))
	if verbose:
		print "Antennas : " + str(antennas) + '\n'
		print "Final cost : " + str(getTotalCost(res, C, K)) + '\n'
	return antennas
	
# search(randomPoints(0,20,20), 100, 10, True)
	
