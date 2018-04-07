#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 512
char buf[ N ];
int n;
vector<char> read(){
  vector<char> ret;
  fgets( buf , N , stdin );
  for( int i = 0 ; buf[ i ] ; i ++ )
    if( isalpha( buf[ i ] ) or
        buf[ i ] == '-' or
        buf[ i ] == '*' )
      ret.push_back( buf[ i ] );
  return ret;
}
vector<char> vv[ N ];
int a , b , c , first , rest , nrest;
int stk[ N ] , stksz;
int pos[ 4 ] , hand[ 4 ] = {5,5,4,4};
bool check(){
  for( int i = 0 ; i < n ; i ++ ){
    int ga = vv[ i ][ 0 ] - 'A';
    int gb = vv[ i ][ 1 ] - 'A';
    int gc = vv[ i ][ 2 ] - 'A';
    for( int j = 1 ; j < 4 ; j ++ ){
      int asked = (i + j) & 3;
      if( vv[ i ][ 2 + j ] == '-' ){
        if( (pos[ asked ] >> ga) & 1 )
          return false;
        if( (pos[ asked ] >> gb) & 1 )
          return false;
        if( (pos[ asked ] >> gc) & 1 )
          return false;
      } 
      if( isalpha( vv[ i ][ 2 + j ] ) ){
        int who = vv[ i ][ 2 + j ] - 'A';
        if( who != ga and who != gb and who != gc )
          return false;
        if( ((pos[ asked ] >> who) & 1) == 0 )
          return false;
      }
      if( vv[ i ][ 2 + j ] == '*' ){
        bool has = false;
        if( (pos[ asked ] >> ga) & 1 ) has = true;
        if( (pos[ asked ] >> gb) & 1 ) has = true;
        if( (pos[ asked ] >> gc) & 1 ) has = true;
        if( not has ) return false;
      }
    }
  }
  return true;
}
bool dfs( int cur ){ 
  if( cur == stksz )
    return check();
  for( int i = 1 ; i < 4 ; i ++ ){
    if( hand[ i ] == 0 ) continue;
    hand[ i ] --;
    pos[ i ] ^= (1 << stk[ cur ]);
    bool ret = dfs( cur + 1 );
    pos[ i ] ^= (1 << stk[ cur ]);
    hand[ i ] ++;
    if( ret ) return true;
  }
  return false;
}
void go( int na , int nb , int nc ){
  nrest = rest ^ (1 << na) ^ (1 << nb) ^ (1 << nc);
  stksz = 0;
  for( int i = 0 ; i < 21 ; i ++ )
    if( (nrest >> i) & 1 )
      stk[ stksz ++ ] = i;
  if( dfs( 0 ) ){
    a |= (1 << na);
    b |= (1 << nb);
    c |= (1 << nc);
  }
}
void solve(){
  pos[ 0 ] = first;
  rest = ((1 << 21) - 1) ^ first;
  
  for( int i = 0 ; i < 6 ; i ++ ) if( (rest >> i) & 1 )
    for( int j = 6 ; j < 12 ; j ++ ) if( (rest >> j) & 1 )
      for( int k = 12 ; k < 21 ; k ++ ) if( (rest >> k) & 1 ){
        go( i , j , k );
        if( __builtin_popcount( a ) > 1 and
            __builtin_popcount( b ) > 1 and
            __builtin_popcount( c ) > 1 )
          return;
      }
}
int main(){
  fgets( buf , N , stdin );
  sscanf( buf , "%d" , &n );
  vector<char> ret = read();
  for( auto cc : ret )
    first |= (1 << (cc - 'A'));
  for( int i = 0 ; i < n ; i ++ )
    vv[ i ] = read();

  solve();

  for( int x : {a, b, c} )
    if( __builtin_popcount( x ) == 1 )
      putchar( __lg( x ) + 'A' );
    else
      putchar( '?' );
  puts( "" );
}
