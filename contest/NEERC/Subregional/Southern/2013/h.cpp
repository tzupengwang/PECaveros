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
#define N 5050
int n;
char c[ N ];
void build(){

}
int dep[ N ] , p[ N ];
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  p[ x ] = y;
}
vector<int> v[ N ];
int indeg[ N ] , len;
void init(){
  n = getint();
  scanf( "%s" , c );
  len = strlen( c );
  for( int i = 0 ; i <= len ; i ++ ) p[ i ] = i;
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] == '=' )
      Union( i , i + 1 );
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] == '<' ){
      v[ find_p( i ) ].push_back( find_p( i + 1 ) );
      indeg[ find_p( i + 1 ) ] ++;
    }else if( c[ i ] == '>' ){
      v[ find_p( i + 1 ) ].push_back( find_p( i ) );
      indeg[ find_p( i ) ] ++;
    }
}
queue<int> Q;
void solve(){
  int st = 0 , got = 0;
  for( int i = 0 ; i <= len ; i ++ )
    if( find_p( i ) == i ){
      st ++;
      if( indeg[ i ] == 0 )
        Q.push( i );
    }
  while( Q.size() ){
    int tn = Q.front(); Q.pop(); got ++;
    for( int i = 0 ; i < (int)v[ tn ].size() ; i ++ ){
      dep[ v[ tn ][ i ] ] = max( dep[ v[ tn ][ i ] ],
                                 dep[ tn ] + 1 );
      indeg[ v[ tn ][ i ] ] --;
      if( indeg[ v[ tn ][ i ] ] == 0 )
        Q.push( v[ tn ][ i ] );
    }
  }
  if( got != st ){
    puts( "-1" );
    return;
  }
  int mx = 0;
  for( int i = 0 ; i <= len ; i ++ )
    if( dep[ find_p( i ) ] > mx )
      mx = dep[ find_p( i ) ];
  if( mx >= n ){
    puts( "-1" );
    return;
  }
  for( int i = 0 ; i <= len ; i ++ )
    putchar( dep[ find_p( i ) ] + 'a' );
  puts( "" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
