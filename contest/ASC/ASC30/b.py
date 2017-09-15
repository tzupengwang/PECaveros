import sys
sys.stdin = open('derangements.in','r')
sys.stdout = open('derangements.out','w')
N = 222
dp = [0 for i in range(N)]
dp[0] = dp[1] = 1
for i in range(2,N):
    dp[i] = 2 * i * dp[i-1]
    if i&1: dp[i] -= 1
    else: dp[i] += 1
    # dp[i] = dp[i-1] + 4 * (i-1) * dp[i-2]
print(dp[int(input())])
