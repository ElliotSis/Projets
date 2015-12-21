problem = False
m, n = map(int, input().split())

if (m > n or m < 1): problem = True
l = []
for k in range(m):
	tmp = list(map(int,input().split()))
	if (tmp[0] <= 0): problem = True
	tmp.pop(0)
	tmp.sort()
	l.append(tmp)

ll = []
sum_n_k = 0
for k in range(m):
	n_k = int(input())
	sum_n_k += n_k
	if (n_k <= 0 or n_k > len(l[k])): problem = True
	tmpp = []
	for i in range(n_k):
		tmp = list(map(int, input().split()))
		if (tmp[0] <= 0): problem = True
		tmp.pop(0)
		tmpp += tmp
	tmpp.sort()
	ll.append(tmpp)

if(sum_n_k != n): problem = True

print(len([1 for k in range(m) if l[k]==ll[k]]) == m and not problem)