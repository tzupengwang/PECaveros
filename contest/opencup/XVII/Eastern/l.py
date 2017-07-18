A, B, C = 0, 1, 1

def sgn(x):
    if x > 0:
        return 1
    if x < 0:
        return -1
    return 0

for _ in range(100000):
    if (sgn(A*A-4*B*C), sgn(B*B-4*A*C), sgn(C*C-4*A*B)) != (-1,-1,1):
        print(_,A,B,C)
    A, B, C = B, C, B+C
