#include <bits/stdc++.h>
using namespace std;
#define N 2048
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
inline LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline void scan( Pt& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
int n;
Pt p[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
}
inline int reg( const Pt& p1 ){
  if( p1.Y < 0 || ( p1.Y == 0 && p1.X < 0 ) )
    return 0;
  return 1;
}
bool cmp( const Pt& p1 , const Pt& p2 ){
  if( reg( p1 ) != reg( p2 ) )
    return reg( p1 ) < reg( p2 );
  return ( p1 ^ p2 ) > 0;
}
inline LL C( LL x ){
  return x * ( x - 1 ) / 2;
}
inline pair< LL , LL > cal( int idx ){
  vector< Pt > v;
  for( int i = 0 ; i < n ; i ++ )
    if( i != idx )
      v.push_back( p[ i ] - p[ idx ] );
  sort( v.begin() , v.end() , cmp );
  LL tota = 0 , totb = 0;
  for( int i = 0 ; i < n - 1 ; i ++ )
    v.push_back( v[ i ] );
  int ptr = 0;
  for( int i = 0 ; i < n - 1 ; i ++ ){
    ptr = max( ptr , i + 1 );
    while( ( v[ i ] ^ v[ ptr ] ) > 0 ) ptr ++;
    LL aa = ptr - i - 1;
    LL bb = n - 2 - aa;
    tota += aa * bb;
    totb += C( aa ) + C( bb );
  }
  return { tota , totb };
}
void solve(){
  if( n == 3 ){
    puts( "0" );
    exit( 0 );
  }
  LL suma = 0 , sumb = 0;
  for( int i = 0 ; i < n ; i ++ ) {
    auto ret = cal( i );
    suma += ret.X;
    sumb += ret.Y;
    //printf( "%lld %lld\n"  ,ret.X , ret.Y );
  }
  suma >>= 1;
  sumb >>= 1;
  double y = ( sumb - suma ) / 2;
  double x = ( suma - 2 * y ) / 3;
  //printf( "%lld %lld\n" , x , y  );
  double up = y + y + x;
  double dn = 1;
  for( int i = 0 ; i < 3 ; i ++ )
    dn *= ( n - i );
  dn /= 6;
  printf( "%.12f\n" , up / dn );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "points.in" , "r" , stdin );
  freopen( "points.out" , "w" , stdout );
#endif
  init();
  solve();
}
