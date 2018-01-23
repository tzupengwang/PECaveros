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
#define N 10
char c[ N ][ N ];
void build(){

}
vector< char > face;
bool tag[ 6 ];
int pr[ 6 ];
void init(){
  for( int i = 0 ; i < 6 ; i ++ )
    scanf( "%s" , c[ i ] );
  for( int i = 0 ; i < 6 ; i ++ )
    face.PB( c[ i ][ 0 ] );
}
vector< pair<char,char> > pp;
bool tt[ 6 ];
int ff[ 6 ] , tff[ 6 ];
inline void rotate(){
  for( int i = 0 ; i < 6 ; i ++ )
    tff[ i ] = ff[ i ];
  ff[ 0 ] = tff[ 1 ];
  ff[ 1 ] = tff[ 5 ];
  ff[ 3 ] = tff[ 0 ];
  ff[ 5 ] = tff[ 3 ];
}
int sf[ 6 ];
int per[ 6 ][ 6 ] = { { 0 , 1 , 2 , 3 , 4 , 5 } ,
                     { 0 , 3 , 4 , 1 , 2 , 5 } ,
                     { 4 , 1 , 0 , 3 , 5 , 2 } ,
                     { 2 , 1 , 5 , 3 , 0 , 4 } ,
                     { 2 , 0 , 1 , 5 , 3 , 4 } ,
                     { 2 , 5 , 3 , 0 , 1 , 4 } };
set<string> ans;
inline void gocheck(){
  // for( int i = 0 ; i < 6 ; i ++ )
    // printf( "%d %d\n" , i , ff[ i ] );
  for( int i = 0 ; i < 6 ; i ++ )
    sf[ i ] = ff[ i ];
  vector< string > vv;
  for( int i = 0 ; i < 6 ; i ++ ){
    for( int j = 0 ; j < 6 ; j ++ )
      ff[ j ] = sf[ per[ i ][ j ] ];
    for( int k = 0 ; k < 4 ; k ++ ){
      string ss = "";
      for( int u = 0 ; u < 6 ; u ++ )
        ss += face[ ff[ u ] ];
      vv.PB( ss );
      rotate();
    }
  }
  sort( ALL( vv ) );
  ans.insert( vv[ 0 ] );
}
inline void find_ans(){
  for( int i = 0 ; i < 4 ; i ++ ){
    ff[ 0 ] = pp[ 0 ].FI;
    ff[ 5 ] = pp[ 0 ].SE;
    ff[ 1 ] = pp[ 1 ].FI; ff[ 3 ] = pp[ 1 ].SE;
    ff[ 2 ] = pp[ 2 ].FI; ff[ 4 ] = pp[ 2 ].SE;
    if( i & 1 ) swap( ff[ 1 ] , ff[ 3 ] );
    if( i & 2 ) swap( ff[ 2 ] , ff[ 4 ] );
    gocheck();
  }
  int cnt = 0;
  for( auto it = ans.begin() ; it != ans.end() ; it ++ ){
    cout << *it << endl;
    if( ++ cnt >= 2 ) break;
  }
  if( cnt == 0 )
    puts( "Impossible" );
}
void solve(){
  for( int i = 0 ; i < 6 ; i ++ ){
    for( int j = 0 ; j < 6 ; j ++ ) tag[ j ] = false;
    tag[ i ] = true;
    int got = 0;
    for( int j = 1 ; j < 5 ; j ++ )
      for( int k = 0 ; k < 6 ; k ++ )
        if( !tag[ k ] && face[ k ] == c[ i ][ j ] ){
          tag[ k ] = true; got ++;
          break;
        }
    if( got != 4 ){
      puts( "Impossible" );
      exit( 0 );
    }
    for( int j = 0 ; j < 6 ; j ++ )
      if( !tag[ j ] )
        pr[ i ] = j;
  }
  multiset< pair<char,char> > S;
  for( int i = 0 ; i < 6 ; i ++ ){
    char c1 = face[ i ];
    char c2 = face[ pr[ i ] ];
    if( S.count( { c2 , c1 } ) )
      S.erase( S.find( { c2 , c1 } ) );
    else{
      pp.PB( MP( i , pr[ i ] ) );
      S.insert( { c1 , c2 } );
    }
  }
  if( (int)pp.size() != 3 ){
    puts( "Impossible" );
    exit( 0 );
  }
  find_ans();
}
int main(){
  freopen( "cube.in" , "r" , stdin );
  freopen( "cube.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
