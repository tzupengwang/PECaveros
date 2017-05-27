#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
inline int getint(){
  int _x=0; char _tc=getchar();    
  while( _tc<'0'||_tc>'9' ) _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
int n , m;
#define N 10010
bool tg[ N ][ N ];
vector<int> v[ N ];
int ans;
const int mxd = N;
vector< pair<int,int> > wt;
void go( int a , int b , int d ){
  if( not tg[ a ][ b ] ){
    tg[ a ][ b ] = true;
    ans ++;
  }
  if( d >= mxd ){
    wt.push_back( { a , b } );
    return;
  }
  for( int aa : v[ a ] )
    if( not tg[ aa ][ b ] )
      go( aa , b , d + 1 );
  for( int bb : v[ b ] )
    if( not tg[ a ][ bb ] )
      go( a , bb , d + 1 );
}
int main(){
  n = getint();
  m = getint();
  //n = 10000;
  //m = 10000;
  for( int i = 0 ; i < m ; i ++ ){
    int ui , vi;
    ui = getint();
    vi = getint();
    //ui = 1;
    //vi = i + 1;
    if( ui == vi ) continue;
    v[ ui ].push_back( vi );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    sort( v[ i ].begin() , v[ i ].end() );
    v[ i ].resize( unique( v[ i ].begin() , v[ i ].end() ) - v[ i ].begin() );
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( not tg[ i ][ i ] )
      go( i , i , 0 );
  while( wt.size() ){
    auto pp = wt.back();
    wt.pop_back();
    go( pp.first , pp.second ,0 );
  }
  printf( "%d\n" , ans );
}
