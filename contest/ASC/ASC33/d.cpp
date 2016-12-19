#include <bits/stdc++.h>
using namespace std;
#define N 20
struct Rule{
  char c[ N ];
  int len;
  int init(){
    scanf( "%s" , c );
    len = strlen( c );
    int st = c[ 0 ] - 'A';
    for( int i = 3 ; i < len ; i ++ )
      c[ i - 3 ] = c[ i ];
    len -= 3;
    return st;
  }
} rl[ 1021 ];
vector< int > v[ 26 ];
int n;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    v[ rl[ i ].init() ].push_back( i );
}
bool instk[ 26 ];
bool vsted[ 26 ];
int prv[ 26 ];
bool ok[ 1021 ] , done[ 1021 ];
int go( int var , int len ){
  if( instk[ var ] && len > prv[ var ] ){
    puts( "infinite" );
    exit( 0 );
  }
  if( instk[ var ] || vsted[ var ] ) return 1;
  instk[ var ] = true;
  int op = prv[ var ];
  prv[ var ] = len;
  int sum = 0;
  for( int id : v[ var ] ){
    if( !ok[ id ] ) continue;
    int nlen = len;
    for( int i = 0 ; i < rl[ id ].len ; i ++ )
      if( rl[ id ].c[ i ] >= 'a' ){
        nlen ++;
        sum = 1;
        break;
      }
    for( int i = 0 ; i < rl[ id ].len ; i ++ )
      if( rl[ id ].c[ i ] <= 'Z' )
        if( go( rl[ id ].c[ i ] - 'A' , nlen ) ){
          nlen ++;
          sum = 1;
        }
    for( int i = 0 ; i < rl[ id ].len ; i ++ )
      if( rl[ id ].c[ i ] <= 'Z' )
        go( rl[ id ].c[ i ] - 'A' , nlen );
  }
  prv[ var ] = op;
  instk[ var ] = false;
  vsted[ var ] = true;
  return sum;
}
void gogo( int now ){
  if( done[ now ] ) return;
  done[ now ] = true;
  for( int i = 0 ; i < rl[ now ].len ; i ++ ){
    if( rl[ now ].c[ i ] >= 'a' ) continue;
    bool ya = false;
    for( int id : v[ rl[ now ].c[ i ] - 'A' ] ){
      gogo( id );
      if( ok[ id ] ){
        ya = true;
        break;
      }
    }
    if( !ya ) return;
  }
  ok[ now ] = true;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    if( !done[ i ] )
      gogo( i );
  //for( int i = 0 ; i < n ; i ++ )
    //printf( "%d %d\n" , i , ok[ i ] );
  //for( int i = 0 ; i < n ; i ++ )
    //ok[ i ] = true;
  go( 'S' - 'A' , 0 );
  puts( "finite" );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "cyclic.in" , "r" , stdin );
  freopen( "cyclic.out" , "w" , stdout );
#endif
  init();
  solve();
}
