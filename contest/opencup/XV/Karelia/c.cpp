#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 3030
const int mod = 1000000007;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int mpow( int a , int b ){
  int ret = 1;
  while( b ){
    if( b & 1 ) ret = mul( ret , a );
    a = mul( a , a );
    b >>= 1;
  }
  return ret;
}
inline int inv( int a ){
  return mpow( a , mod - 2 );
}
int C[ N ][ N ];
void build(){
  for( int i = 0 ; i < N ; i ++ )
    C[ i ][ 0 ] = C[ i ][ i ] = 1;
  for( int i = 2 ; i < N ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      C[ i ][ j ] = add( C[ i - 1 ][ j ] ,
                         C[ i - 1 ][ j - 1 ] );
}
int n , d , a[ N ] , p[ N ] , sz[ N ] , dp[ N ];
void init(){
  scanf( "%d%d" , &n , &d );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    for( int j = (i - 1) * d + 2 ;
         j <= n and j <= i * d + 1 ;
         j ++ )
      p[ j ] = i;
  }
  for( int i = 1 ; i <= n ; i ++ )
    sz[ i ] = 0;
  for( int i = n ; i >= 1 ; i -- ){
    sz[ i ] ++;
    sz[ p[ i ] ] += sz[ i ];
    dp[ i ] = 1;
    int res = sz[ i ] - 1;
    for( int j = (i - 1) * d + 2 ;
         j <= n and j <= i * d + 1 ;
         j ++ ){
      dp[ i ] = mul( dp[ i ] ,
                     mul( C[ res ][ sz[ j ] ] , dp[ j ] ) );
      res -= sz[ j ];
    }
  }
}
int nd[ N ] , vl[ N ] , ressz[ N ] , used[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    used[ i ] = ressz[ i ] = nd[ i ] = 0;
    vl[ i ] = 1;
  }
  nd[ 1 ] = n - 1;
  vl[ 1 ] = dp[ 1 ];
  ressz[ 1 ] = n - 1;
  int ans = dp[ 1 ];
  used[ 1 ] = 1;
  for( int i = 2 ; i <= n ; i ++ ){
    int prt = p[ i ];
    int prt_vl = a[ prt ];
    nd[ prt_vl ] -= sz[ i ];
    vl[ prt_vl ] = mul( vl[ prt_vl ] ,
                        inv( mul( C[ ressz[ prt_vl ] ][ sz[ i ] ] , dp[ i ] ) ) );
    ressz[ prt_vl ] -= sz[ i ];

    nd[ a[ i ] ] = sz[ i ];
    vl[ a[ i ] ] = dp[ i ];
    int tans = 1 , useful = 0;
    //printf( "%d : \n" , i );
    for( int j = n ; j >= 1 ; j -- ){
      if( nd[ j ] ){
        //printf( "> %d need %d\n" , j , nd[ j ] );
        if( useful < nd[ j ] ){
          //puts( "gg" );
          tans = 0;
        }else{
          tans = mul( tans , mul( C[ useful ][ nd[ j ] ] , vl[ j ] ) );
          //printf( "tans = %d\n" , tans );
          useful -= nd[ j ];
        }
      }
      if( !used[ j ] )
        useful ++;
    }
    used[ a[ i ] ] = 1;
    ans = sub( ans , tans );
    nd[ a[ i ] ] --;
    ressz[ a[ i ] ] = sz[ i ] - 1;
  }
  printf( "%d\n" , ans );
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
