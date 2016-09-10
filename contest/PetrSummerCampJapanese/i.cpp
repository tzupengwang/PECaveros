#include <bits/stdc++.h>
using namespace std;
#define N 10101
typedef double type;
typedef long long LL;
typedef pair<LL,LL> PLL;
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
LL operator*( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
LL operator^( const PLL& p1 , const PLL& p2 ){
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
void scan( PLL& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
vector<PLL> p , ch;
void ConvexHull( vector<PLL>& tp ){
  ch.clear();
  int sz = 0 , psz = 1;
  sort( tp.begin() , tp.end() );
  for( int _ = 0 ; _ < 2 ; _ ++ ){
    for( size_t i = 0 ; i < tp.size() ; i ++ ){
      while( sz > psz && ( ( ch[ sz - 1 ] - ch[ sz - 2 ] ) ^
                           ( tp[ i ] - ch[ sz - 1 ] ) ) <= 0 ){
        sz --;
        ch.pop_back();
      }
      ch.push_back( tp[ i ] );
      sz ++;
    }
    psz = sz;
    reverse( tp.begin() , tp.end() );
  }
}
int n;
void init(){
  p.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
}
double cal( const PLL& p1 , const PLL& p2 ){
#define INF (1LL << 62)
  LL c1 = INF , c2 = -INF , d1 = INF , d2 = -INF;
  PLL tp = p2 - p1;
  PLL tp2 = perp( tp );
  for( int i = 0 ; i < n ; i ++ ){
    LL v1 = tp * p[ i ];
    LL v2 = tp2 * p[ i ];
    c1 = min( c1 , v1 );
    c2 = max( c2 , v1 );
    d1 = min( d1 , v2 );
    d2 = max( d2 , v2 );
  }
  double h = ( c2 - c1 ) / sqrt( tp * tp );
  double w = ( d2 - d1 ) / sqrt( tp2 * tp2 );
  return h * w;
}
void solve(){
  ConvexHull( p );
  double ans = 1e40;
  if( (int)p.size() <= 2 ) ans = 0;
  for( size_t i = 0 ; i + 1 < ch.size() ; i ++ )
    ans = min( ans , cal( ch[ i ] , ch[ i + 1 ] ) );
  printf( "%.3f\n" , ans );
}
int main(){
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
