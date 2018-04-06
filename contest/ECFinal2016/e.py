from fractions import Fraction
def r(s):
  ret = 0
  cnt = 0
  gt = False
  for c in s:
    if ord('0') <= ord(c) <= ord('9'):
      ret = ret * 10 + (ord(c) - ord('0'))
      if gt:
        cnt += 1
    else:
      gt = True
  for i in range(cnt,5):
    ret = ret * 10
  return ret
def read():
  ss = input().split(':')
  return Fraction(r(ss[1]),r(ss[0]))
t = int(input())
for _ in range(t):
  n = int(input())
  rr = [Fraction(1) / (Fraction(1) + read()) for i in range(n)]
  rr = sorted(rr)
  ans = 0
  s = Fraction(0)
  for i in rr:
    s += i
    if s >= Fraction(1):
      break
    ans += 1
  print( 'Case #%d: %d' % (_ + 1 , ans) )
