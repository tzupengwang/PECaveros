#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
#define X first
#define Y second
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
inline bool on_line( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  return ( ( p2 - p1 ) ^ ( p3 - p1 ) ) == 0;
}
typedef pair<LL,LL> frac;
inline frac reduce( frac f ){
  LL gg = __gcd( abs( f.X ) , abs( f.Y ) );
  if( f.Y < 0 ) f.Y *= -1 , f.X *= -1;
  return { f.X / gg , f.Y / gg };
}
inline frac frac_sub( const frac& f1 , const frac& f2 ){
  LL up = f1.X * f2.Y - f2.X * f1.Y;
  LL dn = f1.Y * f2.Y;
  return reduce( { up , dn } );
}
pair< bool , pair< frac , frac > > interPnt( Pt p1 , Pt p2 , Pt q1 , Pt q2 ){
	LL f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	LL f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	LL f = ( f1 + f2 );
  if( f == 0 ) return { false , { { 0 , 0 } , { 0 , 0 } } };
  q1 = q1 * f2;
  q2 = q2 * f1;
  LL retx = q1.X + q2.X;
  LL rety = q1.Y + q2.Y;
  return { true , { reduce( { retx , f } ) ,
                    reduce( { rety , f } ) } };
}
inline bool equal( LL p1 , const frac& p2 ){
  if( p2.Y != 1 ) return false;
  return p1 == p2.X;
}
//inline bool equal( const Pt& p1 , const pair< frac , frac > p2 ){
  //return equal( p1.X , p2.X ) && equal( p1.Y , p2.Y );
//}
#define N 200
int n;
Pt p[ N ];
void init(){
  scanf( "%d" , &n ); n <<= 1;
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
}
vector< pair<frac,frac> > ans;
void go( int i1 , int i2 ){
  int j1 = -1;
  for( int j = 0 ; j < n ; j ++ ){
    if( i1 == j || i2 == j ) continue;
    if( on_line( p[ i1 ] , p[ j ] , p[ i2 ] ) ) continue;
    j1 = j; break;
  }
  if( j1 == -1 ) return;
  for( int j2 = 0 ; j2 < n ; j2 ++ ){
    if( j2 == i1 || j2 == i2 || j2 == j1 ) continue;
    pair< bool , pair< frac , frac > > ret =
      interPnt( p[ i1 ] , p[ i2 ] , p[ j1 ] , p[ j2 ] );
    if( !ret.first ) continue;
    //printf( "%d %d %d %d\n" , i1 , i2 , j1 , j2 );
    map< frac , int > cnt;
    bool okay = true , on_inter = false;
    for( int u = 0 ; u < n && okay ; u ++ ){
      //if( u == i1 || u == i2 || u == j1 || u == j2 ) continue;
      pair<frac,frac> dlt;
      dlt.X = frac_sub( { p[ u ].X , 1 } , ret.second.X );
      dlt.Y = frac_sub( { p[ u ].Y , 1 } , ret.second.Y );
      LL dltx = dlt.X.first * dlt.Y.second;
      LL dlty = dlt.Y.first * dlt.X.second;
      if( dltx == 0 && dlty == 0 ){
        on_inter = true;
        continue;
      }
      frac res = reduce( { dltx , dlty } );
      cnt[ res ] ++;
      if( cnt[ res ] > 2 )
        okay = false;
    }
    int cnt1 = 0;
    for( auto it : cnt )
      if( it.second == 1 )
        cnt1 ++;
    if( cnt1 > 1 || ( cnt1 == 1 && !on_inter ) )
      okay = false;
    if( okay )
      ans.push_back( ret.second );
    if( (int)ans.size() > 1 ) return;
  }
}
void solve(){
  for( int i = 1 ; i < n ; i ++ ){
    go( 0 , i );
    if( (int)ans.size() > 1 ) break;
  }
  if( ans.empty() )
    puts( "Impossible" );
  else if( (int)ans.size() > 1 )
    puts( "Ambiguity" );
  else
    printf( "Center of the universe found at (%.12f, %.12f)\n" ,
            (double)ans[ 0 ].X.X / ans[ 0 ].X.Y ,
            (double)ans[ 0 ].Y.X / ans[ 0 ].Y.Y );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "center.in" , "r" , stdin );
  freopen( "center.out" , "w" , stdout );
#endif
  init();
  solve();
}
