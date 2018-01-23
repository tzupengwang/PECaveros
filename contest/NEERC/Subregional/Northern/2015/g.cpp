// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 101010
int n , m , k;
vector<int> v[ N ];
int indeg[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  k = getint();
  while( m -- ){
    int ui = getint();
    int vi = getint();
    v[ ui ].PB( vi );
    indeg[ vi ] ++;
  }
}
set<int> S, rem;
vector<PII> vans;
vector<int> topo;
int lst;
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( indeg[ i ] == 0 )
      S.insert( i );
  int got = 0;
  while( got < n ){
    while( (int)S.size() > 1 && k ){
      k --;
      int tmp = *S.begin();
      S.erase( tmp );
      rem.insert( tmp );
    }
    got ++;
    int tmp;
    if( S.size() && rem.size() && k &&
        *rem.rbegin() > *S.begin() ){
      k --;
      int a = *S.begin();
      int b = *rem.rbegin();
      S.erase( a );
      rem.erase( b );
      rem.insert( a );
      vans.PB( MP( lst , b ) );
      tmp = b;
    }else if( S.size() ){
      tmp = *S.begin();
      S.erase( tmp );
    }else{
      tmp = *--rem.end();
      rem.erase( tmp );
      vans.PB( MP( lst , tmp ) );
    }
    lst = tmp;
    topo.PB( tmp );
    for( int i = 0 ; i < (int)v[ tmp ].size() ; i ++ ){
      indeg[ v[ tmp ][ i ] ] --;
      if( indeg[ v[ tmp ][ i ] ] == 0 )
        S.insert( v[ tmp ][ i ] );
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d%c" , topo[ i ] , " \n"[ i == n - 1 ] );
  printf( "%d\n" , (int)vans.size() );
  for( int i = 0 ; i < SZ( vans ) ; i ++ )
    printf( "%d %d\n" , vans[ i ].FI , vans[ i ].SE );
}
int main(){
  freopen( "graph.in" , "r" , stdin );
  freopen( "graph.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
