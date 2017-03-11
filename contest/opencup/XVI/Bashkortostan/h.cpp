// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<LD,LD> Pt;
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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
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
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 101010
void build(){

}
int n , totalId , depId , cId[ N ];
map<int,int> id;
map<PLL,int> dep[ N ];
map<int,int> dep2[ N ];
map<PLL,int> gen;
string name[ N ];
int d[ N ] , m[ N ] , y[ N ] , lid[ N ];
void init(){
  n = getint();
}
inline PLL hsh( int dept , int tId ){
  ll fi = y[ tId ] * 100000000ll +
          m[ tId ] * 10000ll +
          d[ tId ];
  ll se = dept * 100000000ll +
          lid[ tId ];
  return MP( fi , se );
}
void solve(){
  while( n -- ){
    int cmd = getint() , dept;
    if( cmd == 1 ){
      dept = getint();
      if( id.count( dept ) == 0 )
        id[ dept ] = ++ depId;
      cin >> name[ totalId ];
      d[ totalId ] = getint();
      m[ totalId ] = getint();
      y[ totalId ] = getint();
      lid[ totalId ] = ++ cId[ id[ dept ] ];
      PLL tp = hsh( dept , totalId );
      // printf( "%s %d %lld %lld\n" , name[ totalId ].c_str() , lid[ totalId ] , tp.FI , tp.SE );
      gen[ tp ] = totalId;
      dep[ id[ dept ] ][ tp ] = totalId;
      dep2[ id[ dept ] ][ lid[ totalId ] ] = totalId;
      totalId ++;
    }else{
      dept = getint();
      int iid = getint();
      int did = id[ dept ];
      int aid = dep2[ did ][ iid ];
      PLL tp = hsh( dept , aid );
      gen.erase( tp );
      dep[ did ].erase( tp );
      dep2[ did ].erase( iid );
    }
    if( (int)gen.size() == 0 )
      printf( "Vacant " );
    else
      printf( "%s " , name[ gen.begin()->second ].c_str() );
    if( (int)dep[ id[ dept ] ].size() == 0 )
      printf( "Vacant\n" );
    else
      printf( "%s\n" , name[ dep[ id[ dept ] ].begin()->second ].c_str() );
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
