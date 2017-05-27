a = [ [ -1 for j in range(10) ] for i in range(10) ]
a[1][1] = 0
two = 1
for i in range(1,1000):
  two *= 2
  rgt = two % 10
  lft = two
  while lft >= 10:
    lft //= 10
  if a[lft][rgt] == -1:
    a[lft][rgt] = i
for i in range(10):
  for j in range(10):
    print('a[%d][%d]=%d;' % (i, j, a[i][j]))
