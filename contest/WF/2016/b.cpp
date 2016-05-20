//by tzupengwang™
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int n , b , s , r ;
vector< ii > vs[ 5005 ] ;
vector< ii > vt[ 5005 ] ;
int ds[ 5005 ] , dt[ 5005 ] ;
priority_queue< ii , vector< ii > , greater< ii > > pq ;

void shortest() {
  memset( ds , -1 , sizeof ds ) ;
  memset( dt , -1 , sizeof dt ) ;

  while ( !pq.empty() ) pq.pop() ;
  pq.push( ii( 0 , b + 1 ) ) ;
  while ( !pq.empty() ) {
    int nw , dis ;
    tie( dis , nw ) = pq.top() ; pq.pop() ;

    if ( ds[ nw ] != -1 ) continue ;
    ds[ nw ] = dis ;

    for ( ii tp : vs[ nw ] ) if ( ds[ tp.first ] == -1 ) {
      int nxt , cst ;
      tie( nxt , cst ) = tp ;
      pq.push( ii( dis + cst , nxt ) ) ;
    }
  }

  while ( !pq.empty() ) pq.pop() ;
  pq.push( ii( 0 , b + 1 ) ) ;
  while ( !pq.empty() ) {
    int nw , dis ;
    tie( dis , nw ) = pq.top() ; pq.pop() ;

    if ( dt[ nw ] != -1 ) continue ;
    dt[ nw ] = dis ;

    for ( ii tp : vt[ nw ] ) if ( dt[ tp.first ] == -1 ) {
      int nxt , cst ;
      tie( nxt , cst ) = tp ;
      pq.push( ii( dis + cst , nxt ) ) ;
    }
  }
}

void init() {
  scanf( "%d%d%d%d" , &n , &b , &s , &r ) ;
  for ( int i = 0 , x , y , z ; i < r ; i ++ ) {
    scanf( "%d%d%d" , &x , &y , &z ) ;
    vs[ x ].emplace_back( y , z ) ;
    vt[ y ].emplace_back( x , z ) ;
  }
  shortest() ;
}

vector< int > v ;
ll pre[ 5005 ] ;
ll dp[ 5005 ][ 5005 ] ;

void DP( int l , int r , int vl , int vr , int j ) {
  if ( l > r ) return ;
  int i = ( l + r ) / 2 ;
  int lb = max( j - 1 , vl ) , rb = min( i - 1 , vr ) ;
  int bst = lb ; ll val = dp[ i ][ j - 1 ] ;
  for ( int ip = lb ; ip <= rb ; ip ++ ) {
    ll tcst = dp[ ip ][ j - 1 ] + (ll)( i - ip - 1 ) * ( pre[ i ] - pre[ ip ] ) ;
    if ( tcst <= val ) {
      val = tcst , bst = ip ;
    }
  }
  dp[ i ][ j ] = val ;
  DP( l , i - 1 , vl , bst , j ) ;
  DP( i + 1 , r , bst , vr , j ) ;
}

void process() {
  int ans = 0 ;
  for ( int i = 1 ; i <= b ; i ++ ) {
    if ( ds[ i ] == -1 || dt[ i ] == -1 ) s -- ;
    else v.push_back( ds[ i ] + dt[ i ] ) ;
  }
  assert( s > 0 ) ;
  v.push_back( -1 ) ;
  sort( v.begin() , v.end() ) ;
  pre[ 0 ] = 0 ;
  for ( int i = 1 ; i < (int)v.size() ; i ++ ) pre[ i ] = pre[ i - 1 ] + v[ i ] ;
  for ( int i = 1 ; i < (int)v.size() ; i ++ ) dp[ i ][ 1 ] = ( i - 1 ) * pre[ i ] ;
  for ( int j = 2 ; j <= s ; j ++ )
    DP( j , v.size() - 1 , 1 , v.size() - 1 , j ) ;
  printf( "%lld\n" , dp[ (int)v.size() - 1 ][ s ] ) ;
}

int main() {
  init() ;
  process() ;
  return 0 ;
}

