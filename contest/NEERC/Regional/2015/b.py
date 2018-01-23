import sys
sys.stdin = open('binary.in', 'r')
sys.stdout = open('binary.out', 'w')

def ok(x):
    s = str(x)
    s2 = bin(int(s))[2:]
    ls = len(s)
    return s2[-ls:] == s
cand = []
cand.append(0)
cand.append(1)
ten = 1
for i in range(1, 1000):
    ten *= 10
    for j in cand:
        nj = j + ten
        if ok( nj ):
            cand.append(nj)
    if len(cand) >= 10001:
        # print(i+1)
        break;
# print(len(cand))
cand = sorted(cand)
print(cand[int(input())])

exit(0)
ct = 0
for i in range(1, 1000000):
    s = bin(i)[2:]
    s2 = bin(int(s))[2:]
    ls = len(s)
    if s2[-ls:] == s:
        # cand.append(s)
        ct += 1
        # print('a[{}]=\"{}\";'.format(ct, s))
        print(ct, s)
        if ct >= 10000:
            break
print(ct)
