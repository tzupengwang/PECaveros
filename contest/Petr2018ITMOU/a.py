import math
def f2(l, r):
  ret = (r - l) * r
  ret -= (r ** 2 - l ** 2) / 2.
  ret -= (r ** 2 - l ** 2) * math.log(r) / 4.
  ret += ((r ** 2) * math.log(r) - (l ** 2) * math.log(l)) / 4.
  ret -= (r ** 2 - l ** 2) / 8.
  ret *= 2. / ((r - l) ** 2)
  return ret

def f3t(l, r, p):
  ret = 36. * (p ** 2) * (math.log(r) ** 2)
  ret += 152. * (p ** 2)
  ret += 36. * (p ** 2) * (math.log(p) ** 2)
  ret -= 405. * (p * r)
  ret += 6. * p * (22. * p - 27. * r) * math.log(r)
  ret -= 6. * p * (12. * p * math.log(r) + 22. * p - 27. * r) * math.log(p)
  ret += 324. * (r ** 2)
  ret *= p / 324.
  return ret

def f3(l, r):
  ret = f3t(l, r, r) - f3t(l, r, l)
  ret *= 3. / ((r - l) ** 3)
  return ret

def f4t(l, r, p):
  ret1 = -((r - p) ** 4) / 4

  ret2 = 12. * (3. * (p ** 2) - 8. * p * r + 6. * (r ** 2)) * math.log(p)
  ret2 -= 9. * (p ** 2) * (4. * math.log(r) + 1)
  ret2 += 32. * p * r * (3. * math.log(r) + 1)
  ret2 -= 36. * r * r * (2. * math.log(r) + 1)
  ret2 *= p * p / 96.

  ret3 = -72. * (3 * p - 4 * r) * (math.log(p) ** 2)
  ret3 -= 27. * p * (8 * (math.log(r) ** 2) + 4 * math.log(r) + 1)
  ret3 += 12. * math.log(p) * (12 * (3 * p - 4 * r) * math.log(r) + 9 * p - 16 * r)
  ret3 += 32. * r * (9 * (math.log(r) ** 2) + 6 * math.log(r) + 2)
  ret3 *= (p ** 3) / 864

  ret4 = -24 * (math.log(p) ** 2) * (4 * math.log(r) + 1)
  ret4 += 12 * (math.log(p)) * (8 * (math.log(r) ** 2) + 4 * math.log(r) + 1)
  ret4 += 32 * (math.log(p) ** 3) - 32 * (math.log(r) ** 3)
  ret4 += -24 * (math.log(r) ** 2) - 12 * (math.log(r)) - 3
  ret4 *= (p ** 4) / 512

  return ret1 + ret2 + ret3 + ret4
def f4(l, r):
  ret = f4t(l, r, r) - f4t(l, r, l)
  ret *= 4. / ((r - l) ** 4)
  return ret

for _ in range(int(input())):
  n,l,r=list(map(int,input().split()))
  if n == 2: print('%.9f' % f2(l,r))
  if n == 3: print('%.9f' % f3(l,r))
  if n == 4: print('%.9f' % f4(l,r))
