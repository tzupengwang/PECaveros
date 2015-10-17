#include <bits/stdc++.h>
using namespace std;
int __ = 1;
#define N 100010
int n , p[ N ] , dp[ N ][ 3 ];
int pr[ N ][ 3 ];
int got[ N ];
vector<int> v[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    v[ i ].clear();
    got[ i ] = 0;
  }
  for( int i = 1 ; i < n ; i ++ ){
    scanf( "%d" , &p[ i ] );
    v[ p[ i ] ].push_back( i );
  }
}
void add( int now , int son , int vl ){
  if( got[ now ] == 0 ){
    ++got[ now ];
    dp[ now ][ 1 ] = vl;
    pr[ now ][ 1 ] = son;
    return;
  }else if( vl > dp[ now ][ 1 ] ){
    swap( dp[ now ][ 1 ] , vl );
    swap( pr[ now ][ 1 ] , son );
  }
  if( got[ now ] == 1 ){
    ++got[ now ];
    dp[ now ][ 2 ] = vl;
    pr[ now ][ 2 ] = son;
    return;
  }else if( vl > dp[ now ][ 2 ] ){
    swap( dp[ now ][ 2 ] , vl );
    swap( pr[ now ][ 2 ] , son );
  }
}
void DP1( int now ){
  dp[ now ][ 0 ] = 0;
  dp[ now ][ 1 ] = 0;
  dp[ now ][ 2 ] = 0;
  int tsum = 0;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ ){
    DP1( v[ now ][ i ] );
    tsum += max( dp[ v[ now ][ i ] ][ 0 ],
                 dp[ v[ now ][ i ] ][ 1 ] );
  }
  dp[ now ][ 0 ] = tsum;
  int tans = tsum;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ ){
    int ttsum = tsum - max( dp[ v[ now ][ i ] ][ 0 ],
                            dp[ v[ now ][ i ] ][ 1 ] );
    ttsum += 1 + dp[ v[ now ][ i ] ][ 0 ];
    tans = max( tans , ttsum );
    add( now , v[ now ][ i ] , ttsum );
  }
  dp[ now ][ 1 ] = tans;
}
int fans;
vector<int> ans;
void DP2( int now , int fp0 , int fp1 ){
  if( dp[ now ][ 0 ] + max( fp0 , fp1 ) < fans ){
    ans.push_back( now );
  }
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ ){
    int son = v[ now ][ i ];
    int nf0 = max( fp0 , fp1 ) + dp[ now ][ 0 ] -
              max( dp[ son ][ 0 ] , dp[ son ][ 1 ] );
    int nvl1 = fp0 + ( now != 0 ) + dp[ now ][ 0 ] -
              max( dp[ son ][ 0 ] , dp[ son ][ 1 ] );
    nvl1 = max( nvl1 , nf0 );
    int nvl2 = 0;
    if( (int)v[ now ].size() > 1 ){
      for( int j = 1 ; j <= 2 ; j ++ )
        if( pr[ now ][ j ] != son )
          nvl2 = max( nvl2 , dp[ now ][ j ] );
      nvl2 = nvl2 - max( dp[ son ][ 0 ] , dp[ son ][ 1 ] );
      nvl2 += max( fp0 , fp1 );
    }
    DP2( son , nf0 , max( nvl1 , nvl2 ) );
   }
}
void solve(){
  ans.clear();
  DP1( 0 );
  fans = max( dp[ 0 ][ 0 ] , dp[ 0 ][ 1 ] );
  DP2( 0 , 0 , 0 );
  printf( "%d %d\n" , fans , (int)ans.size() );
  sort( ans.begin() , ans.end() );
  int _sz = (int)ans.size();
  for( int i = _sz - 1 , j = 0 ; i >= 0 && j < 3 ; i -- , j ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ j == 2 || i == 0 ] );
}
int main(){
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
