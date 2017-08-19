import math

gcd = math.gcd

C = [[0 for j in range(444)] for j in range(444)]

for i in range(0, 401):
    C[i][0] = 1
    for j in range(1, i+1):
        C[i][j] = C[i-1][j] + C[i-1][j-1]

C_n_le_m = [[0 for j in range(444)] for j in range(444)]
for i in range(0, 401):
    C_n_le_m[i][0] = 1
    for j in range(1, i+1):
        C_n_le_m[i][j] = C[i][j] + C_n_le_m[i][j-1]

n_m_nostr = [[0 for m in range(0, 22)] for n in range(0, 22)]
n_m_noflu = [[0 for m in range(0, 22)] for n in range(0, 22)]

r, s, d, c = 0, 0, 0, 0

def calc_no_flu():
    n_m_noflu[0][0] = 1
    for i in range(0, s):
        for m in range(0, d+1):
            for j in range(0, min(r, c-1)+1):
                if m+j > d:
                    break
                n_m_noflu[i+1][m+j] += n_m_noflu[i][m] * C[r][j]

def calc_no_str():
    dp = [[0 for i in range(0, r+1)] for j in range(0, r+1)]
    tdp = [[[0 for k in range(0, r+1)] for j in range(0, r+1)] for i in range(0, r+1)]
    tdp[0][0][0] = 1
    for i in range(0, r):
        for j in range(0, i+1):
            for k in range(0, j+1):
                t = tdp[i][j][k]
                tdp[i+1][j][0] += t
                if k+1 < c:
                    tdp[i+1][j+1][k+1] += t

    for i in range(0, r+1):
        for j in range(0, r+1):
            dp[i][j] = sum(tdp[i][j])

    n_m_nostr[0][0][0] = 1
    n_m_nostr[0][r][0] = 1
    for i in range(1, s+1):
        for m in range(0, d+1):
            n_m_nostr[i][0][m] = n_m_nostr[i-1][r][m]
        for rank in range(1, r+1):
            for m in range(0, d+1):
                for j in range(0, r+1):
                    if m+j > d:
                        break
                    n_m_nostr[i][rank][m+j] += n_m_nostr[i-1][r][m] * dp[rank][j]


def f(i):
    res = 0
    for m in range(c, min(r, d)+1):
        rst = d-m
        for j in range(0, rst+1):
            tmp = n_m_noflu[i-1][j] * C[r][m] * C[(s-i)*r][rst-j]
            res += tmp
    return res

def F():
    res = 0
    for i in range(1, s+1):
        res += f(i)
    return res

def g(i, j):
    res = 0
    rst = d-c
    for p in range(0, rst+1):
        u = r*s - (i-1)*r - (j+c-1)
        v = rst - p
        # print(res)
        # print(i, j-1, p, n_m_nostr[i][j-1][p])
        # print(u, v, C[u][v])
        res += n_m_nostr[i][j-1][p] * C[u][v]
    return res

def G():
    if c > r:
        return 0
    res = 0
    for i in range(1, s+1):
        for j in range(1, r-c+1):
            res += g(i, j)
    return res

# import sys
# sys.stdin = open("poker.in", "r")
# sys.stdout = open("poker.out", "w")
ppp = 0
while True:
    r, s, d, c = map(int, input().split())
    n_m_noflu = [[0 for m in range(0, 22)] for n in range(0, 22)]
    n_m_nostr = [[[0 for l in range(0, 22)] for m in range(0, 22)] for n in range(0, 22)]
    calc_no_flu()
    calc_no_str()
    if r == 0:
        break
    X = F()
    Y = G()
    Z = C[r*s][d]
    gyz = gcd(Y, Z)
    if ppp == 1:
        print("")
    ppp = 1
    print(Z)
    print("%d/%d" % (Y/gyz, Z/gyz))
    gxz = gcd(X, Z)
    print("%d/%d" % (X/gxz, Z/gxz))

