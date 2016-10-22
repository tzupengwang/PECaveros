#include <bits/stdc++.h>
using namespace std;
#define N 1021
bool p[ N ];
vector< int > pp;
int main(){
  for( int i = 2 ; i < N ; i ++ )
    if( !p[ i ] ){
      pp.push_back( i );
      for( int j = i + i ; j < N ; j += i )
        p[ j ] = true;
    }
  int t; scanf( "%d" , &t ); while( t -- ){
    int k; scanf( "%d" , &k );
    bool got = false;
    for( size_t i = 0 ; i < pp.size() && !got ; i ++ )
      for( size_t j = i ; j < pp.size() && !got ; j ++ ){
        if( pp[ i ] + pp[ j ] >= k ) break;
        int ret = k - pp[ i ] - pp[ j ];
        if( ret < 2 ) continue;
        if( p[ ret ] ) continue;
        vector< int > ans = { pp[ i ] , pp[ j ] , ret };
        sort( ans.begin() , ans.end() );
        for( size_t u = 0 ; u < ans.size() ; u ++ )
          printf( "%d%c" , ans[ u ] , " \n"[ u + 1 == ans.size() ] );
        got = true;
      }
    if( !got ) puts( "0" );
  }
}
