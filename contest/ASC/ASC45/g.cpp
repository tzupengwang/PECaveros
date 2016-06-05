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
// #define X FI
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
#define N 20000
#define BS 13131
#define X 25
#define L 20
#define R 40
char c[ N ][ 60 ];
int hs[ N ][ 60 ];
int bs[ 60 ];
map< int , int > M[ 60 ];
vector< int > v[ 1010101 ];
inline int hsvl( int id , int l , int r ){
  return sub( hs[ id ][ r ] , mul( hs[ id ][ l - 1 ] , bs[ r - l + 1 ] ) );
}
void build(){
  bs[ 0 ] = 1;
  for( int i = 1 ; i < 60 ; i ++ )
    bs[ i ] = mul( bs[ i - 1 ] , BS );
}
void init(){
  int mcnt = 0;
  for( int i = 0 ; i < N ; i ++ ){
    gets( c[ i ] + 1 );
    for( int j = 1 ; j <= 50 ; j ++ ){
      hs[ i ][ j ] = add( mul( hs[ i ][ j - 1 ] , BS ) , c[ i ][ j ] );
      if( j >= L && j <= R ){
        if( M[ j ].count( hs[ i ][ j ] ) == 0 )
          M[ j ][ hs[ i ][ j ] ] = mcnt ++;
        v[ M[ j ][ hs[ i ][ j ] ] ].PB( i );
      }
    }
  }
}
char got[ 1021 ];
void solve(){
  int tlen = 0;
  for( int _ = 0 ; tlen + 550 <= 50000 ; _ ++ ){
    int ii = rand() % N;
    int glen = 0;
    for( int j = 1 ; j <= 50 ; j ++ )
      got[ ++ glen ] = c[ ii ][ j ];
    for( int j = 0 ; glen < 500 ; j ++ ){
      bool flag = false;
      for( int u = L ; u <= R ; u ++ ){
        int tvl = hsvl( ii , 50 - u + 1 , 50 );
        if( M[ u ].count( tvl ) == 0 ) continue;
        int nxt = M[ u ][ tvl ];
        ii = v[ nxt ][ rand() % v[ nxt ].size() ];
        for( int k = u + 1 ; k <= 50 ; k ++ )
          got[ ++ glen ] = c[ ii ][ k ];
        flag = true;
        break;
      }
      if( !flag ) break;
    }
    if( glen >= 500 ){
      tlen += glen;
      got[ ++ glen ] = '\0';
      puts( got + 1 );
    }
  }
}
int main(){
  freopen( "genome.in" , "r" , stdin );
  freopen( "genome.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
