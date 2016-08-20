// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
// typedef pair<LD,LD> Pt;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define X FI
#define Y SE
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define eps2 1e-6
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
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
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
bool operator==( const Pt& p1 , const Pt& p2 ){
  return equal( p1.X , p2.X ) &&
         equal( p1.Y , p2.Y );
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ) return Pt( -INF, -INF );
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
inline void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
inline void print( Pt& tp ){
  printf( "(%.3f, %.3f)" , tp.X , tp.Y );
}
void build(){
}
int n;
const type pi = acos( -1.0 );
#define N 9
vector< Pt > p;
Pt sp;
inline Pt reflect( const Pt& p1 , const Pt& p2 , const Pt& fst , const Pt& to ){
  Pt tmp = p2 - p1;
  Pt zen = tmp * ( ( ( tmp * ( to - fst ) ) / norm2( tmp ) ) );
  Pt fen = ( to - fst ) - zen;
  Pt aa = zen - fen;
  return aa;
}
inline bool in( const Pt& md , const Pt& p1 , const Pt& p2 ){
  if( p1 == md || p2 == md ) return true;
  return ( ( md - p1 ) * ( md - p2 ) ) < eps2;
}
inline type ang( const Pt& tp ){
  type tang = atan2( tp.Y , tp.X );
  while( tang < 0.0 ) tang += 2.0 * pi;
  while( tang > 2.0 * pi ) tang -= 2.0 * pi;
  return tang;
}
bool init(){
  scanf( "%d" , &n );
  if( n == 0 ) return false;
  scan( sp );
  p.resize( n + 1 );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  p[ n ] = p[ 0 ];
  return true;
}
// set< int > ans;
#define K1 150000
#define K2 150000
inline void chg( vector<Pt>& poly , Pt p1 , Pt p2 ){
  for( size_t i = 0 ; i < poly.size() ; i ++ ){
    Pt tmp = p1 + ( p2 - p1 ) * ( ( poly[ i ] - p1 ) * ( p2 - p1 ) ) / norm2( p2 - p1 );
    poly[ i ] = tmp * 2 - poly[ i ];
  }
}
inline bool okay( const vector< int > per ){
  vector< Pt > poly = p;
  vector< pair<type,int> > vv;
  for( size_t i = 0 ; i < per.size() ; i ++ ){
    type deg1 = ang( poly[ per[ i ]     ] - sp );
    type deg2 = ang( poly[ per[ i ] + 1 ] - sp );
    if( deg1 > deg2 ) swap( deg1 , deg2 );
    if( deg2 - deg1 > pi ){
      deg1 += 2.0 * pi;
      swap( deg1 , deg2 );
    }
    vv.emplace_back( deg1 , +1 );
    vv.emplace_back( deg2 , -1 );
    vv.emplace_back( deg1 + 2.0 * pi , +1 );
    vv.emplace_back( deg2 + 2.0 * pi , -1 );
    vv.emplace_back( deg1 + 4.0 * pi , +1 );
    vv.emplace_back( deg2 + 4.0 * pi , -1 );
    chg( poly , poly[ per[ i ] ] , poly[ per[ i ] + 1 ] );
  }
  sort( ALL( vv ) );
  int sum = 0;
  for( size_t l = 0 , r = 0 ; l < vv.size() ; l = r ){
    while( r < vv.size() && equal( vv[ l ].X , vv[ r ].X ) ) r ++;
    for( size_t k = l ; k < r ; k ++ )
      sum += vv[ k ].Y;
    if( sum >= n ) return true;
  }
  return false;
}
// inline bool go( int num , Pt fst ){
  // int got = 0;
  // Pt pre = sp , now = fst;
  // int vv = 0;
  // for( int i = 0 ; i < n ; i ++ ){
    // if( ( got >> num ) & 1 ) return false;
    // vv = vv * 10 + num;
    // got |= ( 1 << num );
    // // Pt nxt = reflect( num , pre , now );
    // int tnxt = -1;
    // Pt njiou;
    // int til = n;
    // for( int j = 0 ; j < til ; j ++ ){
      // if( j == num ) continue;
      // Pt jiou = interPnt( now , now + nxt , p[ j ] , p[ j + 1 ] );
      // if( jiou.X < -1e4 ) continue;
      // if( !in( jiou , p[ j ] , p[ j + 1 ] ) ) continue;
      // if( tnxt != -1 ) return false;
      // tnxt = j;
      // njiou = jiou;
      // til = min( til , j + 2 );
    // }
    // if( tnxt == -1 ) return false;
    // num = tnxt;
    // pre = now;
    // now = njiou;
  // }
  // ans.insert( vv );
  // return true;
// }
void solve(){
  int ans = 0;
  vector< int > per;
  for( int i = 0 ; i < n ; i ++ )
    per.push_back( i );
  do{
    if( okay( per ) ) ans ++;
  }while( next_permutation( ALL( per ) ) );
  // ans.clear();
  // for( int i = 0 ; i < K1 ; i ++ ){
    // int tnxt = -1;
    // Pt njiou;
    // Pt nxt = { cos( 2.0 * pi * (type)i / K1 ) ,
               // sin( 2.0 * pi * (type)i / K1 ) };
    // int til = n;
    // for( int j = 0 ; j < til ; j ++ ){
      // Pt jiou = interPnt( sp , sp + nxt , p[ j ] , p[ j + 1 ] );
      // if( jiou.X < -1e4 ) continue;
      // if( !in( jiou , p[ j ] , p[ j + 1 ] ) ) continue;
      // if( ( jiou - sp ) * nxt < -eps ) continue;
      // if( tnxt != -1 ){
        // tnxt = -1; break;
      // }
      // til = min( til , j + 2 );
      // tnxt = j;
      // njiou = jiou;
    // }
    // if( tnxt == -1 ) continue;
    // if( go( tnxt , njiou ) ) i += 11;
  // }
  // for( int i = 0 ; i < n ; i ++ ){
    // Pt p1 = p[ i ] , p2 = p[ i + 1 ];
    // Pt dlt = p2 - p1;
    // int k2 = K2;
    // type dist = norm( p1 - p2 );
    // if( dist < 20 ) k2 *= dist / 20;
    // for( int j = 1 ; j < k2 ; j ++ )
      // if( go( i , p1 + dlt * ( (type)j / k2 ) ) )
        // j += 11;
  // }
  printf( "%d\n" , ans );
}
int main(){
  build();
  while( init() ){
    solve();
  }
}
