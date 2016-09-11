#include <bits/stdc++.h>
using namespace std;
#define N 222
int n , sn , sm , len;
char cmd[ N ] , c[ N ][ N ];
void reduce(){
  len = strlen( cmd );
  for( int i = 1 ; i < len ; i ++ )
    if( len % i == 0 ){
      bool okay = true;
      for( int j = 0 ; j < len ; j ++ )
        if( cmd[ j ] != cmd[ j % i ] ){
          okay = false;
          break;
        }
      if( okay ){
        len = i;
        return;
      }
    }
}
int dn[]={0,0,-1,1};
int dm[]={-1,1,0,0};
int trans( char ctmp ){
  if( ctmp == '<' ) return 0;
  if( ctmp == '>' ) return 1;
  if( ctmp == '^' ) return 2;
  if( ctmp == 'v' ) return 3;
  assert( false );
  return -1;
}
int dir[ N ];
void init(){
  scanf( "%d" , &n );
  scanf( "%s" , cmd );
  reduce();
  for( int i = 0 ; i < len ; i ++ )
    dir[ i ] = trans( cmd[ i ] );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , c[ i ] + 1 );
    for( int j = 1 ; j <= n ; j ++ )
      if( c[ i ][ j ] == 'R' ){
        sn = i , sm = j;
        c[ i ][ j ] = '.';
      }
  }
}
int tag[ N ][ N ][ N ];
#define M 8000080
int px[ M ];
int py[ M ];
int nxt( int xn , int xm , int icmd ){
  for( int i = icmd ; i < icmd + len ; i ++ ){
    int nxtn = xn + dn[ dir[ i % len ] ];
    int nxtm = xm + dm[ dir[ i % len ] ];
    if( c[ nxtn ][ nxtm ] == '#' ) continue;
    return i % len;
  }
  return -1;
}
const int BS = 1313131;
const int mod = 1000000007;
inline int mul( long long a , long long b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int add( long long a , long long b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( long long a , long long b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
int hs[ M ] , bs[ M ];
inline int hsh( int tl , int tr ){
  return sub( hs[ tr ] , mul( hs[ tl - 1 ] , bs[ tr - tl + 1 ] ) );
}
void cal( int l , int r ){
  int tlen = r - l;
  bs[ 0 ] = 1;
  for( int i = 1 ; i <= tlen ; i ++ )
    bs[ i ] = mul( bs[ i - 1 ] , BS );
  for( int i = 1 ; i <= tlen ; i ++ )
    hs[ i ] = add( mul( hs[ i - 1 ] , BS ) ,
                   px[ l + i - 1 ] * 201 + py[ l + i - 1 ] );
  for( int i = 1 ; i < tlen ; i ++ )
    if( tlen % i == 0 ){
      if( hsh( 1 , i ) == hsh( tlen - i + 1 , tlen ) &&
          hsh( i + 1 , tlen ) == hsh( 1 , tlen - i ) ){
        printf( "%d\n" , i );
        exit( 0 );
      }
    }
  printf( "%d\n" , tlen );
  exit( 0 );
}
void solve(){
  int stmp = 1;
  for( int i = 0 ; ; ){
    int nxtcmd = nxt( sn , sm , i );
    if( nxtcmd == -1 ){
      puts( "1" );
      exit( 0 );
    }
    if( tag[ sn ][ sm ][ nxtcmd ] ){
      cal( tag[ sn ][ sm ][ nxtcmd ] , stmp );
      printf( "%d\n" , stmp - tag[ sn ][ sm ][ nxtcmd ] );
      exit( 0 );
    }
    px[ stmp ] = sn;
    py[ stmp ] = sm;
    tag[ sn ][ sm ][ nxtcmd ] = stmp ++;
    sn += dn[ dir[ nxtcmd ] ];
    sm += dm[ dir[ nxtcmd ] ];
    i = ( nxtcmd + 1 ) % len;
  }
}
int main(){
  init();
  solve();
}
