import sys
for line in sys.stdin:
    n = int(line)
    dp = [0 for i in range(n+1)]
    for i in range(n,0,-1):
        dp[i] = (n//i)**4
        for j in range(i+i,n,i):
            dp[i] -= dp[j]
    print(dp[1])
