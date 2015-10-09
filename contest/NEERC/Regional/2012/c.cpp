#include <bits/stdc++.h>
using namespace std;
#define N 4010
#define K 50
int getint(){
  int _;
  scanf( "%d" , &_ );
  return _;
}
int m , n , k , smin , smax , cn;
char c[ 30 ][ K ][ K ];
char a1[ K ][ N ];
int trans( char ctmp ){
  if( ctmp == ' ' ) return 26;
  return ctmp - 'A';
}
void init(){
  m = getint();
  n = getint();
  k = getint();
  smin = getint();
  smax = getint();
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < k ; j ++ )
      c[ 26 ][ i ][ j ] = '.';
  char ctmp[ N ];
  vector<int> v;
  gets( ctmp );
  gets( ctmp );
  cn = (int)( strlen( ctmp ) + 1 ) / ( k + 3 );
  int len = strlen( ctmp );
  for( int i = 0 ; i < len ; i += k + 3 ){
    int tnum = trans( ctmp[ i ] );
    v.push_back( tnum );
    for( int j = 0 ; j < k ; j ++ )
      c[ tnum ][ 0 ][ j ] = ctmp[ i + 2 + j ];
  }
  for( int i = 1 ; i < m ; i ++ ){
    for( int ti = 0 ; ti < cn ; ti ++ ){
      scanf( "%s" , ctmp );
      for( int j = 0 ; j < k ; j ++ )
        c[ v[ ti ] ][ i ][ j ] = ctmp[ j ];
    }
  }
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      a1[ i ][ j ] = '.';
  char in[ N ];
  gets( in );
  gets( in );
  int tlen = strlen( in );
  int pre = 0;
  for( int i = 0 ; i < tlen ; i ++ ){
    int dlt = getint();
    pre += dlt;
    int num = trans( in[ i ] );
    for( int j = 0 ; j < m ; j ++ )
      for( int tk = 0 ; tk < k ; tk ++ )
        a1[ j ][ pre + tk ] = c[ num ][ j ][ tk ];
    pre += k;
  }
}
char out[ N ];
int on , dp[ K ][ N ] , bk[ K ][ N ];
bool got[ K ][ N ];
void DP( int pos , int lst ){
  if( got[ pos ][ lst ] ) return;
  got[ pos ][ lst ] = true;
  if( pos < 1 ){
    int tcnt = 0;
    for( int i = 0 ; i < m ; i ++ )
      for( int j = 0 ; j <= lst ; j ++ )
        if( a1[ i ][ j ] == '*' )
          tcnt ++;
    dp[ pos ][ lst ] = tcnt;
    return;
  }
  int ncst = 0;
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < k ; j ++ )
      if( c[ trans( out[ pos ] ) ][ i ][ j ] !=
          a1[ i ][ lst + j ] )
        ncst ++;
  if( pos > 1 ){
    int mcst = 1000000000 , fi = -1;
    int pren = ( pos - 2 ) * ( k + smin );
    for( int i = max( pren , lst - k - smax ) ;
             i <= lst - k - smin ; i ++ ){
      DP( pos - 1 , i );
      int tcst = 0;
      for( int j = 0 ; j < m ; j ++ )
        for( int tk = i + k ; tk < lst ; tk ++ )
          if( a1[ j ][ tk ] == '*' )
            tcst ++;
      if( dp[ pos - 1 ][ i ] + tcst < mcst ){
        mcst = dp[ pos - 1 ][ i ] + tcst;
        fi = i;
      }
    }
    dp[ pos ][ lst ] = ncst + mcst;
    bk[ pos ][ lst ] = fi;
    return;
  }else{
    DP( 0 , lst - 1 );
    dp[ pos ][ lst ] = ncst + dp[ 0 ][ lst - 1 ];
    return;
  }
}
deque<int> vans;
void find_ans( int now , int pos ){
  while( now ){
    if( now == 1 ){
      vans.push_front( pos );
      return;
    }else{
      assert( pos - bk[ now ][ pos ] );
      assert( pos - bk[ now ][ pos ] - k >= smin );
      assert( pos - bk[ now ][ pos ] - k <= smax );
      vans.push_front( pos - bk[ now ][ pos ] - k );
      pos = bk[ now ][ pos ];
      now --;
    }
  }
}
void solve(){
  gets( out + 1 );
  gets( out + 1 );
  on = strlen( out + 1 );
  for( int i = ( on - 1 ) * ( k + smin ) ; i <= n - k ; i ++ ){
    DP( on , i );
    for( int j = 0 ; j < m ; j ++ )
      for( int tk = i + k ; tk < n ; tk ++ )
        if( a1[ j ][ tk ] == '*' )
          dp[ on ][ i ] ++;
  }
  int ans = 1000000000 , ai = 0;
  for( int i = ( on - 1 ) * ( k + smin ) ; i <= n - k ; i ++ )
    if( dp[ on ][ i ] < ans )
      ans = dp[ on ][ i ], ai = i;
  find_ans( on , ai );
  for( int i = 0 ; i < on ; i ++ )
    printf( "%d%c" , vans[ i ] , " \n"[ i == on - 1 ] );
}
int main(){
  freopen( "caption.in" , "r" , stdin );
  freopen( "caption.out" , "w" , stdout );
  init();
  solve();
}
