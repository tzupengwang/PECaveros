#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , m , cnt[ N ] , ind[ N ];
vector< int > e[ N ] , v[ N ];
void init(){
  scanf( "%d" , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    cnt[ i ] = ind[ i ] = 0;
    e[ i ].clear();
    v[ i ].clear();
  }
  while( m -- ){
    int ui , vi; scanf( "%d%d" , &ui , &vi );
    e[ ui ].push_back( vi );
    ind[ vi ] ++;
  }
}
int tag[ N ] , stmp , ccnt;
void gogo( int now ){
  if( tag[ now ] == stmp ) return;
  tag[ now ] = stmp;
  ccnt ++;
  for( int x : e[ now ] )
    gogo( x );
}
inline int go( int st ){
  ++ stmp; ccnt = 0;
  gogo( st );
  return ccnt;
}
void solve(){
  queue< int > Q;
  for( int i = 1 ; i <= n ; i ++ )
    if( ind[ i ] == 0 ){
      v[ i ].push_back( i );
      Q.push( i );
    }
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    int bst = 0;
    for( size_t i = 1 ; i < v[ tn ].size() ; i ++ )
      if( cnt[ v[ tn ][ i ] ] > cnt[ v[ tn ][ bst ] ] )
        bst = i;
    int got = v[ tn ][ bst ];
    cnt[ got ] ++;
    for( int x : e[ tn ] ){
      v[ x ].push_back( got );
      ind[ x ] --;
      if( ind[ x ] == 0 )
        Q.push( x );
    }
  }
  vector< pair<int,int> > vv;
  for( int i = 1 ; i <= n ; i ++ )
    if( cnt[ i ] )
      vv.push_back( { cnt[ i ] , i } );
  sort( vv.begin() , vv.end() );
  reverse( vv.begin() , vv.end() );
  int id = -1 , mx = -1;
  for( int i = 0 ; i < min( (int)vv.size() , 2 ) ; i ++ ){
    int ret = go( vv[ i ].second );
    if( ret > mx ){
      mx = ret;
      id = vv[ i ].second;
    }
  }
  printf( "%d %d\n" , id , mx );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "journey.in" , "r" , stdin );
  freopen( "journey.out" , "w" , stdout );
#endif
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
