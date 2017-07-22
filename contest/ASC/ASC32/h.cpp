#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 222
void imp(){
  puts( "-1" );
  exit(0);
}
int ans[ N ][ N ];
int n , m , d;
int cc[ N ];
vector<int> v[ N ];
int inq[ N ][ N ] , stmp;
int tg[ N ][ N ][ N ];
void go( int ui , int vi ){
  ++ stmp;
  queue< pair<int,int> > que;
  que.push( { ui , vi } );
  while( que.size() ){
    tie(ui, vi) = que.front(); que.pop();
    ans[ ui ][ vi ] = 0;
    ans[ vi ][ ui ] = 0;
    for( int i = 1 ; i <= d + 1 ; i ++ )
      cc[ i ] = 0;
    for( auto i : v[ ui ] )
      if( ans[ ui ][ i ] )
        cc[ ans[ ui ][ i ] ] ++;
    for( auto i : v[ vi ] )
      if( ans[ vi ][ i ] )
        cc[ ans[ vi ][ i ] ] ++;
    vector< pair<int,int> > vv;
    for( int i = 1 ; i <= d + 1 ; i ++ )
      vv.push_back( { cc[ i ] , i } );
    sort( vv.begin() , vv.end() );
    for( auto i : vv ){
      if( tg[ ui ][ vi ][ i.second ] == stmp )
        continue;
      tg[ ui ][ vi ][ i.second ] = stmp;
      ans[ ui ][ vi ] =
      ans[ vi ][ ui ] = i.second;
      //printf( "%d %d : %d\n" , ui , vi , i.second );
      for( auto ii : v[ ui ] )
        if( ans[ ii ][ ui ] == i.second ){
          if( inq[ ii ][ ui ] == stmp ) imp();
          inq[ ii ][ ui ] = stmp;
          ans[ ii ][ ui ] =
          ans[ ui ][ ii ] = 0;
          que.push( { ii , ui } );
        }
      for( auto ii : v[ vi ] )
        if( ans[ ii ][ vi ] == i.second ){
          if( inq[ ii ][ vi ] == stmp ) imp();
          inq[ ii ][ vi ] = stmp;
          ans[ ii ][ vi ] =
          ans[ vi ][ ii ] = 0;
          que.push( { ii , vi } );
        }
      break;
    }
  }
}
int a[ 2222 ] , b[ 2222 ];
int main(){
#ifdef ONLINE_JUDGE
  freopen( "roadsigns.in" , "r" , stdin );
  freopen( "roadsigns.out" , "w" , stdout );
#endif
  cin >> n >> m >> d;
  for( int i = 0 ; i < m ; i ++ ){
    cin >> a[ i ] >> b[ i ];
    go( a[ i ] , b[ i ] );
    v[ a[ i ] ].push_back( b[ i ] );
    v[ b[ i ] ].push_back( a[ i ] );
  }
  for( int i = 0 ; i < m ; i ++ )
    printf( "%d%c" , ans[ a[ i ] ][ b[ i ] ] , " \n"[ i + 1 == m ] );
}
