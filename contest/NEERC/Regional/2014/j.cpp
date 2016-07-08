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
#define N 514
void build(){

}
char c[ N ];
int len;
void init(){
  scanf( "%s" , c );
  len = strlen( c );
}
vector< int > mth[ N ];
inline void go( int now ){
  if( now < 10 ){
    for( int i = 0 ; i < len ; i ++ )
      if( c[ i ] - '0' == now )
        mth[ now ].push_back( i );
  }else{
    for( int i = 0 ; i + 1 < len ; i ++ )
      if( c[ i     ] - '0' == now / 10 &&
          c[ i + 1 ] - '0' == now % 10 )
        mth[ now ].push_back( i );
  }
}
bool got[ N ] , tk[ N ];
vector< PII > ans;
vector<int> res;
bool ohya;
int pp[ N ];
void dfs( int now ){
  if( ohya ) return;
  if( now == (int)res.size() ){
    for( int i = 0 ; i < now ; i ++ )
      ans.push_back( { pp[ i ] , res[ i ] } );
    ohya = true;
    return;
  }
  for( int pos : mth[ res[ now ] ] ){
    if( res[ now ] < 10 && tk[ pos ] ) continue;
    if( res[ now ] >= 10 && ( tk[ pos ] || tk[ pos + 1 ] ) ) continue;
    pp[ now ] = pos;
    if( res[ now ] < 10 ) tk[ pos ] = true;
    else tk[ pos ] = tk[ pos + 1 ] = true;
    dfs( now + 1 );
    if( ohya ) return;
    if( res[ now ] < 10 ) tk[ pos ] = false;
    else tk[ pos ] = tk[ pos + 1 ] = false;
  }
}
void solve(){
  int x = 1, ln = 1;
  while( ln < len ){
    x ++;
    if( x < 10 ) ln ++;
    else ln += 2;
  }
  for( int i = 1 ; i <= x ; i ++ )
    go( i );
  for( int _ = 1 ; _ <= x ; _ ++ ){
    int bst = -1 , bstv = N;
    for( int j = 1 ; j <= x ; j ++ )
      if( !got[ j ] && (int)mth[ j ].size() < bstv )
        bstv = (int)mth[ j ].size() , bst = j;
    assert( bst != -1 );
    if( (int)mth[ bst ].size() > 1 ) break;
    got[ bst ] = true;
    for( int pos : mth[ bst ] ){
      if( bst < 10 && !tk[ pos ] ){
        tk[ pos ] = true;
        ans.push_back( { pos , bst } );
        break;
      }else if( bst >= 10 && !tk[ pos ] && !tk[ pos + 1 ] ){
        tk[ pos ] = true;
        tk[ pos + 1 ] = true;
        ans.push_back( { pos , bst } );
        break;
      }
    }
    for( int j = 1 ; j <= x ; j ++ )
      if( !got[ j ] ){
        for( size_t k = 0 ; k < mth[ j ].size() ; k ++ )
          if( j < 10 && tk[ mth[ j ][ k ] ] ){
            swap( mth[ j ][ k ] , mth[ j ].back() );
            mth[ j ].pop_back(); k --;
          }else if( j >= 10 && ( tk[ mth[ j ][ k ] ] || tk[ mth[ j ][ k ] + 1 ] ) ){
            swap( mth[ j ][ k ] , mth[ j ].back() );
            mth[ j ].pop_back(); k --;
          }
      }
  }
  for( int i = 1 ; i <= x ; i ++ )
    if( !got[ i ] )
      res.push_back( i );
  dfs( 0 );
  sort( ALL( ans ) );
  for( int i = 0 ; i < x ; i ++ )
    printf( "%d%c" , ans[ i ].SE , " \n"[ i + 1 == x ] );
}
int main(){
  freopen( "joke.in" , "r" , stdin );
  freopen( "joke.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
