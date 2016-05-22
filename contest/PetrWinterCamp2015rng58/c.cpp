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
void build(){

}
#define N 9
ll n , a[ N ] , sum;
vector<int> v;
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    a[ i ] = getint();
    sum += a[ i ];
    // if( a[ i ] < n - 1 ){
    v.PB( min( 6ll , a[ i ] ) );
      // sum += ( n - 1 ) - a[ i ];
    // }
  }
  // sum -= n * ( n - 1 ) / 2;
}
// vector<PII> edge;
// int bt[ 65536 ] , tdeg[ N ];
// inline bool okay( int msk ){
  // for( size_t i = 0 ; i < v.size() ; i ++ )
    // tdeg[ i ] = 0;
  // for( size_t i = 0 ; i < edge.size() ; i ++ )
    // if( ( msk >> i ) & 1 ){
      // tdeg[ edge[ i ].FI ] ++;
      // tdeg[ edge[ i ].SE ] ++;
    // }
  // for( size_t i = 0 ; i < v.size() ; i ++ )
    // if( tdeg[ i ] > v[ i ] )
      // return false;
  // return true;
// }
int mx;
// map< vector<int> , int > M;
bool tag[ N ][ N ];
vector<int> tv;
int go(){
  // if( M.count( tv ) ) return M[ tv ];
  int bst = 0;
  for( size_t i = 0 ; i < tv.size() ; i ++ )
    for( size_t j = i + 1 ; j < tv.size() ; j ++ )
      if( tv[ i ] && tv[ j ] && !tag[ i ][ j ] ){
        tag[ i ][ j ] = true;
        tv[ i ] --; tv[ j ] --;
        bst = max( bst , 1 + go() );
        tv[ i ] ++; tv[ j ] ++;
        tag[ i ][ j ] = false;
      }
  for( size_t i = 0 ; i < tv.size() ; i ++ )
    for( size_t j = i + 1 ; j < tv.size() ; j ++ )
      if( tv[ i ] && tv[ j ] && !tag[ i ][ j ] )
      for( size_t k = j + 1 ; k < tv.size() ; k ++ )
        if( tv[ k ] &&
            !tag[ i ][ k ] && 
            !tag[ j ][ k ] ){
          tag[ i ][ j ] = tag[ i ][ k ] = tag[ j ][ k ] = true;
          tv[ i ] --; tv[ j ] --; tv[ k ] --;
          bst = max( bst , 2 + go() );
          tv[ i ] ++; tv[ j ] ++; tv[ k ] ++;
          tag[ i ][ j ] = tag[ i ][ k ] = tag[ j ][ k ] = false;
          for( size_t l = k + 1 ; l < tv.size() ; l ++ )
            if( tv[ l ] &&
                !tag[ i ][ l ] &&
                !tag[ j ][ l ] &&
                !tag[ k ][ l ] ){
              tag[ i ][ j ] = tag[ i ][ k ] = tag[ j ][ k ] = true;
              tag[ i ][ l ] = tag[ j ][ l ] = tag[ k ][ l ] = true;
              tv[ i ] --; tv[ j ] --; tv[ k ] --; tv[ l ] --;
              bst = max( bst , 3 + go() );
              tv[ i ] ++; tv[ j ] ++; tv[ k ] ++; tv[ l ] ++;
              tag[ i ][ j ] = tag[ i ][ k ] = tag[ j ][ k ] = false;
              tag[ i ][ l ] = tag[ j ][ l ] = tag[ k ][ l ] = false;
            }
        }
  return bst;
}
void solve(){
  tv = v;
  mx = go();
  // for( size_t i = 0 ; i < v.size() ; i ++ )
    // for( size_t j = i + 1 ; j < v.size() ; j ++ )
      // edge.PB( MP( i , j ) );
  // int esz = (int)edge.size() , mx = 0;
  // for( int msk = 1 ; msk < ( 1 << esz ) ; msk ++ ){
    // bt[ msk ] = bt[ msk / 2 ] + msk % 2;
    // if( okay( msk ) )
      // mx = max( mx , bt[ msk ] );
  // }
  sum -= mx;
  cout << sum << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
