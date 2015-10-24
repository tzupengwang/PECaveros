
import random

T = 100
print( T )
for _ in range( T ):
    n , m , k = 1000 , 1000 , 0
    pt = []
    def ok( x , y ):
        if 1 < x < n and 1 < y < m:
            for ( px , py ) in pt:
                if abs( px - x ) + abs( py - y ) <= 2:
                    return False
            for ( px , py ) in [ ( 1 , 1 ) , ( n , m ) ]:
                if abs( px - x ) + abs( py - y ) <= 2:
                    return False
            return True
        return False
    for i in range( k ):
        x , y = random.randrange( n ) + 1 , random.randrange( m ) + 1
        while not ok( x , y ):
            x , y = random.randrange( n ) + 1 , random.randrange( m ) + 1
        pt.append( ( x , y ) )
    print( "%d %d %d" % ( n , m , k ) )
    for p in pt:
        print( "%d %d" % p )
