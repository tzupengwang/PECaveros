import math

def fix(a,b,c):
    return tuple(sorted((a,b,c)))


k , n = map( int , input().split() )

a , b , c = 1 , k , k*(k+1)


st1 = set()
st2 = set([fix(a,b,c)])

qu = [ (a , b , c) ]
ans = []
cur = 0

def SQRT(n):
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x

# def SQRT(x):
    # t = int(math.sqrt(x))
    # l , r = 0 , x
    # while l <= r:
        # mid = ( l+r ) // 2
        # if mid*mid < x:
            # l = mid+1
        # elif mid*mid == x:
            # return mid
        # else:
            # r = mid-1

while cur < len(qu):
    A,B,C = qu[ cur ]
    cur += 1
    if A*A+B*B+C*C != k*(A*B+A*C+B*C)+1:
        continue
    if A > 0 and B > 0 and C > 0 and A not in st1 and B not in st1 and C not in st1:
        st1.add(A)
        st1.add(B)
        st1.add(C)
        ans.append((A,B,C))
    if len(ans) >= n:
        break

    AAp = (k*(B+C)) - A
    # hao = k*k*(B+C)*(B+C)-4*B*B-4*C*C+4*k*B*C+4
    # AAp = (k*(B+C)+SQRT(hao)) // 2
    # AAn = (k*(B+C)-SQRT(hao)) // 2

    if fix(AAp, B, C) not in st2:
        st2.add(fix(AAp, B, C))
        qu.append((AAp, B, C))

    A, B = B, A
    AAp = (k*(B+C)) - A
    # hao = k*k*(B+C)*(B+C)-4*B*B-4*C*C+4*k*B*C+4
    # AAp = (k*(B+C)+SQRT(hao)) // 2
    # AAn = (k*(B+C)-SQRT(hao)) // 2
    if fix(AAp, B, C) not in st2:
        st2.add(fix(AAp, B, C))
        qu.append((AAp, B, C))

    A, C = C, A
    AAp = (k*(B+C)) - A
    # hao = k*k*(B+C)*(B+C)-4*B*B-4*C*C+4*k*B*C+4
    # AAp = (k*(B+C)+SQRT(hao)) // 2
    # AAn = (k*(B+C)-SQRT(hao)) // 2
    if fix(AAp, B, C) not in st2:
        st2.add(fix(AAp, B, C))
        qu.append((AAp, B, C))


print('\n'.join(map(lambda p:"%d %d %d" % p, ans[:n])))




