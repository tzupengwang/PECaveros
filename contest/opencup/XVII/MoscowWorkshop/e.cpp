#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5+10;
const int LOG  = 18;

int n , A[ MAXN ];
int L[ LOG ][ MAXN ];
int R[ LOG ][ MAXN ];

struct min_SEG {
  int dat[ MAXN<<2 ];
  void init( int id , int l , int r , int *arr ) {
    if ( l == r ) {
      dat[id] = arr[ l ];
      return;
    }
    int mid = ( l+r ) / 2;
    init( id*2 , l , mid , arr );
    init( id*2+1 , mid+1 , r , arr );
    dat[ id ] = min( dat[ id*2 ] , dat[ id*2+1 ] );
  }
  int qry( int id , int l , int r , int a , int b ) {
    if ( b < l || r < a ) return MAXN;
    if ( a <= l && r <= b ) return dat[ id ];
    int mid = ( l+r ) / 2;
    int r1 = qry( id*2 , l , mid , a , b );
    int r2 = qry( id*2+1 , mid+1 , r , a , b );
    return min( r1 , r2 );
  }
};

struct max_SEG {
  int dat[ MAXN<<2 ];
  void init( int id , int l , int r , int *arr ) {
    if ( l == r ) {
      dat[id] = arr[ l ];
      return;
    }
    int mid = ( l+r ) / 2;
    init( id*2 , l , mid , arr );
    init( id*2+1 , mid+1 , r , arr );
    dat[ id ] = max( dat[ id*2 ] , dat[ id*2+1 ] );
  }
  int qry( int id , int l , int r , int a , int b ) {
    if ( b < l || r < a ) return -MAXN;
    if ( a <= l && r <= b ) return dat[ id ];
    int mid = ( l+r ) / 2;
    int r1 = qry( id*2 , l , mid , a , b );
    int r2 = qry( id*2+1 , mid+1 , r , a , b );
    return max( r1 , r2 );
  }
};

min_SEG mnsg;
max_SEG mxsg;

void predo() {
  scanf( "%d" , &n );
  for ( int i = 1 ; i <= n ; i++ ) scanf( "%d" , A+i );
  for ( int i = 1 ; i <= n ; i++ ) {
    L[ 0 ][ i ] = max( 1 , i-A[i] );
    R[ 0 ][ i ] = min( n , i+A[i] );
  }
  //puts( "predo" );
  for( int k = 0 ; k < LOG-1 ; k++ ) {
    mnsg.init( 1 , 1 , n , L[ k ] );
    mxsg.init( 1 , 1 , n , R[ k ] );
    for ( int i = 1 ; i <= n ; i++ ) {
      L[ k+1 ][ i ] = mnsg.qry( 1 , 1 , n , L[ k ][ i ] , R[ k ][ i ] );
      R[ k+1 ][ i ] = mxsg.qry( 1 , 1 , n , L[ k ][ i ] , R[ k ][ i ] );
   //   printf( "  %d %d [%d %d]\n" , k+1 , i , L[ k+1 ][ i ] , R[ k+1 ][ i ] );
    }
  }
  //puts( "predo done" );
}

int cL[ MAXN ] , cR[ MAXN ];
int tL[ MAXN ] , tR[ MAXN ];

int ord[ MAXN ];

bool DC( int l , int r ) {
  //printf( "DC %d %d\n" , l , r );
  if ( l >= r ) return 0;
  int mid = ( l+r ) / 2;
  if ( DC( l , mid ) ) return 1;
  if ( DC( mid+1 , r ) ) return 1;

  int id = -1 , j = r;

  for ( int ii = l ; ii <= mid ; ii++ ) {
    int i = ord[ ii ];
    while( j > tR[ i ] && j >= mid+1 ) {
      if ( id == -1 || tL[ id ] < tL [ j ] ) id = j;
      j--;
    }
    if ( id != -1 ) {
      if ( i < tL[ id ] ) {
        //printf( "!! %d %d [%d, %d] [%d, %d]\n" , i , id , tL[ i ] , tR[ i ] , tL[ id ] , tR[ id ] );
        return 1;
      }
    }
  }

  inplace_merge( ord+l , ord+mid+1 , ord+r+1 , [&]( int a , int b ) {
         return tR[ a ] > tR[ b ];
  } );
  return 0;
}

inline bool check( int step , int lg ) {
  //printf( "chk %d %d\n" , step , lg );
  mnsg.init( 1 , 1 , n , L[ lg ] );
  mxsg.init( 1 , 1 , n , R[ lg ] );
  for ( int i = 1 ; i <= n ; i++ ) {
    tL[ i ] = mnsg.qry( 1 , 1 , n , cL[ i ] , cR[ i ] );
    tR[ i ] = mxsg.qry( 1 , 1 , n , cL[ i ] , cR[ i ] );
  }
  for ( int i = 1 ; i <= n ; i++ ) ord[ i ] = i;
  bool res = DC( 1 , n );
  return res;
}

void solve() {
  int cur = 0;
  for ( int i = 1 ; i <= n ; i++ ) cL[ i ] = cR[ i ] = i;
  for( int i = LOG-1 ; i >= 0 ; i-- ) {
    if ( check( cur + ( 1<<i ) , i ) ) {
      copy( tL+1 , tL+1+n , cL+1 );
      copy( tR+1 , tR+1+n , cR+1 );
      cur += ( 1<<i ); 
    }
  }
  printf( "%d\n" , cur+1 );
}

int main() {
  predo();
  solve();
}
