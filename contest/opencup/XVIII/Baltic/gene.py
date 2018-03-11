import random

n = 300
P = 1000000007

print(n)

for i in range(n):
    print(' '.join(map(str, [random.randrange(0, P) for j in range(n)])))
