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
#define N 111
int n;
vector< int > ans[ 3 ];
void init(){
  ans[ 0 ].clear();
  ans[ 1 ].clear();
  ans[ 2 ].clear();
}
void set0(){
  ans[ 0 ].push_back( 2 * n - 1 );
  for( int i = 1 ; i < n ; i ++ )
    ans[ 0 ].push_back( i );
  ans[ 0 ].push_back( 2 * n );
  for( int i = n ; i < 2 * n - 1 ; i ++ )
    ans[ 0 ].push_back( i );
}
void set1(){
  ans[ 1 ].push_back( 2 * n - 1 );
  for( int i = n ; i < 2 * n - 1 ; i ++ )
    ans[ 1 ].push_back( i );
  ans[ 1 ].push_back( 2 * n );
  for( int i = 2 ; i <= n ; i ++ )
    ans[ 1 ].push_back( i == n ? 1 : i );
}
int mth[ N ];
void set2(){
  for( int i = 1 ; i < n ; i ++ ){
    int got = i + n;
    if( i == n - 1 ) got = n;
    mth[ i ] = got;
  }
  ans[ 2 ].push_back( 2 * n - 1 );
  for( int i = n - 1 ; i >= 1 ; i -= 2 )
    ans[ 2 ].push_back( i );
  for( int i = n - 2 ; i >= 1 ; i -= 2 )
    ans[ 2 ].push_back( i );
  ans[ 2 ].push_back( 2 * n );
  for( int i = 1 ; i < n ; i ++ )
    ans[ 2 ].push_back( mth[ ans[ 2 ][ i ] ] );
}
void checker(){
  set< PII > S;
  for( int i = 0 ; i < 3 ; i ++ ){
    for( int j = 1 ; j <= n ; j ++ ){
      if( S.count( { ans[ i ][ j - 1 ] , ans[ i ][ j ] } ) ){
        cerr << "Error : " << n << endl;
        return;
      }
      S.insert( { ans[ i ][ j - 1 ] , ans[ i ][ j ] } );
      S.insert( { ans[ i ][ j ] , ans[ i ][ j - 1 ] } );
    }
    for( int j = n + 1 ; j < 2 * n ; j ++ ){
      if( S.count( { ans[ i ][ j - n ] , ans[ i ][ j ] } ) ){
        cerr << "Error : " << n << endl;
        return;
      }
      S.insert( { ans[ i ][ j - n ] , ans[ i ][ j ] } );
      S.insert( { ans[ i ][ j ] , ans[ i ][ j - n ] } );
    }
  }
}
void solve(){
  if( n > 5 ){
    set0();
    set1();
    set2();
  }else if( n == 3 ){
    for( int i = 1 ; i <= 6 ; i ++ )
      ans[ 0 ].push_back( i );
    ans[ 1 ] = { 1 , 4 , 5 , 3 , 2 , 6 };
    ans[ 2 ] = { 2 , 6 , 1 , 3 , 4 , 5 };
  }else if( n == 4 ){
    ans[ 0 ] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 };
    ans[ 1 ] = { 1 , 6 , 7 , 8 , 5 , 3 , 4 , 2 };
    ans[ 2 ] = { 8 , 1 , 7 , 5 , 3 , 4 , 2 , 6 };
  }else if( n == 5 ){
    ans[ 0 ] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 };
    ans[ 1 ] = { 1 , 9 , 8 , 7 , 10 , 6 , 3 , 4 , 5 , 2 };
    ans[ 2 ] = { 10 , 1 , 8 , 6 , 2 , 4 , 7 , 5 , 3 , 9 };
  }
  // checker();
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 2 * n ; j ++ )
      printf( "%d%c" , ans[ i ][ j ] , " \n"[ j + 1 == 2 * n ] );
}
int main(){
  freopen( "embedding.in" , "r" , stdin );
  freopen( "embedding.out" , "w" , stdout );
  build();
  //__ = getint();
  while( scanf( "%d" , &n ) == 1 && n ){
  // for( n = 3 ; n <= 100 ; n ++ ){
    init();
    solve();
  }
}
