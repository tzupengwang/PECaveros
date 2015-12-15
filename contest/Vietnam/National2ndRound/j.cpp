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
int __ = 1 , cs;
/*********default*********/
#define N 252525
int n;
vector< vector<int> > pos;
int mp[ 5 ][ 5 ][ 5 ][ 5 ] , mmidx;
void DFS( int now , int got , vector<int> tv ){
  if( now == 4 ){
    if( got < 4 ) return;
    mp[ tv[ 0 ] ][ tv[ 1 ] ][ tv[ 2 ] ][ tv[ 3 ] ] = mmidx ++;
    pos.PB( tv );
    return;
  }
  for( int i = 0 ; i <= 4 ; i ++ ){
    if( got + i > 4 ) break;
    tv[ now ] = i;
    DFS( now + 1 , got + i , tv );
  }
}
void build(){
  vector<int> _v;
  _v.resize( 4 );
  for( int i = 0 ; i < 4 ; i ++ ) _v[ i ] = 0;
  DFS( 0 , 0 , _v );
}
inline int trans_clr( char clr ){
  if( clr == 'B' ) return 1;
  if( clr == 'G' ) return 2;
  if( clr == 'R' ) return 3;
  if( clr == 'Y' ) return 4;
  return 0;
}
inline int trans( char clr , char num ){
  return trans_clr( clr ) * 10 + num - '0';
}
int v[ N ][ 4 ];
int sum[ N ];
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    char in[ 20 ];
    scanf( "%s" , in );
    int tsum = 0;
    for( int j = 0 ; j < 8 ; j += 2 ){
      v[ i - 1 ][ j >> 1 ] = trans( in[ j ] , in[ j + 1 ] );
      tsum += in[ j + 1 ] - '0';
    }
    sum[ i - 1 ] = tsum;
  }
}
inline int score( int idx , int ps ){
  int x = v[ idx ][ ps ] % 10;
  int clr = v[ idx ][ ps ] / 10;
  if( clr == 1 ) return sum[ idx ] - x;
  if( clr == 2 ) return sum[ idx ] + x;
  if( clr == 3 ) return sum[ idx ] * x;
  if( clr == 4 && x <= 0 ) return 0;
  if( clr == 4 ) return sum[ idx ] / x;
  return 0;
}
int dp[ N ][ 40 ];
bool got[ N ][ 40 ];
int inv[]={2,3,0,1};
int _b[ 4 ];
inline int midx(){
  return mp[ _b[ 0 ] ][ _b[ 1 ] ][ _b[ 2 ] ][ _b[ 3 ] ]; 
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 35 ; j ++ ){
      got[ i ][ j ] = false;
      dp[ i ][ j ] = -2000000000;
    }
  for( int i = 0 ; i < 4 ; i ++ ) _b[ i ] = 0;
  for( int i = 0 ; i < 4 ; i ++ )
    _b[ v[ 0 ][ i ] / 10 - 1 ] ++;
  int _mp = midx();
  dp[ 0 ][ _mp ] = 0;
  got[ 0 ][ _mp ] = true;
  int ans = -2000000000;
  for( int tn = 0 ; tn < n ; tn ++ )
    for( int tmp = 0 ; tmp < 35 ; tmp ++ ){
      if( !got[ tn ][ tmp ] ) continue;
      if( tn == n - 1 ){
        ans = max( ans , dp[ tn ][ tmp ] );
        continue;
      }
      int nxt = tn + 1;
      for( int i = 0 ; i < 4 ; i ++ ){
        int tclr = v[ nxt ][ i ] / 10;
        if( pos[ tmp ][ tclr - 1 ] > 0 ){
          for( int j = 0 ; j < 4 ; j ++ )
            _b[ j ] = pos[ tmp ][ j ];
          _b[ tclr - 1 ] --;
          _b[ ( v[ nxt ][ inv[ i ] ] / 10 ) - 1 ] ++;
          int nmp = midx();
          dp[ nxt ][ nmp ] = max( dp[ nxt ][ nmp ] , dp[ tn ][ tmp ] +
              score( nxt , i ) );
          got[ nxt ][ nmp ] = true;
        }
      }
      dp[ nxt ][ tmp ] = max( dp[ nxt ][ tmp ] , dp[ tn ][ tmp ] - sum[ nxt ] );
      got[ nxt ][ tmp ] = true;
    }
  printf( "%d\n" , ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
