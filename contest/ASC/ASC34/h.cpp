#include <bits/stdc++.h>
using namespace std;
const int mod = 239;
typedef long long LL;
#define N 33
inline int modit( int a ){
  return ( a % mod + mod ) % mod;
}
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( int a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
struct Mat{
  int n , a[ N ][ N ];
  Mat( int _n = 0 ) : n(_n) {
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        a[ i ][ j ] = 0;
  }
  Mat operator*( const Mat& he ) const{
    Mat tmp( n );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        for( int k = 0 ; k < n ; k ++ )
          tmp.a[ i ][ j ] = add( tmp.a[ i ][ j ],
                                 mul( a[ i ][ k ] , he.a[ k ][ j ] ) );
    return tmp;
  }
  Mat operator^( LL tk ) const{
    Mat I( n ) , A( n );
    for( int i = 0 ; i < n ; i ++ ){
      I.a[ i ][ i ] = 1;
      for( int j = 0 ; j < n ; j ++ )
        A.a[ i ][ j ] = a[ i ][ j ];
    }
    while( tk ){
      if( tk & 1ll ) I = I * A;
      A = A * A; tk >>= 1;
    }
    return I;
  }
};
LL n , k , ret[ N ];
Mat mm[ 333 ] , om[ 333 ] , rr;
void solve(){
  mm[ 0 ] = Mat( k + 1 );
  for( int i = 0 ; i <= k ; i ++ )
    mm[ 0 ].a[ i ][ i ] = 1;
  for( int now = 1 ; now <= mod ; now ++ ){
    mm[ now ] = Mat( k + 1 );
    for( int i = 0 ; i <= k ; i ++ ){
      mm[ now ].a[ i ][ i ] = modit( 2 * i );
      if( i + 1 <= k )
        mm[ now ].a[ i + 1 ][ i ] = modit( now + 1 - 2 * i );
    }
    om[ now ] = mm[ now ];
    mm[ now ] = mm[ now ] * mm[ now - 1 ];
  }
  rr = mm[ 0 ];
  LL dlt = n - 1;
  for( int i = dlt % mod + 1 ; i <= dlt % mod + mod ; i ++ ){
    int j = i; if( j > mod ) j -= mod;
    rr = om[ j ] * rr;
  }
  rr = rr ^ ( dlt / mod );
  rr = rr * mm[ dlt % mod ];
  printf( "%d\n" , rr.a[ k ][ 1 ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "peaks.in" , "r" , stdin );
  freopen( "peaks.out" , "w" , stdout );
#endif
  scanf( "%lld%lld" , &n , &k );
  solve();
}
