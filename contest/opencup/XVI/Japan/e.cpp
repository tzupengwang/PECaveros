#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL
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
void scan( Pt& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
int n , m , q;
Pt p[ N ];
vector<int> v[ N ];
void init(){
  scanf( "%d%d%d" , &n , &m , &q );
  for( int i = 1 ; i <= n ; i ++ )
    scan( p[ i ] );
  while( m -- ){
    int ui, vi; scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
}
int bs;
int region( const Pt& pp ){
  if( pp.Y == 0 ){
    if( pp.X < 0 ) return 0;
    return 1;
  }
  if( pp.Y < 0 ) return 0;
  return 1;
}
bool cmp( int i1 , int i2 ){
  Pt p1 = p[ i1 ] - p[ bs ];
  Pt p2 = p[ i2 ] - p[ bs ];
  int r1 = region( p1 );
  int r2 = region( p2 );
  if( r1 != r2 ) return r1 < r2;
  return ( p[ i1 ] ^ p[ i2 ] ) < 0;
}
map<int,int> at[ N ];
vector<  >
void pre_solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    bs = i;
    sort( v[ i ].begin() , v[ i ].end() , cmp );
    for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
      at[ i ][ v[ i ][ j ] ] = j;
  }
  
}
void solve(){
  pre_solve();
}
int main(){
  init();
  solve();
}
