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
int pos[ 4 ] , must[ 4 ];
vector<char> vv[ N ];
int a , b , c;
int hand[4] = {5,5,4,4};
void go( int now ){
  for( int i = 1 ; i < 4 ; i ++ )
    if( __builtin_popcount( pos[ i ] ) == hand[ i ] )
      must[ i ] = pos[ i ];
  if( now == n ){
    int aa = 0 , bb = 0 , cc = 0;
    {
      for( int i = 0 ; i < 4 ; i ++ )
        aa |= (must[ i ] & ((1 << 6) - 1));
      aa ^= ((1 << 6) - 1);
      if( !aa ) return;
    }
    {
      for( int i = 0 ; i < 4 ; i ++ )
        bb |= (must[ i ] & (((1 << 6) - 1) << 6));
      bb ^= (((1 << 6) - 1) << 6);
      if( !bb ) return;
    }
    {
      for( int i = 0 ; i < 4 ; i ++ )
        cc |= (must[ i ] & (((1 << 9) - 1) << 12));
      cc ^= (((1 << 9) - 1) << 12);
      if( !cc ) return;
    }
    if( aa == (aa & (-aa)) ) a |= aa;
    if( bb == (bb & (-bb)) ) b |= bb;
    if( cc == (cc & (-cc)) ) c |= cc;
    aa = bb = cc = 0;
    {
      for( int i = 0 ; i < 4 ; i ++ )
        aa |= (pos[ i ] & ((1 << 6) - 1));
      aa ^= ((1 << 6) - 1);
    }
    {
      for( int i = 0 ; i < 4 ; i ++ )
        bb |= (pos[ i ] & (((1 << 6) - 1) << 6));
      bb ^= (((1 << 6) - 1) << 6);
    }
    {
      for( int i = 0 ; i < 4 ; i ++ )
        cc |= (pos[ i ] & (((1 << 9) - 1) << 12));
      cc ^= (((1 << 9) - 1) << 12);
    }
    a |= aa;
    b |= bb;
    c |= cc;
    return;
  }
  int ppos[ 4 ] , pmust[ 4 ];
  for( int i = 0 ; i < 4 ; i ++ ){
    ppos[ i ] = pos[ i ];
    pmust[ i ] = must[ i ];
  }

  int ga = vv[ now ][ 0 ] - 'A';
  int gb = vv[ now ][ 1 ] - 'A';
  int gc = vv[ now ][ 2 ] - 'A';

  int asking = now & 3;

  bool got = false;
  for( int i = 1 ; i < 4 ; i ++ ){
    int asked = (asking + i) & 3;
    if( vv[ now ][ 2 + i ] == '-' ){
      pos[ asked ] &= (~(1 << ga));
      pos[ asked ] &= (~(1 << gb));
      pos[ asked ] &= (~(1 << gc));
      continue;
    }
    for( int cand : {ga, gb, gc} ){
      if( vv[ now ][ 2 + i ] != '*' and
          vv[ now ][ 2 + i ] - 'A' != cand )
        continue;
      if( ((pos[ asked ] >> cand) & 1) ){
        int spos[ 4 ] , smust[ 4 ];
        for( int j = 0 ; j < 4 ; j ++ ){
          spos[ j ] = pos[ j ];
          smust[ j ] = must[ j ];
        }
        for( int j = 0 ; j < 4 ; j ++ )
          if( j != asked )
            pos[ j ] &= (~(1 << cand));
        must[ asked ] |= (1 << cand);
        go( now + 1 );
        for( int j = 0 ; j < 4 ; j ++ ){
          pos[ j ] = spos[ j ];
          must[ j ] = smust[ j ];
        }
      }
    }
    got = true;
  }
  if( not got ) go( now + 1 );

  for( int i = 0 ; i < 4 ; i ++ ){
    pos[ i ] = ppos[ i ];
    must[ i ] = pmust[ i ];
  }
}
int main(){
  fgets( buf , N , stdin );
  sscanf( buf , "%d" , &n );
  vector<char> ret = read();
  for( auto cc : ret )
    pos[ 0 ] |= (1 << (cc - 'A'));
  for( int i = 1 ; i < 4 ; i ++ )
    pos[ i ] = ((1 << 21) - 1) ^ pos[ 0 ];
  for( int i = 0 ; i < n ; i ++ )
    vv[ i ] = read();
  must[ 0 ] = pos[ 0 ];
  go( 0 );
  for( int x : {a, b, c} )
    if( __builtin_popcount( x ) == 1 )
      putchar( __lg( x ) + 'A' );
    else
      putchar( '?' );
  puts( "" );
}
