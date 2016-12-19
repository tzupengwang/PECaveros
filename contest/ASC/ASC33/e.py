import sys
N = 151
C = [ [ 0 for j in range( N ) ] for i in range( N ) ]
for i in range(N):
  C[i][i] = 1
for i in range(2,N):
  for j in range(1,i):
    C[i][j] = C[i-1][j-1] + C[i-1][j]
dp = [ [ 0 for i in range( N ) ] for j in range( N ) ]
# dp[0][0] = 1
for k in range( N ):
  dp[0][k] = 1
for i in range( 1 , N ):
  for j in range( 0 , i ):
    p = [ 0 for k in range( i + 1 ) ]
    p[1] = 1
    for k in range( 0 , j ):
      tp = [ 0 for k in range( i + 1 ) ]
      for sz in range( 1 , i ):
        for u in range( sz , i + 1 ):
          tp[ u ] += p[ u - sz ] * C[ i - ( u - sz ) - 1 ][ sz - 1 ]
      for u in range( i + 1 ):
        p[u] = tp[u]
    dp[i][j] = dp[i][j-1] + p[i]
  print( "dp[%d]=%d\n" % ( i , sum( dp[i] ) ) )
  sys.stdout.flush();
