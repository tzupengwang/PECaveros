mod = 1000000007
def rev(x): return pow(x,mod-2,mod)
a = [1,1]
s=set()
s.add(1)
while True:
  b = [0, 0]
  b[0] = 4 * a[0] * a[1] - a[0] * a[0]
  b[1] = 4 * a[1] * a[1]
  b[0] %= mod
  b[1] %= mod
  bb = (b[0] * rev(b[1])) % mod
  print(bb)
  if bb in s:
    break
  s.add(bb)
  a[0]=b[0]
  a[1]=b[1]
print(len(s))
