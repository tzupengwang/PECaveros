def isqrt(n):
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x
n = int(input())
x = isqrt(n)
print('YES' if x * x == n else 'NO')
