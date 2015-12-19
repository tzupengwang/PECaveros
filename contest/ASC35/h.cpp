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
#define N 5010
int k;
int n , m , l1 , l2;
int a[ N ] , b[ N ];
int cnta[ N ] , cntb[ N ];
void build(){

}
void init(){
  k = getint();
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    a[ i ] = getint();
    cnta[ a[ i ] ] ++;
  }
  m = getint();
  for( int i = 0 ; i < m ; i ++ ){
    b[ i ] = getint();
    cntb[ b[ i ] ] ++;
  }
}
bool taga[ N ], tagb[ N ];
void solve(){
  int ptr1 = 0 , ptr2 = 0 , alen = 0;
  while( ptr1 < n || ptr2 < m ){
    for( int i = 1 ; i <= k ; i ++ )
      taga[ i ] = tagb[ i ] = false;
    int got1 = 0 , got2 = 0;
    int tk = -1;
    for( int i = 1 ; i <= k ; i ++ )
      if( cnta[ i ] == 0 && cntb[ i ] == 0 ){
        tk = i; break;
      }
    // printf( "%d %d\n" , ptr1 , ptr2 );
    if( tk != -1 ){
      alen ++;
      printf( "%d\n" , alen );
      for( int i = 0 ; i < alen ; i ++ )
        printf( "%d%c" , tk , " \n"[ i == alen - 1 ] );
      exit( 0 );
    }
    while( ptr1 < n && got1 < k ){
      if( !taga[ a[ ptr1 ] ] ){
        taga[ a[ ptr1 ] ] = true;
        cnta[ a[ ptr1 ] ] --;
        got1 ++;
      }
      ptr1 ++;
    }
    // printf( "== %d %d\n" , ptr2 , got2 );
    while( ptr2 < m && got2 < k ){
      if( !tagb[ b[ ptr2 ] ] ){
        tagb[ b[ ptr2 ] ] = true;
        cntb[ b[ ptr2 ] ] --;
        got2 ++;
      }
      ptr2 ++;
    }
    // printf( "== %d %d\n" , ptr2 , got2 );
    alen ++;
  }
  alen ++;
  printf( "%d\n" , alen );
  for( int i = 0 ; i < alen ; i ++ )
    printf( "1%c" , " \n"[ i == alen - 1 ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
