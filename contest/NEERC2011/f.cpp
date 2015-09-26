// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
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
ll getint(){
    ll _x=0,_tmp=1; char _tc=getchar();    
    while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
    if( _tc == '-' ) _tc=getchar() , _tmp = -1;
    while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
    return _x*_tmp;
}
ll mypow( ll _a , ll _x , ll _mod ){
    if( _x == 0 ) return 1ll;
    ll _tmp = mypow( _a , _x / 2 , _mod );
    _tmp = ( _tmp * _tmp ) % _mod;
    if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
    return _tmp;
}
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
typedef pair<ll,ll> PLL;
typedef pair< PLL , PLL > rec;
void build(){

}
rec o1 , i1 , o2 , i2;
rec normal( const rec& r ){
  rec tmp;
  tmp.FI.FI = min( r.FI.FI , r.SE.FI );
  tmp.SE.FI = max( r.FI.FI , r.SE.FI );
  tmp.FI.SE = min( r.FI.SE , r.SE.SE );
  tmp.SE.SE = max( r.FI.SE , r.SE.SE );
  return tmp;
}
/*void output( const rec& r ){
  cout << r.FI.FI << " ";
  cout << r.FI.SE << " ";
  cout << r.SE.FI << " ";
  cout << r.SE.SE;
}*/
void init(){
  ll a , b , c , d;
  a = getint(); b = getint();
  c = getint(); d = getint();
  o1 = MP( MP( a , b ) , MP( c , d ) );
  o1 = normal( o1 );
  a = getint(); b = getint();
  c = getint(); d = getint();
  i1 = MP( MP( a , b ) , MP( c , d ) );
  i1 = normal( i1 );
  a = getint(); b = getint();
  c = getint(); d = getint();
  o2 = MP( MP( a , b ) , MP( c , d ) );
  o2 = normal( o2 );
  a = getint(); b = getint();
  c = getint(); d = getint();
  i2 = MP( MP( a , b ) , MP( c , d ) );
  i2 = normal( i2 );
/*  output( o1 ); puts( "" );
  output( i1 ); puts( "" );
  output( o2 ); puts( "" );
  output( i2 ); puts( "" );*/
}
ll area( const rec& r ){
  if( r.SE.FI < r.FI.FI ) return 0;
  if( r.SE.SE < r.FI.SE ) return 0;
  return ( r.SE.FI - r.FI.FI ) *
         ( r.SE.SE - r.FI.SE );
}
rec inter_rec( const rec& r1 , const rec& r2 ){
  rec tr;
  tr.FI.FI = max( r1.FI.FI , r2.FI.FI );
  tr.FI.SE = max( r1.FI.SE , r2.FI.SE );
  tr.SE.FI = min( r1.SE.FI , r2.SE.FI );
  tr.SE.SE = min( r1.SE.SE , r2.SE.SE );
  return tr;
}
ll inter( const rec& r1 , const rec& r2 ){
  rec tr = inter_rec( r1 , r2 );
  if( tr.FI.FI > tr.SE.FI ) return 0;
  if( tr.FI.SE > tr.SE.SE ) return 0;
//  output( tr ); putchar( ' ' );
//  cout << area( tr ) << endl;
  return max( 0ll , area( tr ) );
}
ll cal( ll dltx , ll dlty ){
  rec no2 , ni2;
  no2 = MP( MP( o2.FI.FI + dltx , o2.FI.SE + dlty ) ,
            MP( o2.SE.FI + dltx , o2.SE.SE + dlty ) );
  ni2 = MP( MP( i2.FI.FI + dltx , i2.FI.SE + dlty ) ,
            MP( i2.SE.FI + dltx , i2.SE.SE + dlty ) );
  ll tans = 0;
  tans = inter( o1 , no2 );
  rec ojiao = inter_rec( o1 , no2 );
  rec oi1 = inter_rec( ojiao , i1 );
  rec oni2 = inter_rec( ojiao , ni2 );
  tans -= area( oi1 );
  tans -= area( oni2 );
  tans += inter( oi1 , oni2 );
  return max( 0ll , tans );
}
void solve(){
  ll ans = -1 , ax = -1 , ay = -1;
  vector<ll> px;
  vector<ll> py;
  px.PB( o1.FI.FI - o2.FI.FI );
  px.PB( o1.SE.FI - o2.SE.FI );
  px.PB( o1.FI.FI - o2.SE.FI );
  px.PB( o1.SE.FI - o2.FI.FI );
  px.PB( i1.FI.FI - i2.FI.FI );
  px.PB( i1.SE.FI - i2.SE.FI );
  px.PB( i1.FI.FI - i2.SE.FI );
  px.PB( i1.SE.FI - i2.FI.FI );
  px.PB( o1.FI.FI - i2.FI.FI );
  px.PB( o1.SE.FI - i2.SE.FI );
  px.PB( o1.FI.FI - i2.SE.FI );
  px.PB( o1.SE.FI - i2.FI.FI );
  px.PB( i1.FI.FI - o2.FI.FI );
  px.PB( i1.SE.FI - o2.SE.FI );
  px.PB( i1.FI.FI - o2.SE.FI );
  px.PB( i1.SE.FI - o2.FI.FI );
/***/
  py.PB( o1.FI.SE - o2.FI.SE );
  py.PB( o1.SE.SE - o2.SE.SE );
  py.PB( o1.FI.SE - o2.SE.SE );
  py.PB( o1.SE.SE - o2.FI.SE );
  py.PB( i1.FI.SE - i2.FI.SE );
  py.PB( i1.SE.SE - i2.SE.SE );
  py.PB( i1.FI.SE - i2.SE.SE );
  py.PB( i1.SE.SE - i2.FI.SE );
  py.PB( o1.FI.SE - i2.FI.SE );
  py.PB( o1.SE.SE - i2.SE.SE );
  py.PB( o1.FI.SE - i2.SE.SE );
  py.PB( o1.SE.SE - i2.FI.SE );
  py.PB( i1.FI.SE - o2.FI.SE );
  py.PB( i1.SE.SE - o2.SE.SE );
  py.PB( i1.FI.SE - o2.SE.SE );
  py.PB( i1.SE.SE - o2.FI.SE );
  for( int i = 0 ; i < (int)px.size() ; i ++ )
    for( int j = 0 ; j < (int)py.size() ; j ++ ){
      ll tans = cal( px[ i ] , py[ j ] );
      if( tans > ans ){
        ans = tans; ax = px[ i ]; ay = py[ j ];
      }
    }
  cout << ans << endl;
  cout << ax << " " << ay << endl;
}
int main(){
  freopen( "frames.in" , "r" , stdin );
  freopen( "frames.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
