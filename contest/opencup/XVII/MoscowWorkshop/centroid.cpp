#include<bits/stdc++.h>
using namespace std;

typedef pair< int , long long > ii;
const int N = 100005 ;
inline void maxify( int &x , int y ) { x = max( x , y ) ; }

vector< ii > adj[ N ] ;
int p[ N ] ;
int vis[ N ] ;
int sz[ N ] , M[ N ] ; // subtree size of u and M(u)

struct node { // single node on the path
  int now , nxt ;
  long long dis ;
  node() {}
  node( int x , int y , long long z )
    : now( x ) , nxt( y ) , dis( z ) {}
} ;
vector< node > path[ N ] ;

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
        int nxt = pr.first ;
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
  int centroid ;
  for ( int &nd : q )
    if ( M[ nd ] + M[ nd ] <= (int)q.size() )
      centroid = nd ;

  // path[ nd ] stores the nodes on the path from the root
  // to "nd" on the centroid tree
  // struct node( now , nxt , dis )
  for ( int &nd : q ) {
    if ( path[ nd ].size() )
      path[ nd ].back().nxt = centroid ;
    path[ nd ].emplace_back( centroid , -1 , 0 ) ;
  }

  { // bfs from centroid to compute distance from all
    // nodes to the centroid, can also be done with LCA
    q.clear() ;
    size_t pt = 0 ;
    q.push_back( centroid ) ;
    p[ centroid ] = -1 ;
    while ( pt < q.size() ) {
      int now = q[ pt ++ ] ;
      long long ndis = path[ now ].back().dis ;
      for ( auto &pr : adj[ now ] ) {
        int nxt = pr.first ;
        long long cdis = pr.second ;
        if ( !vis[ nxt ] && nxt != p[ now ] ) {
          q.push_back( nxt ) , p[ nxt ] = now ;
          path[ nxt ].back().dis = ndis + cdis ;
        }
      }
    }
  }

  // decompose the tree recursively
  // set vis[ centroid ] = 1 to break the tree into forest
  vis[ centroid ] = 1 ;
  for ( auto &pr : adj[ centroid ] ) {
    int nxt = pr.first ;
    if ( !vis[ nxt ] ) centroidDecomp( nxt ) ;
  }
  return centroid ;
}



long long sum[ N ] ;
int tot[ N ] , cnt[ N ] ;
void mark( int x ) {
  for ( auto& nd : path[ x ] ) {
    int now = nd.now , nxt = nd.nxt ;
    long long dis = nd.dis ;
    sum[ now ] += dis ;
    tot[ now ] ++ ;
    if ( nxt != -1 ) {
      sum[ nxt ] -= dis ;
      cnt[ nxt ] ++ ;
    }
  }
}

long long query( int x ) {
  long long ret = 0 ;
  for ( auto& nd : path[ x ] ) {
    int now = nd.now , nxt = nd.nxt ;
    long long dis = nd.dis ;
    ret += sum[ now ] + dis * ( tot[ now ] - cnt[ nxt ] ) ;
  }
  return ret ;
}

int main() {
  int n , q ;
  scanf( "%d%d" , &n , &q ) ;
  for ( int i = 1 ; i < n ; i ++ ) {
    int a , b , c ;
    scanf( "%d%d%d" , &a , &b , &c ) ;
    adj[ a ].emplace_back( b , c ) ;
    adj[ b ].emplace_back( a , c ) ;
  }
  centroidDecomp( 0 ) ;
  while( q -- ) {
    int m , l ;
    scanf( "%d%d" , &m , &l ) ;
    if( m == 1 ) mark( l ) ;                // Mark a point
    else printf( "%lld\n" , query( l ) ) ;  // Query
  }
  return 0;
}
