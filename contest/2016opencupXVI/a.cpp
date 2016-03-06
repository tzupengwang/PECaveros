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
#define N 3030
void build(){

}
int n;
char c[ N ][ N ];
map<int,int> col[ N ] , row[ N ];
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%s" , c[ i ] + 1 );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      if( c[ i ][ j ] != '?' ){
        row[ i ][ c[ i ][ j ] - 'a' ] ++;
        col[ j ][ c[ i ][ j ] - 'a' ] ++;
      }
}
vector< tuple<int,int,int> > v;
bool mc[ N ] , mr[ N ];
void solve(){
  while( (int)v.size() < 2 * n ){
    for( int i = 1 ; i <= n ; i ++ )
      if( !mr[ i ] ){
        if( (int)row[ i ].size() == 0 ){
          v.PB( MT( 0 , i , 0 ) );
          // printf( "got row %d\n" , i  );
          mr[ i ] = true;
        }else if( (int)row[ i ].size() == 1 ){
          v.PB( MT( 0 , i , row[ i ].begin()->first ) );
          // printf( "got row %d\n" , i  );
          for( int j = 1 ; j <= n ; j ++ )
            if( c[ i ][ j ] - 'a' == row[ i ].begin()->first ){
              col[ j ][ c[ i ][ j ] - 'a' ] --;
              if( col[ j ][ c[ i ][ j ] - 'a' ] == 0 )
                col[ j ].erase( c[ i ][ j ] - 'a' );
            }
          mr[ i ] = true;
        }
      }
    for( int i = 1 ; i <= n ; i ++ )
      if( !mc[ i ] ){
        if( (int)col[ i ].size() == 0 ){
          v.PB( MT( 1 , i , 0 ) );
          // printf( "got col %d\n" , i  );
          mc[ i ] = true;
        }else if( (int)col[ i ].size() == 1 ){
          v.PB( MT( 1 , i , col[ i ].begin()->first ) );
          // printf( "got col %d\n" , i  );
          for( int j = 1 ; j <= n ; j ++ )
            if( c[ j ][ i ] - 'a' == col[ i ].begin()->first ){
              row[ j ][ c[ j ][ i ] - 'a' ] --;
              if( row[ j ][ c[ j ][ i ] - 'a' ] == 0 )
                row[ j ].erase( c[ j ][ i ] - 'a' );
            }
          mc[ i ] = true;
        }
      }
  }
  reverse( ALL( v ) );
  for( size_t i = 0 ; i < v.size() ; i ++ )
    if( get<0>( v[ i ] ) == 0 )
      printf( "h %d %c\n" , get<1>( v[ i ] ) , get<2>( v[ i ] ) + 'a' );
    else
      printf( "v %d %c\n" , get<1>( v[ i ] ) , get<2>( v[ i ] ) + 'a' );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
