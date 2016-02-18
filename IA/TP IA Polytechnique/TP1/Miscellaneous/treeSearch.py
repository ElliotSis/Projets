import sys
import copy
import random
sys.path.append('./Lib')

# Lib Michel
from node import *
from state import *
from lowestcost_search import *

# Our lib
from utilities import *
from antenna import *

random.seed()

class AntennaState(State):
    def __init__(self, points, K, C):
        self.K = K
        self.C = C
        self.remainingPoints = points
        self.antennas = []
        random.shuffle(self.remainingPoints)

    def equals(self, state):
        return all(a.equals(b) for a, b in zip(sorted(self.antennas, lambda x, y: -1 if x.center < y.center else (1 if x.center > y.center else 0)),sorted(state.antennas, lambda x, y: -1 if x.center < y.center else (1 if x.center > y.center else 0)))) and set(self.remainingPoints) == set(state.remainingPoints)

    def show(self):
        print 'Points yet to cover : ', self.remainingPoints
        print 'Antennas : '
        for antenna in self.antennas:
            antenna.show()
        print
        
    def executeAction(self, (action, i)):
        point = self.remainingPoints.pop()
        random.shuffle(self.remainingPoints)
        if action == 'coverPointAlone':
            self.antennas.append(Antenna(point))
        elif action == 'coverPointWithAntenna':
            self.antennas[i].addPoint(point)
        else:
            raise Exception('Erreur')

    def possibleActions(self):
        actions = []
        actions.append(('coverPointAlone', None))
        for i in range(len(self.antennas)):
            actions.append(('coverPointWithAntenna', i))
        return actions

    def cost(self, (action, i)):
        if action == 'coverPointAlone':
            return self.K + self.C
        elif action == 'coverPointWithAntenna':
            tmp = copy.deepcopy(self.antennas[i])
            tmp.addPoint(self.remainingPoints[-1])
            return tmp.cost(self.K, self.C) - self.antennas[i].cost(self.K, self.C)
        else:
            raise Exception('Erreur')

    def isGoal(self):
        return not self.remainingPoints


def search(points, K, C):
    solution = lowestcost_search(AntennaState(points, K, C))
    res = []
    for antenna in solution.state.antennas:
        res.append((float(antenna.center[0]), float(antenna.center[1]), float(antenna.radius)))
    return res
