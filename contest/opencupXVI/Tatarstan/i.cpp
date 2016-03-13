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
int n;
void build(){

}
set<PII> S[ 20 ];
map< tuple<int,int,int,int> , int > M;
void init(){
  n = getint();
}
int num[ N ][ 4 ] , nt;
void Add(){
  for( int i = 0 ; i < 16 ; i ++ ){
    int sum = 0;
    for( int j = 0 ; j < 4 ; j ++ )
      if( ( i >> j ) & 1 )
        sum += num[ nt ][ j ];
      else
        sum -= num[ nt ][ j ];
    S[ i ].insert( MP( sum , nt ) );
  }
  M[ MT( num[ nt ][ 0 ] , num[ nt ][ 1 ] ,
         num[ nt ][ 2 ] , num[ nt ][ 3 ] ) ] = nt;
}
void Del(){
  int id = M[ MT( num[ nt ][ 0 ] , num[ nt ][ 1 ] ,
              num[ nt ][ 2 ] , num[ nt ][ 3 ] ) ];
  for( int i = 0 ; i < 16 ; i ++ ){
    int sum = 0;
    for( int j = 0 ; j < 4 ; j ++ )
      if( ( i >> j ) & 1 )
        sum += num[ nt ][ j ];
      else
        sum -= num[ nt ][ j ];
    S[ i ].erase( MP( sum , id ) );
  }
}
int dist( int ano , int bno ){
  int tans = 0;
  for( int i = 0 ; i < 4 ; i ++ )
    tans += abs( num[ ano ][ i ] - num[ bno ][ i ] );
  return tans;
}
void Qry(){
  int bst = 0;
  for( int i = 0 ; i < 16 ; i ++ ){
    PII tp1 = *S[ i ].begin();
    PII tp2 = *--S[ i ].end();
    bst = max( bst , dist( nt , tp1.SE ) );
    bst = max( bst , dist( nt , tp2.SE ) );
  }
  printf( "%d\n" , bst );
}
void solve(){
  while( n -- ){
    int tp = getint();
    for( int i = 0 ; i < 4 ; i ++ )
      num[ nt ][ i ] = getint();
    if( tp == 1 ) Add();
    else if( tp == 2 ) Del();
    else Qry();
    nt ++;
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
