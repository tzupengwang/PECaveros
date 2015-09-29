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
#define N 35010
int n , t[ N ] , vv[ N ];
map< PII , int > M;
typedef map< PII , int >::iterator mi;
map< pair<D,D> , int > M2;
typedef map< pair<D,D> , int >::iterator mi2;
bool operator<( const pair<D,D>& p1 , const pair<D,D>& p2 ){
  if( !equal( p1.FI , p2.FI ) )
    return p1.FI < p2.FI;
  if( p1.SE < p2.SE - eps )
    return true;
  return false;
}
vector< pair<PII,int> > v;
void build(){

}
void init(){
  M.clear();
  v.clear();
  for( int i = 1 ; i <= n ; i ++ ){
    t[ i ] = getint();
    vv[ i ] = getint();
    M[ MP( t[ i ] , vv[ i ] ) ] ++;
  }
  for( mi it = M.begin() ; it != M.end() ; it ++ )
    v.PB( MP( it->first , it->second ) );
}
#define T FI
#define V SE
pair<D,D> jiao( PII p1 , PII p2 ){
  D tt = (D)( p1.T * p1.V - p2.T * p2.V ) / (D)( p1.V - p2.V );
  D y = ( tt - (D)p1.T ) * (D)p1.V;
  return MP( tt , y );
}
void solve(){
  int ans = 1;
  for( int i = 0 ; i < (int)v.size() ; i ++ ){
    M2.clear();
    ans = max( ans , v[ i ].SE );
    int nxtt = v[ i ].FI.T + ( 100.0 ) / v[ i ].FI.V;
    for( int j = i + 1 ; j < (int)v.size() ; j ++ )
      if( v[ j ].FI.T <= nxtt ){
        if( v[ i ].FI.V != v[ j ].FI.V ){
          pair<D,D> tp = jiao( v[ i ].FI , v[ j ].FI );
          if( tp.SE < 100.0 + eps &&
              tp.SE > -eps )
            M2[ tp ] += v[ j ].SE;
        }
      }else break;
    for( mi2 it = M2.begin() ; it != M2.end() ; it ++ )
      ans = max( ans , v[ i ].SE + it->second );
  }
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
