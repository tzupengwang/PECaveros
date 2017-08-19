import math

def C(n, k):
    res = 1
    for i in range(n-k+1, n+1):
        res *= i
    return res

fi = open("discuss.in", "r")
fo = open("discuss.out", "w")

z = int(fi.read())
ans = z
target = z
for k in range(2, 450):
    target *= k
    l = k+k
    r = l
    while C(r, k) < target:
        r *= 2
    res = -1
    while l <= r:
        mid = (l+r) >> 1
        if C(mid, k) <= target:
            res = mid
            l = mid+1
        else:
            r = mid-1
    if C(res, k) == target and res != -1:
        ans = min(ans, res)
if z == 1:
    ans = "1"
fo.write(str(ans)+"\n")

