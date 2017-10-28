import random
import string

def randstr():
    res = ''.join(random.choice(string.ascii_lowercase) for _ in range(10))
    return res

t = 20
print(t)
for i in range(t):
  n = 50000
  print(n)
  ht = set()
  for i in range(n):
      s = randstr()
      while s in ht:
          s = randstr()
      ht.add(s)
      print(s)
