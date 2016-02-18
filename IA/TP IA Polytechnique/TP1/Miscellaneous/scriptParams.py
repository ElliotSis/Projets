from SimulatedAnnealing import *
import sys
import random

def formatedAnswer(n, T0, lambdaT, kStep, kMax, Min, purcent, time, init):
	if init:
		return " ; T0 ; lambdaT ; kStep ; kMax ; Min ; % ; MoySec" + '\n'
	return "{0:d} ; {1:d} ; {2:f} ; {3:d} ; {4:d} ; {5:d} ; {6:.2%} ; {7:2f} ".format(n ,T0, lambdaT, kStep, kMax, Min, purcent, time) + '\n'

random.seed()
T0_list = [1,5,10]
lambdaT = 0.97
kStep_list = [1, 10, 100, 1000]
kMax_list = [10, 100, 1000, 10000, 100000]
nbIte = 100
C=10
K=100
for n in range(3,11):
	positions = randomPoints(n, 20, 20)
	with open('testParams/n_'+str(n)+'.txt', 'w') as f:	
		f.write(formatedAnswer(1,2,3,4,5,6,7, 9,True))
		for T0 in T0_list:
			for kMax in kMax_list:
				for kStep in kStep_list:
					if kStep < kMax:
						begin = time.clock()
						mini = 99999
						count = 0
						for i in range(nbIte):
							save = positions[:]
							positions = randomInit(positions)
							aux = getTotalCost(simulatedAnnealing(positions, T0, lambdaT, kStep, kMax, C, K), C, K)
							if aux < mini:
								mini = aux
								count = 1
							elif aux == mini:
								count = count + 1
							positions = save
						end = time.clock()
						f.write(formatedAnswer(n,T0,lambdaT,kStep,kMax,mini,float(count)/nbIte, (end - begin)/nbIte,False))


								