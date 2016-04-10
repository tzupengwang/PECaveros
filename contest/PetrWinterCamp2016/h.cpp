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
#define N 55
void build(){
  srand( 514514 );
}
ll n , k , x[ N ] , y[ N ] , z[ N ];
vector<int> per, pa;
void init(){
  n = getint(); k = getint();
  per.clear();
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
    z[ i ] = getint();
    per.PB( i );
  }
  random_shuffle( ALL( per ) );
}
ll pans, ans;
void output(){
  printf( "%lld\n" , pans );
  pa.resize( k );
  sort( ALL( pa ) );
  for( int i = 0 ; i < k ; i ++ )
    printf( "%d%c" , pa[ i ] + 1 , " \n"[ i + 1 == k ] );
}
void solve(){
  ll sumx = 0 , sumy = 0 , sumz = 0;
  for( int i = 0 ; i < k ; i ++ ){
    sumx += x[ per[ i ] ];
    sumy += y[ per[ i ] ];
    sumz += z[ per[ i ] ];
  }
  pans = ans = sumx * sumx + sumy * sumy + sumz * sumz;
  pa = per;
  if( k == n ){
    output();
    return;
  }
#define K 100000
  for( int _ = 0 ; _ < 5 ; _ ++ ){
    for( int i = 0 ; i < K ; i ++ ){
      int ii = rand() % k;
      int jj = k + rand() % ( n - k );
      ll tsumx = sumx - x[ per[ ii ] ] + x[ per[ jj ] ];
      ll tsumy = sumy - y[ per[ ii ] ] + y[ per[ jj ] ];
      ll tsumz = sumz - z[ per[ ii ] ] + z[ per[ jj ] ];
      ll tans = tsumx * tsumx + tsumy * tsumy + tsumz * tsumz;
      if( tans > ans ){
        ans = tans;
        sumx = tsumx;
        sumy = tsumy;
        sumz = tsumz;
        swap( per[ ii ] , per[ jj ] );
      }
      if( ans > pans ){
        pans = ans;
        pa = per;
      }
    }
    random_shuffle( ALL( per ) );
    sumx = 0 , sumy = 0 , sumz = 0;
    for( int i = 0 ; i < k ; i ++ ){
      sumx += x[ per[ i ] ];
      sumy += y[ per[ i ] ];
      sumz += z[ per[ i ] ];
    }
    ans = sumx * sumx + sumy * sumy + sumz * sumz;
    if( ans > pans ){
      pans = ans;
      pa = per;
    }
  }
  output();
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
