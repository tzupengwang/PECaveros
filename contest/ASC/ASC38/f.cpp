#include <bits/stdc++.h>
using namespace std;
#define N 111
int st , r;
typedef vector< int > rule;
rule rl[ N ];
vector< int > v[ N ];
char c[ 9 ];
void init(){
  scanf( "%s" , c );
  st = c[ 0 ] - 'A';
  int _; scanf( "%d" , &_ );
  for( int i = 0 ; i < _ ; i ++ ){
    scanf( "%s" , c );
    int from = c[ 0 ] - 'A';
    scanf( "%s" , c );
    string ss; getline( cin , ss );
    stringstream is( ss );
    v[ from ].push_back( i );
    while( is >> c ){
      if( c[ 0 ] >= 'a' ) continue;
      rl[ i ].push_back( c[ 0 ] - 'A' );
    }
    reverse( rl[ i ].begin() , rl[ i ].end() );
  }
}
int aa , bb;
#define DEP 11
bool okay;
int stk[ N + N ];
inline int hsh( int ndep ){
#define BS 13131
#define mod 1000000007
  int x = 0;
  for( int i = 0 ; i < ndep ; i ++ )
    x = ( (long long)x * BS + stk[ i ] ) % mod;
  return x;
}
set< int > vst , S;
int _DEP = DEP;
void go( int ndep , bool abye ){
  //for( int i = 0 ; i < ndep ; i ++ )
    //printf( "%d " , stk[ i ] );
  //puts( "" );
  int hsvl = hsh( ndep );
  if( ndep > _DEP || okay ) return;
  if( S.count( hsvl ) || ndep == 0 ){
    if( abye )
      okay = true;
    return;
  }
  if( vst.count( hsvl ) ) return;
  int who = stk[ -- ndep ];
  if( who == bb ) return;
  vst.insert( hsvl );
  S.insert( hsvl );
  if( who == aa ) abye = true;
  for( int id : v[ who ] ){
    if( ndep + (int)rl[ id ].size() >= _DEP ) continue;
    int tdep = ndep;
    for( int u : rl[ id ] )
      stk[ tdep ++ ] = u;
    go( tdep , abye );
    if( okay ) return;
  }
  S.erase( S.find( hsvl ) );
}
void solve(){
  //for( int i = 0 ; i < 26 ; i ++ )
    //random_shuffle( v[ i ].begin() , v[ i ].end() );
  int qry; scanf( "%d" , &qry ); while( qry -- ){
    scanf( "%s" , c ); aa = c[ 0 ] - 'A';
    scanf( "%s" , c ); bb = c[ 0 ] - 'A';
    okay = false;
    if( v[ aa ].size() ){
      for( _DEP = 1 ; _DEP <= DEP && !okay ; _DEP ++ ){
        S.clear();
        vst.clear();
        stk[ 0 ] = st;
        go( 1 , false );
      }
    }
    puts( okay ? "NO" : "YES" );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "formal.in" , "r" , stdin );
  freopen( "formal.out" , "w" , stdout );
#endif
  init();
  solve();
}
