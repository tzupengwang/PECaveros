// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
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
int __ = 1;
/*********default*********/
#define N 32
#define M 10101
int n , m , maxn , si[ N ] , ti[ N ];
vector<PII> v , w;
vector<int> d;
void build(){

}
void init(){
  n = getint(); m = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    si[ i ] = getint();
    ti[ i ] = getint();
    v.PB( MP( ti[ i ] , i ) );
  }
  sort( ALL( v ) );
  for( int i = 1 ; i <= m ; i ++ ){
    int li = getint();
    int ri = getint();
    w.PB( MP( li , ri ) );
  }
  sort( ALL( w ) );
  for( int i = m - 1 ; i >= 0 && (int)d.size() < n ; i -- )
    for( int j = w[ i ].SE - 1 ; j >= w[ i ].FI && (int)d.size() < n ; j -- )
      d.PB( j + 1 );
  reverse( ALL( d ) );
  maxn = (int)d.size();
}
int hf , hf2;
int dp[ N ][ N ][ M ];
int dpset[ N ][ N ][ M ];
int tk[ N ];
int ans , ansn , ansset;
// 0..hf-1
void DFS( int now , int got , int sc , int cs , int tset ){
  if( cs + got > d.back() ) return;
  if( got > maxn ) return;
  if( now == hf ){
    for( int tr = 0 ; tr <= hf2 ; tr ++ ){
      if( got + tr > maxn ) break;
      int psum = 0;
      bool flag = true;
      for( int i = 0 ; i < got ; i ++ ){
        if( psum + ti[ v[ tk[ i ] ].SE ] + i + 1 > d[ maxn - got - tr + i ] ){
          flag = false; break;
        }
        psum += ti[ v[ tk[ i ] ].SE ];
      }
      if( !flag ) continue;
      if( sc > dp[ got ][ tr ][ cs ] ){
        // printf( "=====\n" );
        // printf( "%d %d %d\n" , got , tr , cs );
        // for( int i = 0 ; i < got ; i ++ )
          // printf( "%d%c" , v[ tk[ i ] ].SE , " \n"[ i == got - 1 ] );
        // printf( "               : %d\n" , sc );
        dp[ got ][ tr ][ cs ] = sc;
        dpset[ got ][ tr ][ cs ] = tset;
      }
    }
    return;
  }
  DFS( now + 1 , got , sc , cs , tset );
  tk[ got ] = now;
  DFS( now + 1 , got + 1 , sc + si[ v[ now ].SE ] ,
                           cs + ti[ v[ now ].SE ] , tset | ( 1 << now ) );
}
// hf..n-1
void DFS2( int now , int got , int sc , int cs , int tset ){
  if( cs + got > d.back() ) return;
  if( got > maxn ) return;
  if( now == n ){
    for( int tl = 0 ; tl <= hf ; tl ++ ){
      if( got + tl > maxn ) break;
      int psum = 0, rem = M;
      for( int i = 0 ; i < got ; i ++ ){
        rem = min( rem , d[ maxn - got + i ] - psum - ti[ v[ tk[ i ] ].SE ] - i - 1 - tl );
        psum += ti[ v[ tk[ i ] ].SE ];
      }
      if( rem < 0 ) continue;
      if( sc + dp[ tl ][ got ][ rem ] > ans ){
        ans = sc + dp[ tl ][ got ][ rem ];
        ansn = tl + got;
        ansset = tset | dpset[ tl ][ got ][ rem ];
      }
    }
    return;
  }
  DFS2( now + 1 , got , sc , cs , tset );
  tk[ got ] = now;
  DFS2( now + 1 , got + 1 , sc + si[ v[ now ].SE ] ,
                            cs + ti[ v[ now ].SE ] , tset | ( 1 << now ) );
}
void solve(){
  hf2 = n / 2; hf = n - hf2;
  DFS( 0 , 0 , 0 , 0 , 0 );
  for( int i = 0 ; i <= hf ; i ++ )
    for( int j = 0 ; j <= hf2 ; j ++ )
      for( int k = 0 ; k <= d.back() ; k ++ ){
        if( k && dp[ i ][ j ][ k - 1 ] > dp[ i ][ j ][ k ] ){
          dp[ i ][ j ][ k ] = dp[ i ][ j ][ k - 1 ];
          dpset[ i ][ j ][ k ] = dpset[ i ][ j ][ k - 1 ];
        }
        if( dp[ i ][ j ][ k ] > ans ){
          ans = dp[ i ][ j ][ k ];
          ansn = i + j;
          ansset = dpset[ i ][ j ][ k ];
        }
      }
  DFS2( hf , 0 , 0 , 0 , 0 );
  vector<PII> vans;
  int tptr = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( ( ansset >> i ) & 1 ){
      vans.PB( MP( d[ maxn - ansn + tptr ] -1 , v[ i ].SE ) );
      tptr ++;
    }
  sort( ALL( vans ) );
  printf( "%d %d\n" , ans , tptr );
  for( int i = 0 ; i < tptr ; i ++ )
    printf( "%d %d\n" , vans[ i ].SE , vans[ i ].FI );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
