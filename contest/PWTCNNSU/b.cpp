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
#define N 101010
void build(){

}
ll n , m , x[ N ] , f[ N ];
set<ll> S[ 2 ];
typedef set<ll>::iterator si;
void init(){
  n = getint(); m = getint();
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    f[ i ] = getint();
    S[ f[ i ] ].insert( x[ i ] );
  }
}
void solve(){
  ll cnt = 0 , dir = 0 , pos = m;
  while( S[ 0 ].size() || S[ 1 ].size() ){
    // printf( "%lld %lld\n" , dir , pos );
    if( dir == 0 ){
      if( S[ 0 ].size() ){
        si it = S[ 0 ].upper_bound( pos );
        if( it == S[ 0 ].begin() ){
          cnt ++; pos = 0;
        }else{
          -- it;
          pos = *it;
          S[ 0 ].erase( pos );
        }
      }else cnt ++, pos = 0;
    }else{
      if( S[ 1 ].size() ){
        si it = S[ 1 ].upper_bound( pos );
        if( it == S[ 1 ].end() ){
          puts( "-1" );
          exit( 0 );
        }else{
          pos = *it;
          S[ 1 ].erase( pos );
        }
      }else{
        puts( "-1" );
        exit( 0 );
      }
    }
    dir = 1 - dir;
  }
  if( dir == 0 ) cnt ++;
  printf( "%lld\n" , cnt );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
