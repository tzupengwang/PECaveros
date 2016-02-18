/ eddy1021
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
void build(){

}
ll ex , ey;
set< PLL > S;
void init(){
  ex = getint();
  ey = getint();
}
queue< PLL > Q;
inline ll lcm( const ll &x , const ll &y ){
  return ( x / __gcd( x , y ) ) * y;
}
void expand( PLL tp ){
  if( tp.FI == tp.SE ) return;
  if( tp.FI > tp.SE ){
    ll bdr = sqrt( tp.FI );
    for( ll i = 1 ; i <= bdr ; i ++ )
      if( tp.FI % i == 0 ){
        ll tlcm = lcm( i , tp.SE );
        if( i + tlcm == tp.FI ){
          if( S.count( MP( i , tp.SE ) ) == 0 ){
            S.insert( MP( i , tp.SE ) );
            Q.push( MP( i , tp.SE ) );
          }
        }
        tlcm = lcm( tp.FI / i , tp.SE );
        if( tp.FI / i + tlcm == tp.FI ){
          if( S.count( MP( tp.FI / i , tp.SE ) ) == 0 ){
            S.insert( MP( tp.FI / i , tp.SE ) );
            Q.push( MP( tp.FI / i , tp.SE ) );
          }
        }
      }
  }else{
    ll bdr = sqrt( tp.SE );
    for( ll i = 1 ; i <= bdr ; i ++ )
      if( tp.SE % i == 0 ){
        ll tlcm = lcm( i , tp.FI );
        if( i + tlcm == tp.SE ){
          if( S.count( MP( tp.FI , i ) ) == 0 ){
            S.insert( MP( tp.FI , i ) );
            Q.push( MP( tp.FI , i ) );
          }
        }
        tlcm = lcm( tp.SE / i , tp.FI );
        if( tp.SE / i + tlcm == tp.SE ){
          if( S.count( MP( tp.FI , tp.SE / i ) ) == 0 ){
            S.insert( MP( tp.FI , tp.SE / i ) );
            Q.push( MP( tp.FI , tp.SE / i ) );
          }
        }
      }
  }
}
void solve(){
  S.clear();
  Q.push( MP( ex , ey ) );
  S.insert( MP( ex , ey ) );
  while( Q.size() ){
    PLL tp = Q.front(); Q.pop();
    expand( tp );
  }
  printf( "Case #%d: %d\n" , ++ _cs , (int)S.size() );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
