M = [ [ 0 for i in range( 66 ) ] for j in range( 66 ) ]
F = [ [ 0 for i in range( 66 ) ] for j in range( 66 ) ]
dpmf = [ [ 0 for i in range( 66 ) ] for j in range( 66 ) ]
dpfm = [ [ [ 0 for i in range( 66 ) ] for j in range( 66 ) ] for k in range( 66 ) ]
sF = [ 0 for j in range( 66 ) ]
C = [ [ 0 for i in range( 111 ) ] for j in range( 111 ) ]
for i in range( 0 , 111 ):
  C[ i ][ 0 ] = C[ i ][ i ] = 1
for i in range( 2 , 111 ):
  for j in range( 1 , i ):
      C[ i ][ j ] = C[ i - 1 ][ j - 1 ] + C[ i - 1 ][ j ]
def H( a , b ):
  a += b - 1
  ret = 1
  for i in range( a , a - b ):
    ret *= i
  for i in range( 1 , b + 1 ):
    ret //= i
  return ret
sF[ 1 ] = 1;
dpmf[ 0 ][ 0 ] = 1;
for i in range( 0 , 66 ):
  dpfm[ 0 ][ 0 ][ i ] = 1
for i in range( 1 , 66 ):
  for j in range( 1 , i + 1 ):
    # M[ i ][ j ]
    cnt = 0
    for o in range( 1 , i + 1 ):
      if i % o != 0: continue
      if j % o != 0: continue
      cnt += 1
      M[ i ][ j ] = dpmf[ o ][ j // o ]
    M[ i ][ j ] //= cnt
    # dpmf[ i ][ j ]
    for x in range( 1 , j - i + 1 ):
      dpmf[ i ][ j ] += dpmf[ i - 1 ][ j - x ] * sF[ x ]
    F[ i ][ j ] = dpfm[ i ][ j - 1 ][ j - i + 1 ]
    for k in range( 0 , 66 ):
      dpfm[ i ][ j ][ k ] = dpfm[ i ][ j ][ k - 1 ]
      for u in range( 1 , min( i , ( j // k ) ) ):
        dpfm[ i ][ j ][ k ] += dpfm[ i - u ][ j - u * k ][ k - 1 ] * H( sum( M[ k ] ) , u )
  for j in range( 1 , i + 1 ):
    sF[ i ] += F[ j ][ i ];
while True:
  n = int( input() )
  print( sum( M[ n ] ) )
