#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
LL ori( const Pt& o , const Pt& a , const Pt& b ){
  LL ret = ( a - o ) ^ ( b - o );
  return ret / max( 1ll , abs( ret ) );
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const Pt& p1 , const Pt& p2 ,
             const Pt& q1 , const Pt& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    return false;
    if( ori( p1 , p2 , q1 ) ) return false;
    return ( ( p1 - q1 ) * ( p2 - q1 ) ) <= 0 ||
           ( ( p1 - q2 ) * ( p2 - q2 ) ) <= 0 ||
           ( ( q1 - p1 ) * ( q2 - p1 ) ) <= 0 ||
           ( ( q1 - p2 ) * ( q2 - p2 ) ) <= 0;
  }
  return ( ori( p1 , p2 , q1 ) * ori( p1 , p2, q2 ) < 0 ) &&
         ( ori( q1 , q2 , p1 ) * ori( q1 , q2, p2 ) < 0 );
}
void scan( Pt& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
#define N 1021
LL n , w , l;
Pt p[ N ] , p2[ N ];
void init(){
  scanf( "%lld" , &n ); n ++;
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  scanf( "%lld" , &w );
  for( int i = 0 ; i < n ; i ++ )
    p2[ i ] = p[ i ] + Pt( 0 , w );
  l = p[ n - 1 ].X;
}
const double eps = 1e-7;
inline bool okay( Pt tp1 , Pt tp2 , int i , int j ){
  for( int k = i ; k <= j ; k ++ ){
    Pt dlt = tp2 - tp1;
    double yy = (double)dlt.Y * ( p[ k ].X - tp1.X ) / dlt.X + tp1.Y;
    if( yy < p[ k ].Y - eps || yy > p2[ k ].Y + eps )
      return false;
  }
  return true;
  // for( int i = 1 ; i < n ; i ++ )
    // if( banana( tp1 , tp2 , p[ i - 1 ] , p[ i ] ) )
      // return false;
  // for( int i = 1 ; i < n ; i ++ )
    // if( banana( tp1 , tp2 , p2[ i - 1 ] , p2[ i ] ) )
      // return false;
  // return true;
}
map< Pt , int > M;
int mcnt;
vector< pair< int , double > > v[ N ];
Pt who[ N ];
void add_node( const Pt& tp ){
  if( M.count( tp ) ) return;
  who[ mcnt ] = tp;
  M[ tp ] = mcnt ++;
}
double ans , d[ N ][ N ];
void add_edge( int ui , int vi , double dst ){
  d[ ui ][ vi ] = d[ vi ][ ui ] = dst;
}
void sp(){
  for( int k = 0 ; k < mcnt ; k ++ )
    for( int i = 0 ; i < mcnt ; i ++ )
      for( int j = 0 ; j < mcnt ; j ++ )
        d[ i ][ j ] = min( d[ i ][ j ] , d[ i ][ k ] + d[ k ][ j ] );
  ans = 1e23;
  for( int i = 0 ; i < mcnt ; i ++ )
    if( who[ i ].X == 0 )
      for( int j = 0 ; j < mcnt ; j ++ )
        if( who[ j ].X == l )
          ans = min( ans , d[ i ][ j ] );
  printf( "%.9f\n" , ans );
}
void solve(){
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      d[ i ][ j ] = 1e23;
  for( int i = 0 ; i < n ; i ++ )
    add_node( p[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    add_node( p2[ i ] );
  for( int i = 0 ; i < n ; i ++ ){
    Pt tmp = { 0 , p[ i ].Y };
    if( okay( tmp , p[ i ] , 0 , i ) &&
        p[ 0 ].Y <= tmp.Y && tmp.Y <= p2[ 0 ].Y ){
      add_node( tmp );
      add_edge( M[ p[ i ] ] , M[ tmp ] , norm( p[ i ] - tmp ) );
    }
    tmp = { l , p[ i ].Y };
    if( okay( p[ i ] , tmp , i , n - 1 ) &&
        p[ n - 1 ].Y <= tmp.Y && tmp.Y <= p2[ n - 1 ].Y ){
      add_node( tmp );
      add_edge( M[ p[ i ] ] , M[ tmp ] , norm( p[ i ] - tmp ) );
    }
  }
  for( int i = 0 ; i < n ; i ++ ){
    Pt tmp = { 0 , p2[ i ].Y };
    if( okay( tmp , p2[ i ] , 0 , i ) &&
        p[ 0 ].Y <= tmp.Y && tmp.Y <= p2[ 0 ].Y ){
      add_node( tmp );
      add_edge( M[ p2[ i ] ] , M[ tmp ] , norm( p2[ i ] - tmp ) );
    }
    tmp = { l , p2[ i ].Y };
    if( okay( p2[ i ] , tmp , i , n - 1 ) &&
        p[ n - 1 ].Y <= tmp.Y && tmp.Y <= p2[ n - 1 ].Y ){
      add_node( tmp );
      add_edge( M[ p2[ i ] ] , M[ tmp ] , norm( p2[ i ] - tmp ) );
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ ){
      if( i == j ||
          ( i < j && okay( p[ i ] , p2[ j ] , i , j ) ) ||
          ( i > j && okay( p2[ j ] , p[ i ] , j , i ) ) )
        add_edge( M[ p[ i ] ] , M[ p2[ j ] ] , norm( p[ i ] - p2[ j ] ) );
    }
  for( int i = 0 ; i + 1 < n ; i ++ ){
    add_edge( M[ p[ i ] ] , M[ p[ i + 1 ] ] , norm( p[ i ] - p[ i + 1 ] ) );
    Pt pre = p[ i + 1 ];
    for( int j = i + 2 ; j < n ; j ++ ){
      LL ret = ( p[ j ] - p[ i ] ) ^ ( pre - p[ i ] );
      if( ret < 0 ){
        if( okay( p[ i ] , p[ j ] , i , j ) )
          add_edge( M[ p[ i ] ] , M[ p[ j ] ] , norm( p[ i ] - p[ j ] ) );
        pre = p[ j ];
      }
    }
  }
  for( int i = 0 ; i + 1 < n ; i ++ ){
    add_edge( M[ p2[ i ] ] , M[ p2[ i + 1 ] ] , norm( p2[ i ] - p2[ i + 1 ] ) );
    Pt pre = p2[ i + 1 ];
    for( int j = i + 2 ; j < n ; j ++ ){
      LL ret = ( p2[ j ] - p2[ i ] ) ^ ( pre - p2[ i ] );
      if( ret > 0 ){
        if( okay( p2[ i ] , p2[ j ] , i , j ) )
          add_edge( M[ p2[ i ] ] , M[ p2[ j ] ] , norm( p2[ i ] - p2[ j ] ) );
        pre = p2[ j ];
      }
    }
  }
  sp();
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "race.in" , "r" , stdin );
  freopen( "race.out" , "w" , stdout );
#endif
  init();
  solve();
}
