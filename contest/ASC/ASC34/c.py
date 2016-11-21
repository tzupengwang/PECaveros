from fractions import Fraction
import sys
fi = open( 'arbitrage.in' , 'r' )
fo = open( 'arbitrage.out' , 'w' )
n = int( fi.readline() )
L = [ [ [0,0] for i in range(n) ] for j in range(n) ]
R = [ [ [0,0] for i in range(n) ] for j in range(n) ]
for i in range(n):
    for j in range(n):
        x = fi.readline().split(' ')
        L[i][j], R[i][j] = Fraction(x[0]), Fraction(x[1])
for i in range(n):
    for j in range(n):
        if 1 / L[ j ][ i ] < R[ i ][ j ]:
            R[ i ][ j ] = 1 / L[ j ][ i ]
for k in range(n):
    for i in range(n):
        for j in range(n):
            R[i][j] = min( R[i][j] , R[i][k] * R[k][j] )
        if R[i][i] < Fraction(1,1):
            fo.write( "Impossible\n" )
            sys.exit( 0 )
for i in range(n):
    fans = ""
    for j in range(n):
        tmp = str(R[0][j]/R[0][i])
        if not ( '/' in tmp ): tmp += "/1"
        fans += tmp + " "
    fans += "\n"
    fo.write( fans )
