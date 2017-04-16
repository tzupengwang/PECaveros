#include <bits/stdc++.h>
using namespace std;
#define N 514
int n;
char c[ N ];
vector< tuple<int,int,int> > v;
vector< tuple<int,int,int> > v2;
int dp[ N * N ] , tdp[ N * N ];
int sdp[ N * N ];
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , c );
    int mn = 0 , bl = 0;
    int len = strlen( c );
    for( int j = 0 ; j < len ; j ++ ){
      if( c[ j ] == '(' ) bl ++;
      else bl --;
      mn = min( mn , bl );
    }
    if( bl >= 0 )
      v.push_back( make_tuple( mn , bl , len ) );
    else{
      mn = 0 , bl = 0;
      for( int j = len - 1 ; j >= 0 ; j -- ){
        if( c[ j ] == ')' ) bl ++;
        else bl --;
        mn = min( mn , bl );
      }
      v2.push_back( make_tuple( mn , bl , len ) );
    }
  }
  int ans = 0;
  for( int _ = 0 ; _ < 2 ; _ ++ ){
    if( _ == 1 ) v = v2;
    sort( v.begin() , v.end() );
    reverse( v.begin() , v.end() );
    int mx = 0;
#define inf 100000000
    dp[ 0 ] = 0;
    n = (int)v.size();
    //for( auto i : v )
      //printf( "%d %d %d\n" , get<0>( i ) ,get<1>( i ) ,get<2>( i ) );
    //printf( "%d\n" , n );
    //puts( "" );
    for( int i = 1 ; i < N * N ; i ++ )
      dp[ i ] = -inf;
    for( int i = 0 ; i < n ; i ++ ){
      for( int j = 0 ; j <= mx ; j ++ )
        tdp[ j ] = dp[ j ];
      for( int j = 0 ; j <= mx ; j ++ ){
        if( j + get<0>( v[ i ] ) < 0 )
          continue;
        int nj = j + get<1>( v[ i ] );
        dp[ nj ] = max( dp[ nj ] , tdp[ j ] + get<2>( v[ i ] ) );
      }
      mx += get<2>( v[ i ] );
    }
    if( _ == 0 )
      for( int i = 0 ; i <= mx ; i ++ )
        sdp[ i ] = dp[ i ];
  }
  //for( int i = 0 ; i <= 10 ; i ++ )
    //printf( "%d %d %d\n" , i , dp[ i ] , sdp[ i ] );
  ans = max( ans , max( dp[ 0 ] , sdp[ 0 ] ) );
  for( int i = 0 ; i < N * N ; i ++ )
    ans = max( ans , dp[ i ] + sdp[ i ] );
  printf( "%d\n" , max( 0 , ans ) );
}
