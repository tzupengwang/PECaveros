#include <bits/stdc++.h>
using namespace std;
#define N 2021
typedef double type;
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
void scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
int k , m , n;
Pt s[ N ] , r[ N ];
vector< pair<int,int> > e[ N ];
void init(){
  scanf( "%d%d%d" , &k , &m , &n );
  for( int i = 1 ; i <= k ; i ++ )
    scan( s[ i ] );
  for( int i = 1 ; i <= k + n ; i ++ )
    e[ i ].clear();
  for( int i = 0 ; i < m ; i ++ ){
    int w , u , v;
    scanf( "%d%d%d" , &w , &u , &v );
    if( u < 0 ) u = abs( u );
    else u += k;
    if( v < 0 ) v = abs( v );
    else v += k;
    e[ u ].push_back( { v , w } );
    e[ v ].push_back( { u , w } );
  }
  for( int i = k + 1 ; i <= k + n ; i ++ )
    s[ i ] = { 0 , 0 };
}
int _cs = 0;
#define K 1021
inline type cost( int i , Pt np ){
  Pt dlt = { 0 , 0 };
  for( auto u : e[ i ] ){
    Pt force = ( s[ u.first ] - np ) * u.second;
    dlt = dlt + force;
  }
  return dlt * dlt;
}
type dx[]={0,1,1,1,0,-1,-1,-1};
type dy[]={1,1,0,-1,-1,-1,0,1};
void solve(){
  type rr = 1e4;
  for( int _ = 0 ; _ < K ; _ ++ ){
    for( int i = k + 1 ; i <= k + n ; i ++ ){
      r[ i ] = s[ i ];
      type ncost = cost( i , s[ i ] );
      for( int j = 0 ; j < 8 ; j ++ ){
        Pt tt = s[ i ] + make_pair( dx[ j ] * rr , dy[ j ] * rr );
        type cc = cost( i , tt );
        if( cc < ncost ){
          r[ i ] = tt;
          ncost = cc;
        }
      }
    }
    rr *= 0.95;
    for( int i = k + 1 ; i <= k + n ; i ++ )
      s[ i ] = r[ i ];
  }
  printf( "Test case number : %d\n" , ++ _cs );
  for( int i = k + 1 ; i <= k + n ; i ++ )
    printf( "%d %.2f %.2f\n" , i - k , s[ i ].X , s[ i ].Y );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
