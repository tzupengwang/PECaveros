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
#define N 404040
void build(){

}
int n , m , mx;
int a[ N ] , b[ N ];
bool cmp( int i , int j ){
  return i > j;
}
void init(){
  n = getint();
  m = getint();
  for( int i = 0 ; i < n ; i ++ )
    a[ i ] = getint();
  sort( a , a + n , cmp );
  for( int i = 0 ; i < m ; i ++ ){
    int ii = getint();
    b[ ii ] ++;
    mx = max( mx , ii );
  }
}
multiset<int> S , S2 , res;
typedef multiset<int>::iterator si;
int hole[ N ];
void solve(){
  hole[ 0 ] = 1;
  int nn = 0 , rres = 0;
  for( int i = 0 ; hole[ i ] > 0 ; i ++ ){
    while( hole[ i ] && b[ i ] ){
      S.insert( i );
      b[ i ] --;
      hole[ i ] --;
    }
    if( b[ i ] ) break;
    while( hole[ i ] && nn < n ){
      hole[ i ] --;
      hole[ i + 1 ] += a[ nn ++ ];
    }
    while( hole[ i ] -- && rres < N ){
      rres ++;
      res.insert( i );
    }
  }
  for( int j = 0 ; j <= mx ; j ++ )
    while( b[ j ] -- )
      S2.insert( j );
  while( res.size() && S2.size() ){
    int fi = *res.begin(); res.erase( res.begin() );
    assert( *S2.begin() >= fi );
    S2.erase( S2.begin() );
    S.insert( fi );
  }
  int ans = (int)S.size();
  while( nn < n && S2.size() && S.size() ){
    int mn = *S.begin();
    S.erase( S.find( mn ) );
    if( nn < n ) hole[ mn + 1 ] += a[ nn ++ ];
    while( S2.size() && *S2.begin() <= mn )
      S2.erase( S2.begin() );
    for( int st = mn + 1 , ed = mn + 1 ; st <= ed && S2.size() ; st ++ ){
      if( *S2.rbegin() < st ) break;
      while( hole[ st ] && S2.count( st ) ){
        S2.erase( S2.find( st ) );
        S.insert( st );
        hole[ st ] --;
      }
      while( hole[ st ] && nn < n ){
        hole[ st + 1 ] += a[ nn ++ ];
        ed = max( ed , st + 1 );
        hole[ st ] --;
      }
      while( hole[ st ] && S2.size() ){
        si it = S2.lower_bound( st );
        S2.erase( it );
        S.insert( st );
        hole[ st ] --;
      }
      ans = max( ans , (int)S.size() );
    }
  }
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
