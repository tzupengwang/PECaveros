#include <bits/stdc++.h>
using namespace std;
#define N 1010
typedef unsigned int uint;

int n , t ;
vector< int > adj[ N ] ;

void init() {
  for ( int i = 1 ; i <= n ; i ++ ) adj[ i ].clear() ;
  for ( int i = 1 ; i < n ; i ++ ) {
    int x , y ;
    scanf( "%d%d" , &x , &y ) ;
    adj[ x ].push_back( y ) ;
    adj[ y ].push_back( x ) ;
  }
}

int p[ N ] ;
int vis[ N ] ;
int sz[ N ] , M[ N ] ; // subtree size of u and M(u)

inline void maxify( int &x , int y ) { x = max( x , y ) ; }
vector< int > centroidDecomp1( int x ) {
  // decompose the subtree and return the centroid
  vector< int > q ;
  { // bfs from arbitrary point to get bfs order for
    // later computation of subtree size and M(u)
    size_t pt = 0 ;
    q.push_back( x ) ;
    p[ x ] = -1 ;
    while ( pt < q.size() ) {
      int now = q[ pt ++ ] ;
      sz[ now ] = 1 ;
      M[ now ] = 0 ;
      for ( auto &pr : adj[ now ] ) {
        int nxt = pr ;
        if ( !vis[ nxt ] && nxt != p[ now ] ) {
          q.push_back( nxt ) , p[ nxt ] = now ;
        }
      }
    }
  }

  // calculate subtree size in reverse order
  reverse( q.begin() , q.end() ) ;
  for ( int& nd : q ) if ( p[ nd ] != -1 ) {
    sz[ p[ nd ] ] += sz[ nd ] ;
    maxify( M[ p[ nd ] ] , sz[ nd ] ) ;
  }
  for ( int& nd : q )
    maxify( M[ nd ] , (int)q.size() - sz[ nd ] ) ;

  // find centroid
  int mm = 1000000 ;
  for ( int &nd : q )
    if ( M[ nd ] < mm ) {
      mm = M[ nd ] ;
    }

  vector< int > ret ;
  for ( int &nd : q )
    if ( M[ nd ] == mm ) {
      ret.push_back( nd ) ;
    }
  return ret ;
}

bool good ;
int centroidDecomp( int x ) {
  // decompose the subtree and return the centroid
  vector< int > q ;
  { // bfs from arbitrary point to get bfs order for
    // later computation of subtree size and M(u)
    size_t pt = 0 ;
    q.push_back( x ) ;
    p[ x ] = -1 ;
    while ( pt < q.size() ) {
      int now = q[ pt ++ ] ;
      sz[ now ] = 1 ;
      M[ now ] = 0 ;
      for ( auto &pr : adj[ now ] ) {
        int nxt = pr ;
        if ( !vis[ nxt ] && nxt != p[ now ] ) {
          q.push_back( nxt ) , p[ nxt ] = now ;
        }
      }
    }
  }

  // calculate subtree size in reverse order
  reverse( q.begin() , q.end() ) ;
  for ( int& nd : q ) if ( p[ nd ] != -1 ) {
    sz[ p[ nd ] ] += sz[ nd ] ;
    maxify( M[ p[ nd ] ] , sz[ nd ] ) ;
  }
  for ( int& nd : q )
    maxify( M[ nd ] , (int)q.size() - sz[ nd ] ) ;

  // find centroid
  int centroid , mm = 1000000 ;
  for ( int &nd : q )
    if ( M[ nd ] < mm || ( M[ nd ] == mm && nd == x ) ) {
      centroid = nd ;
      mm = M[ nd ] ;
    }

  if ( centroid != x ) good = false ;

  // decompose the tree recursively
  // set vis[ centroid ] = 1 to break the tree into forest
  vis[ centroid ] = 1 ;
  for ( auto &pr : adj[ centroid ] ) {
    int nxt = pr;
    if ( !vis[ nxt ] ) centroidDecomp( nxt ) ;
  }
  return centroid ;
}

void process() {
  memset( vis , 0 , sizeof vis ) ;
  vector< int > cc = centroidDecomp1( 1 ) ;
  for ( int c : cc ) {
    memset( vis , 0 , sizeof vis ) ;
    good = true ;
    centroidDecomp( c ) ;
    if ( good ) {
      puts( "Centroid" ) ;
      return ;
    }
  }
  puts( "Random" ) ;
}

int main(){
  cin >> t >> n ;
  for ( int i = 0 ; i < t ; i ++ ) {
    init() ;
    process() ;
  }
}
