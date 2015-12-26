#include <bits/stdc++.h>
using namespace std;
#define N 10100
#define X first
#define Y second
typedef double D;
typedef pair<D,D> Pt;
const D eps = 1e-15;
const D g = 9.8;
inline void Scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
void Print( const Pt& tp ){
  printf( "%.3f %.3f\n" , tp.X , tp.Y );
} 
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return make_pair( p1.X + p2.X , p1.Y + p2.Y );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return make_pair( p1.X - p2.X , p1.Y - p2.Y );
}
inline Pt operator*( const Pt& p1 , const D& tk ){
  return make_pair( p1.X * tk , p1.Y * tk );
}
inline Pt operator/( const Pt& p1 , const D& tk ){
  return make_pair( p1.X / tk , p1.Y / tk );
}
inline D operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline D norm( const Pt& p1 ){
  return sqrt( p1 % p1 );
}
inline D dist( const Pt& p1 , const Pt& p2 ){
  return norm( p1 - p2 );
}
int n;
D v;
Pt p[ N ];
void init(){
  scanf( "%d%lf" , &n , &v );
  for( int i = 0 ; i < n ; i ++ )
    Scan( p[ i ] );
}
D ans;
void solve(){
  int now = 1;
  ans = dist( p[ 0 ] , p[ 1 ] );
  while( now < n - 1 ){
    bool got = false;
    Pt vv = p[ now ] - p[ now - 1 ];
    D ang = atan( vv.Y / vv.X );
    D vc = v * cos( ang );
    D vs = v * sin( ang );
    for( int nxt = now + 1 ; nxt < n ; nxt ++ ){
      D tt = ( p[ nxt ].X - p[ now ].X ) / vc;
      D ty = p[ now ].Y + vs * tt - g / 2.0 * tt * tt;
      if( ty < p[ nxt ].Y - eps ){
        D tl = ( p[ nxt - 1 ].X - p[ now ].X ) / vc , tmid = tl;
        if( nxt == now + 1 ) tl += eps;
        D tr = tt;
        Pt dlt = p[ nxt ] - p[ nxt - 1 ];
        for( int j = 0 ; j < 100 ; j ++ ){
          tmid = ( tl + tr ) * 0.5;
          ty = p[ now ].Y + vs * tmid - g / 2.0 * tmid * tmid;
          D tx = p[ now ].X + tmid * vc;
          Pt tmp = p[ nxt - 1 ] + dlt * ( ( tx - p[ nxt - 1 ].X ) /
                                        ( p[ nxt ].X - p[ nxt - 1 ].X ) );
          if( ty > tmp.Y ) tl = tmid;
          else tr = tmid;
        }
        tmid = ( tl + tr ) * 0.5;
        ty = p[ now ].Y + vs * tmid - g / 2.0 * tmid * tmid;
        D tx = p[ now ].X + tmid * vc;
        Pt tmp = p[ nxt - 1 ] + dlt * ( ( tx - p[ nxt - 1 ].X ) /
                                        ( p[ nxt ].X - p[ nxt - 1 ].X ) );
        ans += dist( tmp , p[ nxt ] );
        //Print( tmp );
        now = nxt;
        got = true;
        break;
      }
    }
    if( !got ) break;
  }
  printf( "%.12f\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ );
  while( _ -- ){
    init();
    solve();
  }
}
