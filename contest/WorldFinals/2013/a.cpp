#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 40404
vector<int> read(){
  string ss; cin >> ss;
  vector<int> v;
  for( int i = 0 ; i < 8 ; i += 2 ){
    if( ss[ i ] == '0' ){
      v.push_back( 0 );
      continue;
    }
    v.push_back( (ss[ i ] - 'A' + 1) * 2 + (ss[ i + 1 ] == '+') );
  }
  return v;
}
vector<int> nxt[ 100 ];
int n ,ind[ 100 ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    vector<int> v = read();
    for( int x = 0 ; x < 4 ; x ++ ){
      if( v[ x ] == 0 ) continue;
      for( int y = 0 ; y < 4 ; y ++ ){
        if( v[ y ] == 0 ) continue;
        if( x == y ) continue;
        nxt[ v[ x ] ^ 1 ].push_back( v[ y ] );
      }
    }
  }
  for( int i = 2 ; i < 54 ; i ++ ){
    sort( nxt[ i ].begin() , nxt[ i ].end() );
    nxt[ i ].resize( unique( nxt[ i ].begin() , nxt[ i ].end() ) - nxt[ i ].begin() );
    for( int x : nxt[ i ] )
      ind[ x ] ++;
  }
  queue<int> Q;
  for( int i = 2 ; i < 54 ; i ++ )
    if( ind[ i ] == 0 )
      Q.push( i );
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    for( int x : nxt[ tn ] ){
      ind[ x ] --;
      if( ind[ x ] == 0 )
        Q.push( x );
    }
  }
  for( int i = 2 ; i < 54 ; i ++ )
    if( ind[ i ] ){
      puts( "unbounded" );
      exit(0);
    }
  puts( "bounded" );
}
