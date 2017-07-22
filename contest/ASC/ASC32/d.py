class DJS:
    def __init__(self, n):
        self.p = [ i for i in range(n) ]
        self.cc = n
    def f(self, ui):
        if ui == self.p[ui]:
            return ui
        x = self.f(self.p[ui])
        self.p[ui] = x
        return self.p[ui]
    def uni(self, ui, vi):
        ui = self.f(ui)
        vi = self.f(vi)
        if ui == vi:
            return
        self.p[ui] = vi
        self.cc -= 1
import sys
sys.stdin = open('partitions.in', 'r')
sys.stdout = open('partitions.out', 'w')
R=lambda:list(map(int,input().split()))
n,l=R()
par = [ [ 0 for i in range(n+1) ] for i in range(n+1) ]
par[0][0] = 1
for i in range(n):
    for j in range(i+1):
        if par[i][j] == 0:
            continue
        par[i+1][j] += par[i][j] * j
        par[i+1][j+1] += par[i][j]
spar = [ sum(par[i]) for i in range(n+1) ]
s = [R()[1:] for i in range(l)]
ans = spar[n]
for msk in range(1, (1<<l)):
    djs = DJS(n)
    for k in range(l):
        if ((msk >> k) & 1) == 0:
            continue
        for i in range(1, len(s[k])):
            djs.uni( s[k][i-1] - 1, s[k][i] - 1 )
    cnt, tmp = 0, msk
    while tmp > 0:
        cnt += (tmp & 1)
        tmp >>= 1
    if cnt % 2:
        ans -= spar[djs.cc]
    else:
        ans += spar[djs.cc]
print(ans)
