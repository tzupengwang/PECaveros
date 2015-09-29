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
#define N 460
int n , m , s[ N ] , deg[ N ];
bool c[ N ][ N ];
set<int> v[ N ];
typedef set<int>::iterator si;
void build(){

}
queue<int> Q;
bool dn[ N ];
int ans;
void init(){
  ans = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    deg[ i ] = 0;
    dn[ i ] = false;
    s[ i ] = getint();
    ans = max( ans , s[ i ] );
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      c[ i ][ j ] = false;
  for( int i = 1 ; i <= m ; i ++ ){
    int tu = getint();
    int tv = getint();
    c[ tu ][ tv ] = 
    c[ tv ][ tu ] = true;
    v[ tu ].insert( tv );
    v[ tv ].insert( tu );
    deg[ tu ] ++;
    deg[ tv ] ++;
    ans = max( ans , s[ tu ] + s[ tv ] );
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( deg[ i ] <= 4 ){
      Q.push( i );
      dn[ i ] = true;
    }
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    vector<int> tmp;
    for( si it = v[ tn ].begin() ; it != v[ tn ].end() ; it ++ ){
      tmp.PB( *it );
      deg[ *it ] --;
      v[ *it ].erase( v[ *it ].find( tn ) );
      if( deg[ *it ] <= 4 && !dn[ *it ] ){
        Q.push( *it );
        dn[ *it ] = true;
      }
    }
    for( int i = 0 ; i < (int)tmp.size() ; i ++ )
      for( int j = i + 1 ; j < (int)tmp.size() ; j ++ )
        if( c[ tmp[ i ] ][ tmp[ j ] ] )
          ans = max( ans , s[ tn ] + s[ tmp[ i ] ] + s[ tmp[ j ] ] );
    for( int i = 0 ; i < (int)tmp.size() ; i ++ )
      for( int j = i + 1 ; j < (int)tmp.size() ; j ++ )
        for( int k = j + 1 ; k < (int)tmp.size() ; k ++ )
          if( c[ tmp[ i ] ][ tmp[ j ] ] &&
              c[ tmp[ i ] ][ tmp[ k ] ] &&
              c[ tmp[ j ] ][ tmp[ k ] ] )
            ans = max( ans , 
                s[ tn ] + s[ tmp[ i ] ] +
                          s[ tmp[ j ] ] +
                          s[ tmp[ k ] ] );
  }
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( cin >> n >> m ){
    init();
    solve();
  }
}
