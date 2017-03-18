#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 1e5+10;

struct BIT {
  int sz;
  LL dat[ MAXN ];
  void init( int _sz ) {
    sz = _sz;
    fill( dat , dat + sz + 1 , 0 );
  }
  void upd( int id , LL x ) {
    for ( int i = id ; i <= sz ; i += i&-i )
      dat[ i ] += x;
  }
  LL qry( int id ) {
    LL res = 0;
    for ( int i = id ; i > 0 ; i -= i&-i )
      res += dat[ i ];
    return res;
  }
} bit;

int n , q;

int tl[ MAXN ] , tr[ MAXN ] , stamp;
int ch[ MAXN ][2];
LL len[ MAXN ] , w[ MAXN ];

void dfs( int u ) {
  if ( u == 0 ) return ;
  tl[ u ] = ++stamp;
  dfs( ch[ u ][ 0 ] );
  dfs( ch[ u ][ 1 ] );
  tr[ u ] = stamp;
}

inline LL qry( int u ) {
  return bit.qry( tr[ u ] ) - bit.qry( tl[ u ] - 1 );
}

int main() {
  scanf( "%d%d" , &n , &q );
  for ( int i = 1 ; i <= n+1 ; i ++ )
    scanf( "%lld" , w+i );
  for( int i = n+2 ; i <= n+n+1 ; i++ ) {
    scanf( "%lld%d%d" , len+i , ch[i]+0 , ch[i]+1 );
    if ( ch[ i ][ 0 ] < 0 ) ch[ i ][ 0 ] *= -1;
    else ch[ i ][ 0 ] += n+1;
    if ( ch[ i ][ 1 ] < 0 ) ch[ i ][ 1 ] *= -1;
    else ch[ i ][ 1 ] += n+1;
  }
  dfs( n+2 );
  bit.init( n+n+1 );
  for ( int i = 1 ; i <= n + 1 ; i++ )
    bit.upd( tl[ i ] , w[ i ] );
  while ( q-- ) {
    int tp , k;
    scanf( "%d%d" , &tp , &k );
    if ( tp == 1 ) {
      LL v;
      scanf( "%lld" , &v );
      bit.upd( tl[ k ] , v - w[ k ] );
      w[ k ] = v;
    } else {
      k += n+1;
      LL lw = qry( ch[ k ][ 0 ] );
      LL rw = qry( ch[ k ][ 1 ] );
      double ans = ( 1. * len[ k ] * rw ) / ( lw + rw );
      printf( "%.15f\n" , ans );
    }
  }
}
