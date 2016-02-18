def partitions(s):
	if (not s):
		return [[]]
	else:
		a = s.pop()
		l = partitions(s)
		res = []
		for p in l:
			res.append([{a}] + p)
			for ss in p:
				res.append([ss | {a}] + [k for k in p if k != ss])
		return res


print(*partitions({1,2,3,4,5,6,7,8,9,10,11,12}),sep='\n')