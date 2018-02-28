#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
const int mod = 1000000009;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
char c[ 3 ][ N ];
int q[ 3 ][ N ] , len[ N ];
void init(){
  for( int i = 0 ; i < 3 ; i ++ ){
    scanf( "%s" , c[ i ] );
    len[ i ] = strlen( c[ i ] );
    q[ i ][ len[ i ] ] = 0;
    for( int j = len[ i ] - 1 ; j >= 0 ; j -- )
      q[ i ][ j ] = q[ i ][ j + 1 ] + (c[ i ][ j ] == '?');
  }
}
int dp[ 8 ][ N ] , gt[ 8 ][ N ] , stmp;
int bt[ 8 ] , pw[ N ];
int way[ 27 ][ 27 ][ 27 ][ 8 ];
int eq[ 27 ][ 27 ];
int df[ 27 ][ 27 ];
int DP( int same , int now ){
  if( !same ) return 1;
  if( bt[ same ] == 1 ){
    int ct = q[ __lg( same ) ][ now ];
    return pw[ ct ];
  }
  if( gt[ same ][ now ] == stmp )
    return dp[ same ][ now ];
  gt[ same ][ now ] = stmp;
  int osame = same;
  {
    int pre = -1;
    for( int i = 0 ; i < 3 ; i ++ )
      if( (same >> i) & 1 ){
        if( len[ i ] == now ){
          if( len[ i ] <= pre )
            return dp[ osame ][ now ] = 0;
          same ^= (1 << i);
        }
        pre = len[ i ];
      }
  }
  if( !same ) return dp[ osame ][ now ] = 0;
  if( same != osame )
    return dp[ osame ][ now ] = DP( same , now );
  int ret = 0;
  if( bt[ same ] == 3 ){
    int v[ 3 ];
    for( int i = 0 ; i < 3 ; i ++ )
      if( c[ i ][ now ] == '?' )
        v[ i ] = 26;
      else
        v[ i ] = c[ i ][ now ] - 'a';
    for( int i = 2 ; i < 8 ; i ++ ){
      if( !way[ v[ 0 ] ][ v[ 1 ] ][ v[ 2 ] ][ i ] )
        continue;
      ret = add( ret , mul( way[ v[ 0 ] ][ v[ 1 ] ][ v[ 2 ] ][ i ] ,
                            mul( DP( i        , now + 1 ) ,
                                 DP( same ^ i , now + 1 ) ) ) );
    }
    if( way[ v[ 0 ] ][ v[ 1 ] ][ v[ 2 ] ][ 1 ] ){
      ret = add( ret , mul( way[ v[ 0 ] ][ v[ 1 ] ][ v[ 2 ] ][ 1 ] ,
                            mul( DP( 1 , now + 1 ) ,
                                 mul( DP( 2 , now + 1 ) ,
                                      DP( 4 , now + 1 ) ) ) ) );
    }
  }else{
    int v[ 2 ] , vt = 0;
    for( int i = 0 ; i < 3 ; i ++ )
      if( (same >> i) & 1 ){
        if( c[ i ][ now ] == '?' )
          v[ vt ++ ] = 26;
        else
          v[ vt ++ ] = c[ i ][ now ] - 'a';
      }
    ret = add( ret ,
               mul( eq[ v[ 0 ] ][ v[ 1 ] ] , DP( same , now + 1 ) ) );
    int ww = df[ v[ 0 ] ][ v[ 1 ] ];
    for( int i = 0 ; i < 3 ; i ++ )
      if( (same >> i) & 1 )
        ww = mul( ww , DP( (1 << i) , now + 1 ) );
    ret = add( ret , ww );
  }
  return dp[ osame ][ now ] = ret;
}
void solve(){
  ++ stmp;
  printf( "%d\n" , DP( 7 , 0 ) );
}
int main(){
  for( int i = 1 ; i < 8 ; i ++ )
    bt[ i ] = bt[ i >> 1 ] + (i & 1);
  for( int i = 0 ; i < 26 ; i ++ )
    for( int j = i ; j < 26 ; j ++ ){
      for( int k = j ; k < 26 ; k ++ ){
        for( int msk = 0 ; msk < 8 ; msk ++ ){
          int ni = i , nj = j , nk = k;
          if( (msk >> 0) & 1 ) ni = 26;
          if( (msk >> 1) & 1 ) nj = 26;
          if( (msk >> 2) & 1 ) nk = 26;
          if( i == j and j == k )
            way[ ni ][ nj ][ nk ][ 7 ] ++;
          else if( i == j )
            way[ ni ][ nj ][ nk ][ 3 ] ++;
          else if( j == k )
            way[ ni ][ nj ][ nk ][ 6 ] ++;
          else
            way[ ni ][ nj ][ nk ][ 1 ] ++;
        }
      }
      for( int msk = 0 ; msk < 8 ; msk ++ ){
        int ni = i , nj = j;
        if( (msk >> 0) & 1 ) ni = 26;
        if( (msk >> 1) & 1 ) nj = 26;
        if( (msk >> 2) & 1 ){
          if( i == j ){
            eq[ ni ][ nj ] ++;
          }else{
            df[ ni ][ nj ] ++;
          }
        }
      }
    }
  pw[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ )
    pw[ i ] = mul( pw[ i - 1 ] , 26 );
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
