def okay(x):
  while x > 0:
    if x % 10 < 1 or x % 10 > 2:
      return False
    x //= 10;
  return True
for i in range(42,43):
  x = 2**i
  p = 1
  while not okay(x * p):
    p += 1
  print(p, x * p)
