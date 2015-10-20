// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef long double D;
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
#define N 110
#define X FI
#define Y SE
int n;
D a;
vector< pair<ll,ll> > p;
typedef pair<ll,ll> PLL;
PLL operator-( const PLL& p1 , const PLL& p3 ){
  return MP( p1.FI - p3.FI , p1.SE - p3.SE );
}
ll operator^( const PLL& p1 , const PLL& p3 ){
  return p1.FI * p3.SE - p1.SE * p3.FI;
}
void build(){

}
ll area( const vector<PLL>& tv ){
  ll tarea = tv.back() ^ tv[ 0 ];
  for( int i = 1 ; i < (int)tv.size() ; i ++ )
    tarea += tv[ i - 1 ] ^ tv[ i ];
  if( tarea < 0 ) tarea *= -1;
  return tarea;
}
ll origin , tri , pos;
void init(){
  cin >> a >> n;
  for( int i = 0 ; i < n ; i ++ ){
    pair<ll,ll> tmp;
    cin >> tmp.X >> tmp.Y;
    p.PB( tmp );
  }
  origin = area( p );
  for( int i = 0 ; i < n ; i ++ ){
    PLL pre = p[ ( i - 1 + n ) % n ];
    PLL nxt = p[ ( i + 1 ) % n ];
    PLL v1 = pre - p[ i ];
    PLL v2 = nxt - p[ i ];
    D dlt = v1 ^ v2;
    if( dlt < 0 ) dlt *= -1;
    tri += dlt;
  }
}
#define K 1000
bool okay( D ts ){
  ll lft = ceil( origin * ( ts * ts * ( 1.0 - a ) ) );
  return lft <= tri;
}
void solve(){
  //D l = 2.0, r = 1000.0 , mid;
  //for( int i = 0 ; i < K ; i ++ ){
  //  mid = ( l + r ) * 0.5;
  //  if( okay( mid ) ) l = mid;
  //  else r = mid;
  //}
  //mid = ( l + r ) * 0.5;
  D ans = sqrt( (D)tri / ( (D)origin * ( 1.0 - a ) )  );
  cout << fixed << setprecision( 12 );
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
