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
#define N 21
int n , s;
ll vl[ 1 << N ];
int cnt[ 1 << N ] , lb[ 1 << N ] , id[ 1 << N ];
void build(){
  for( int i = 0 ; i < ( 1 << N ) ; i ++ ){
    cnt[ i ] = cnt[ i / 2 ] + ( i & 1 );
    lb[ i ] = i & (-i);
  }
  for( int i = 0 ; i < N ; i ++ )
    id[ 1 << i ] = i;
}
vector<PII> a;
void init(){
  n = getint();
  s = getint();
  a.clear();
  for( int i = 0 ; i < n ; i ++ )
    a.PB( MP( getint() , i + 1 ) );
  sort( ALL( a ) );
  reverse( ALL( a ) );
  for( int i = 1 ; i < ( 1 << n ) ; i ++ )
    vl[ i ] = vl[ i ^ lb[ i ] ] + a[ id[ lb[ i ] ] ].FI;
}
int dp[ 1 << N ] , from[ 1 << N ];
bool got[ 1 << N ];
int DP( int );
void DFS( int ns , int now , ll sum , int msk , ll tmn ){
  if( sum > s || dp[ ns ] <= 2 ) return;
  if( now == 0 ){
    if( sum + tmn <= s ) return;
    int tdp = DP( ns ^ msk ) + 1;
    if( tdp < dp[ ns ] ){
      dp[ ns ] = tdp;
      from[ ns ] = ns ^ msk;
    }
    return;
  }
  DFS( ns , now ^ lb[ now ] , sum + a[ id[ lb[ now ] ] ].FI , msk ^ lb[ now ] , tmn );
  DFS( ns , now ^ lb[ now ] , sum , msk , min( tmn , (ll)a[ id[ lb[ now ] ] ].FI ) );
}
int DP( int ns ){
  if( ns == 0 ) return 0;
  if( got[ ns ] ) return dp[ ns ];
  got[ ns ] = true;
  if( vl[ ns ] <= s ){
    from[ ns ] = 0;
    return dp[ ns ] = 1;
  }
  int nid = id[ lb[ ns ] ];
  DFS( ns , ns ^ lb[ ns ] , a[ nid ].FI , lb[ ns ] , 1000000000000ll );
  return dp[ ns ];
}
vector<int> ans;
void find_ans( int msk ){
  while( msk ){
    ans.PB( msk ^ from[ msk ] );
    msk = from[ msk ];
  }
}
void solve(){
  for( ll i = 0 ; i < ( 1ll << n ) ; i ++ ){
    got[ i ] = false;
    dp[ i ] = N;
  }
  DP( ( 1 << n ) - 1 );
  ans.clear();
  find_ans( ( 1 << n ) - 1 );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ ){
    printf( "%d" , cnt[ ans[ i ] ] );
    for( int j = 0 ; j < n ; j ++ )
      if( ( ans[ i ] >> j ) & 1 )
        printf( " %d" , a[ j ].SE );
    puts( "" );
  }
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
