#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 10
int k , m , n , e[ N ] , p[ N ];
int tg[ N ][ 111 ][ 111 ] , stmp;
int dp[ N ][ 111 ][ 111 ];
tuple<int,int,int> que[ N * 111 * 111 ];
int cal( const vector<int>& ord ){
  ++ stmp;
  tg[ 0 ][ 100 ][ 0 ] = stmp;
  dp[ 0 ][ 100 ][ 0 ] = 0;
  int qf = 0 , qt = 0;
  que[ qt ++ ] = make_tuple( 0 , 100 , 0 );
  int ret = 0;
  for( int _ = qf ; _ < qt ; _ ++ ){
    int nn = get<0>( que[ _ ] );
    int ee = get<1>( que[ _ ] );
    int pp = get<2>( que[ _ ] );
    int ndp = dp[ nn ][ ee ][ pp ];
    for( int gt = 1 ; gt * k < ee ; gt ++ ){
      ret = max( ret , ndp + gt );
      if( nn < n ){
        int ne = min( ee - gt * k + e[ ord[ nn ] ] , 100 );
        int np = max( 0 , pp - gt * m ) + p[ ord[ nn ] ];
        if( np >= 100 ) continue;
        if( tg[ nn + 1 ][ ne ][ np ] != stmp or
            ndp + gt > dp[ nn + 1 ][ ne ][ np ] ){
          dp[ nn + 1 ][ ne ][ np ] = ndp + gt;
          if( tg[ nn + 1 ][ ne ][ np ] != stmp ){
            tg[ nn + 1 ][ ne ][ np ] = stmp;
            que[ qt ++ ] = make_tuple( nn + 1 , ne , np );
          }
        }
      }
    }
  }
  return ret;
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    scanf( "%d%d%d" , &k , &m , &n );
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d" , &e[ i ] );
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d" , &p[ i ] );
    int ans = 0;
    vector<int> ord;
    for( int i = 0 ; i < n ; i ++ )
      ord.push_back( i );
    do ans = max( ans , cal( ord ) );
    while( next_permutation( ord.begin() , ord.end() ) );
    printf( "%d\n" , ans );
  }
}
