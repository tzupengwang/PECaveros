
/*
 * xor convolution:
 * x = (x0,x1) , y = (y0,y1)
 * z = ( x0y0 + x1y1 , x0y1 + x1y0 )
 * =>
 * x' = ( x0+x1 , x0-x1 ) , y' = ( y0+y1 , y0-y1 )
 * z' = ( ( x0+x1 )( y0+y1 ) , ( x0-x1 )( y0-y1 ) )
 * z = (1/2) * z''
 * or convolution:
 * x = ( x0 , x0+x1 )
 * and convolution:
 * x = ( x0+x1 , x1 )
 */

typedef long long ll;
const int MAXN = (1<<20)+10;
const ll MOD = 1e9+7;
inline void fwt( ll x[ MAXN ] , int N , bool inv=0 ) {
  for( int d = 1 ; d < N ; d <<= 1 ) {
    int d2 = d<<1;
    for( int s = 0 ; s < N ; s += d2 ) {
      for( int i = s , j = s+d ; i < s+d ; i++ , j++ ) {
        ll ta = x[ i ] , tb = x[ j ];
        x[ i ] = ta+tb;
        x[ j ] = ta-tb;
        if( x[ i ] >= MOD ) x[ i ] -= MOD;
        if( x[ j ] < 0 ) x[ j ] += MOD;
      }
    }
  }
  if( inv )
    for( int i = 0 ; i < N ; i++ )
      x[ i ] /= (ll)N;
}

