#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , m , c[ N ] , indeg[ N ];
vector< int > v[ N ] , g[ N ] , g2[ N ];
void add_edge( int ui , int vi ){
  if( c[ ui ] < c[ vi ] ){
    g[ ui ].push_back( vi );
    indeg[ vi ] ++;
  }
  v[ ui ].push_back( vi );
}
bool cmp( int ui , int vi ){
  return c[ ui ] < c[ vi ];
}
void init(){
  cin >> n;
  for( int i = 1 ; i <= n ; i ++ )
    cin >> c[ i ];
  cin >> m; while( m -- ){
    int ui , vi;
    cin >> ui >> vi;
    add_edge( ui , vi );
    add_edge( vi , ui );
  }
  for( int i = 1 ; i <= n ; i ++ )
    sort( v[ i ].begin() , v[ i ].end() , cmp );
  for( int i = 1 ; i <= n ; i ++ ){
    for( size_t j = 1 ; j < v[ i ].size() ; j ++ ){
      if( c[ v[ i ][ j - 1 ] ] == c[ v[ i ][ j ] ] ){
        g2[ v[ i ][ j - 1 ] ].push_back( v[ i ][ j ] );
        indeg[ v[ i ][ j ] ] ++;
      }else{
        g[ v[ i ][ j - 1 ] ].push_back( v[ i ][ j ] );
        indeg[ v[ i ][ j ] ] ++;
      }
    }
  }
}
int cst[ N ] , dd[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    cst[ i ] = dd[ i ] = 1;
  queue<int> Q;
  for( int i = 1 ; i <= n ; i ++ )
    if( indeg[ i ] == 0 )
      Q.push( i );
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    for( auto nxt : g[ tn ] ){
      cst[ nxt ] = max( cst[ nxt ] , max( cst[ tn ] , dd[ tn ] ) + 1 );
      dd[ nxt ] = max( dd[ nxt ] , cst[ nxt ] );
      indeg[ nxt ] --;
      if( indeg[ nxt ] == 0 )
        Q.push( nxt );
    }
    for( auto nxt : g2[ tn ] ){
      dd[ nxt ] = max( dd[ nxt ] , max( cst[ tn ] , dd[ tn ] ) );
      indeg[ nxt ] --;
      if( indeg[ nxt ] == 0 )
        Q.push( nxt );
    }
  }
  long long ans = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    ans += cst[ i ];
    //cout << i << " " << cst[ i ] << endl;
  }
  cout << ans << endl;
}
int main(){
  init();
  solve();
}
