// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#ifndef ONLINE_JUDGE
#define debug(...) printf(__VA_ARGS__)
#else 
#define debug(...)
#endif
inline ll getint(){
  ll _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
inline ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
inline ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = mul( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = mul( _tmp , _a , _mod );
  return _tmp;
}
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 11
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
  tp.X = getint();
  tp.Y = getint();
}
const D pi = acos( -1.0 );
void build(){

}
inline int my_rand( int x ){
  return rand() % ( x + x + 1 ) - x;
}
inline Pt randp( int x = 3000 ){
  return { my_rand( x ) , my_rand( x ) };
}
inline bool onSeg( const Line& tl , const Pt& tp ){
  if( tp == tl.FI || tp == tl.SE ) return true;
  if( !equal( 0.0 , ( tp - tl.FI ) ^ ( tl.SE - tl.FI ) ) )
    return false;
  return ( ( tl.FI - tp ) * ( tl.SE - tp ) ) < eps;
}
inline type theta( const Pt& tp ){
  return atan2l( tp.Y , tp.X );
}
inline type reg( type ang ){
  while( ang < -pi ) ang += 2.0 * pi;
  while( ang > +pi ) ang -= 2.0 * pi;
  return ang;
}
inline bool in( const vector<Pt>& ch , const Pt& tp ){
  // for( size_t i = 1 ; i < ch.size() ; i ++ )
    // if( onSeg( { { ch[ i - 1 ].X , ch[ i - 1 ].Y } ,
                 // { ch[ i ].X , ch[ i ].Y } } , tp ) )
      // return true;
  for( size_t i = 1 ; i < ch.size() ; i ++ )
    if( ( ( ch[ i - 1 ] - tp ) ^ ( ch[ i ] - tp ) ) < 0.0 ) return false;
  return true;
}
inline vector<Pt> convexHull( vector<Pt>& vv ){
  vector<Pt> ch;
  sort( vv.begin() , vv.end() );
  vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
  int csz = 0 , psz;
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    while( csz > 1 && ( ( ch[ csz - 1 ] - ch[ csz - 2 ] ) ^
                        ( vv[ i ] - ch[ csz - 1 ] ) ) < eps )
      ch.pop_back(), csz --;
    ch.push_back( vv[ i ] ); csz ++;
  }
  reverse( vv.begin() , vv.end() ); psz = csz;
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    while( csz - psz > 0 && ( ( ch[ csz - 1 ] - ch[ csz - 2 ] ) ^
                              ( vv[ i ] - ch[ csz - 1 ] ) ) < eps )
      ch.pop_back(), csz --;
    ch.push_back( vv[ i ] ); csz ++;
  }
  return ch;
}
int n; D l , r;
vector<Pt> p , ch;
inline bool okay( const Pt& tp ){
  return !in( ch , tp );
}
inline D randi(){
  return ( rand() % ( 100000 / n ) ) / 100000.0;
}
inline bool modify( const Pt& tp ){
  bool flag = true;
  for( Pt xp : p ){
    D dst = norm2( tp - xp );
    if( dst < l * l ){
      flag = false;
    }
    if( dst > r * r ){
      flag = false;
    }
  }
  return flag;
}
inline D ang( const Pt& tp ){
  vector< D > dd;
  for( Pt xp : p ){
    Pt tmp = xp - tp;
    D tag = atan2( tmp.Y , tmp.X );
    dd.push_back( tag );
  }
  int xn = (int)dd.size();
  sort( ALL( dd ) );
  D bst = 1e20;
  for( int i = 0 ; i < xn ; i ++ ){
    bst = min( bst , dd[ i + xn - 1 ] - dd[ i ] );
    dd.push_back( dd[ i ] + 2.0 * pi );
  }
  return bst;
}
void init(){
  n = getint();
  l = getint();
  r = getint();
  for( int i = 0 ; i < n ; i ++ ){
    Pt tp; scan( tp );
    p.push_back( tp );
  }
  ch = convexHull( p );
}
D fans = -1;
Pt pans;
inline void Ans( D xans , Pt ppans ){
  if( fans < 0.0 || xans < fans ){
    // printf( "%.9f\n" , xans );
    fans = xans;
    pans = ppans;
  }
}
// void go( Pt tp ){
  // D stp = 1e3 , dn = 0.8;
  // int tcnt = 0;
  // for( int _ = 0 ; _ < 256 ; _ ++ , stp *= dn ){
    // if( okay( tp ) ){
      // pair<bool,Pt> tmp = modify( tp );
      // D tans = -1; Pt xxp = tmp.second;
      // if( tmp.first ){
        // D ttans = ang( tmp.second );
        // if( tans < 0.0 || ttans < tans ){
          // tans = ttans;
          // xxp = tmp.second;
          // Ans( tans , xxp );
        // }
        // for( int j = 0 ; j < 120 ; j += 3 ){
          // Pt nxt = { stp * cos( (D)j / 180.0 * pi ) ,
                     // stp * sin( (D)j / 180.0 * pi ) };
          // nxt = nxt + tp;
          // if( okay( nxt ) ){
            // tmp = modify( nxt );
            // if( tmp.first ){
              // ttans = ang( nxt );
              // if( tans < 0.0 || ttans < tans ){
                // tans = ttans;
                // xxp = nxt;
                // Ans( tans , xxp );
              // }
            // }else if( tans < 0.0 )
              // xxp = tmp.SE;
          // }
        // }
      // }else{
        // tcnt ++;
        // _ --;
        // if( tcnt % 120 == 0 )
          // _ ++;
      // }
      // tp = xxp;
    // }else{
      // D tans = -1; Pt xxp = tp;
      // for( int j = 0 ; j < 120 ; j += 3 ){
        // Pt nxt = { stp * cos( (D)j / 180.0 * pi ) ,
                   // stp * sin( (D)j / 180.0 * pi ) };
        // nxt = nxt + tp;
        // if( okay( nxt ) ){
          // pair<bool,Pt> tmp = modify( nxt );
          // if( tmp.first ){
            // D ttans = ang( nxt );
            // if( tans < 0.0 || ttans < tans ){
              // tans = ttans;
              // xxp = nxt;
              // Ans( tans , xxp );
            // }
          // }else if( tans < 0.0 )
            // xxp = tmp.SE;
        // }
      // }
      // tp = xxp;
    // }
  // }
// }
const int K = 28000000;
void solve(){
  // for( int i = 0 ; i < 120 ; i ++ ){
    // Pt st = { 2e3 * cos( i * 3 / 180.0 * pi ) ,
              // 2e3 * sin( i * 3 / 180.0 * pi ) };
    // go( st );
  // }
  // if( n == 10 ) K = 2800000;
  for( int i = 0 ; i < K / n ; i ++ ){
    Pt ttp = { r * cos( (D)i / ( K / n ) * 2.0 * pi ) ,
               r * sin( (D)i / ( K / n ) * 2.0 * pi ) };
    for( Pt tp : p ){
      Pt tmp = tp + ttp;
      if( okay( tmp ) && modify( tmp ) ){
        D tans = ang( tmp );
        Ans( tans , tmp );
      }
    }
  }
  if( fans < -0.5 ) puts( "impossible" );
  else printf( "%.9f %.9f\n" , pans.X , pans.Y );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "shepherd.in" , "r" , stdin );
  freopen( "shepherd.out" , "w" , stdout );
#endif
  srand( time(0) ^ ( 514 * 50216 ) );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
