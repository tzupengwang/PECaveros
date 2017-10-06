import sys
sys.stdin = open('dinner.in', 'r')
sys.stdout = open('dinner.out', 'w')
k,n=list(map(int,input().split()))
C = [ [0 for i in range(n+1)] for j in range(n+1)]
for i in range(n+1):
  C[i][0]=C[i][i]=1
for i in range(2,n+1):
  for j in range(1,i):
    C[i][j] = C[i-1][j] + C[i-1][j-1]
ans = k ** n
bns = -1
for i in range(k-1,0,-1):
    tans = C[k][i] * ( i ** n )
    ans = ans + bns * tans
    bns = -bns
print(ans)
