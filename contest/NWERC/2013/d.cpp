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
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 8
int n , k , r[ N ] , c[ N ];
void build(){

}
void init(){
  for( int i = 1 ; i <= n ; i ++ )
    r[ i ] = getint();
  for( int i = 1 ; i <= r[ 1 ] ; i ++ ){
    c[ i ] = 0;
    for( int j = 1 ; j <= n ; j ++ )
      if( r[ j ] >= i )
        c[ i ] ++;
  }
  n = r[ 1 ];
  k = getint();
}
vector< vector<int> > pos[ N ];
vector<int> tv;
void DFS( int got , int pre ){
  if( got > 0 && got <= c[ 1 ] ){
    pos[ got ].PB( tv );
  }
  for( int i = pre + 1 ; i <= k ; i ++ ){
    tv.PB( i );
    DFS( got + 1 , i );
    tv.pop_back();
  }
}
ll dp[ N ][ N * N ];
bool good( vector<int>& pre , vector<int>& now ){
  for( int i = 0 ; i < (int)now.size() ; i ++ )
    if( now[ i ] < pre[ i ] )
      return false;
  return true;
}
void solve(){
  tv.clear();
  for( int i = 0 ; i < N ; i ++ )
    pos[ i ].clear();
  DFS( 0 , 0 );
  for( int i = 0 ; i < (int)pos[ c[ 1 ] ].size() ; i ++ )
    dp[ 1 ][ i ] = 1;
  for( int i = 2 ; i <= n ; i ++ )
    for( int j = 0 ; j < (int)pos[ c[ i ] ].size() ; j ++ ){
      dp[ i ][ j ] = 0;
      for( int tk = 0 ; tk < (int)pos[ c[ i - 1 ] ].size() ; tk ++ )
        if( good( pos[ c[ i - 1 ] ][ tk ] ,
                  pos[ c[ i ] ][ j ] ) )
          dp[ i ][ j ] += dp[ i - 1 ][ tk ];
    }
  ll ans = 0;
  for( int i = 0 ; i < (int)pos[ c[ n ] ].size() ; i ++ )
    ans += dp[ n ][ i ];
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( cin >> n ){
    init();
    solve();
  }
}
