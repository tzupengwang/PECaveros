import math
ip = input()
n, m = list(map(int,ip.split()))

if n > m:
    n, m=m, n

if n == m:
    print(n)
else:
    n = n-1
    m = m-1
    g = math.gcd(n, m)
    g2 = g+g
    def f(X, Y):
        ax = X // g2
        bx = X % g2
        ay = Y // g2
        by = Y % g2
        if by < bx:
            ax, ay = ay, ax
            bx, by = by, bx
        res = (bx + 1) * (ax + 1) * (ay + 1)
        res += (by - bx) * ax * (ay + 1)
        res += (g2 - 1 - by) * ax * ay
        return res
    k = m // g2 + 1
    ans = f(n, m) + f(n, g2 * k) - f(n, g2 * k - m - 1)
    ans -= (n // g2 + 1) * (m // g2 + 1) + (n//g - n//g2) * (m//g - m//g2)
    ans %= int(10**18 + 9)
    print(ans)
