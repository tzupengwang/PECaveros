#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1000001
vector< pair<int,pair<int,int>> > cand;
const short inf = 1021;
short dp[ 321 ][ N ];
void build(){
  for( LL i = 2 ; ; i ++ ){
    LL cc = i * (i + 1) * (i + i + 1) / 6;
    if( cc >= N ) break;
    cand.push_back( { cc , { -i , 1 } } );
  }
  for( LL i = 2 ; ; i ++ ){
    LL cc = (i + i) * (i + 1) * (i + i + 1) / 3;
    if( cc >= N ) break;
    cand.push_back( { cc , { -i - i , 2 } } );
  }
  for( LL i = 1 ; ; i ++ ){
    LL cc = (i + 1) * (i + i + 1) * (i + i + 3) / 3;
    if( cc >= N ) break;
    cand.push_back( { cc , { -i - i - 1 , 2 } } );
  }
  sort( cand.begin() , cand.end() );
  for( size_t i = 0 ; i <= cand.size() ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      dp[ i ][ j ] = inf;
  dp[ 0 ][ 0 ] = 0;
  for( size_t i = 0 ; i < cand.size() ; i ++ ){
    for( int j = 0 ; j < N ; j ++ )
      dp[ i + 1 ][ j ] = dp[ i ][ j ];
    for( int j = 0 ; j + cand[ i ].first < N ; j ++ )
      if( dp[ i ][ j ] + 1 < dp[ i + 1 ][ j + cand[ i ].first ] )
        dp[ i + 1 ][ j + cand[ i ].first ] = dp[ i ][ j ] + 1;

  }
  //for( int i = 1 ; i < N ; i ++ )
    //dp[ i ] = N;
  //for( size_t i = 0 ; i < cand.size() ; i ++ )
    //for( int j = N - 1 - cand[ i ].first ; j >= 0 ; j -- )
      //if( dp[ j ] + 1 < dp[ j + cand[ i ].first ] ){
        //dp[ j + cand[ i ].first ] = dp[ j ] + 1;
        //bk[ j + cand[ i ].first ] = j;
        //who[ j + cand[ i ].first ] = cand[ i ].second.first * -2 +
                                     //cand[ i ].second.second - 1;
      //}
  //int ans = 0;
  //for( int i = 1 ; i < N ; i ++ )
    //ans += dp[ i ];
  //cout << ans << endl;
}
int _cs;
//void go( int now ){
  //if( !now ) return;
  //go( bk[ now ] );
  //printf( " %d%c" , who[ now ] >> 1 , "HL"[ who[ now ] & 1 ] );
//}
int main(){
  build();
  int c; while( scanf( "%d" , &c ) == 1 and c ){
    printf( "Case %d:" , ++ _cs );
    if( dp[ cand.size() ][ c ] == inf ) puts( " impossible" );
    else{
      int ni = cand.size();
      while( ni and c ){
        if( c >= cand[ ni - 1 ].first and
            dp[ ni - 1 ][ c - cand[ ni - 1 ].first ] + 1 ==
            dp[ ni ][ c ] ){
          printf( " %d%c" ,
                  -cand[ ni - 1 ].second.first ,
                  "HL"[ cand[ ni - 1 ].second.second - 1 ] );
          c -= cand[ ni - 1 ].first;
        }
        ni --;
      }
      puts( "" );
    }
  }
}
