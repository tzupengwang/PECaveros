a='....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx'
b='....x.....x.....x.x...x.x.....x.........x.x...x.x...x.x...x'
c='....x.....x.....x.x...x.x.....x.........x.x...x.x...x.x...x'
d='....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.x...x'
e='....x.x.........x.....x.....x.x...x.....x.x...x.....x.x...x'
f='....x.x.........x.....x.....x.x...x.....x.x...x.....x.x...x'
g='....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx'
ret = 'char c[12][99][99]={'
for i in range(1,11):
  st = (i-1)*6
  ret += '{'
  for k in [a, b, c, d, e, f, g]:
    ret += '\"' + k[st:st+5] + '\",'
  ret += '},'
ret += '};'   
print(ret)
