#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 111
typedef long long LL;
const LL mod = 1000000000;
inline LL add( LL a , LL b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline LL mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int n;
vector< int > v[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi; scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
}
int dp[ N ][ N ][ 2 ];
int tmp[ N ][ 2 ];
void go( int now , int prt ){
  dp[ now ][ 0 ][ 0 ] = 1;
  dp[ now ][ 1 ][ 1 ] = 1;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    go( son , now );
    for( int i = 0 ; i <= n ; i ++ )
      for( int j = 0 ; j < 2 ; j ++ ){
        tmp[ i ][ j ] = dp[ now ][ i ][ j ];
        dp[ now ][ i ][ j ] = 0;
      }
    for( int he = 0 ; he <= n ; he ++ )
      for( int heo = 0 ; heo < 2 ; heo ++ ){
        if( dp[ son ][ he ][ heo ] == 0 ) continue;
        for( int my = 0 ; he + my - 1 <= n ; my ++ )
          for( int myo = 0 ; myo < 2 ; myo ++ ){
            if( tmp[ my ][ myo ] == 0 ) continue;
            int nxto = myo;
            int nxtc = he + my;
            int vl = mul( dp[ son ][ he ][ heo ] , tmp[ my ][ myo ] );
            dp[ now ][ nxtc ][ nxto ] = add( dp[ now ][ nxtc ][ nxto ] ,
                                             vl );
            //printf( "%d %d %d from %d %d , %d %d\n" , now , nxto , nxtc,
                    //he , heo , my , myo );
            if( heo > 0 && myo > 0 ){
              nxtc --;
              vl = mul( dp[ son ][ he ][ heo ] , tmp[ my ][ myo ] );
              dp[ now ][ nxtc ][ nxto ] = add( dp[ now ][ nxtc ][ nxto ] ,
                                               vl );
            }
          }
      }
  }
}
void solve(){
  go( 1 , 1 );
  //for( int i = 1 ; i <= n ; i ++ )
    //for( int j = 0 ; j <= n ; j ++ )
      //for( int k = 0 ; k < 2 ; k ++ )
        //if( dp[ i ][ j ][ k ] )
          //printf( "%d %d %d : %d\n" , i , j , k , dp[ i ][ j ][ k ] );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d\n" , (int)add( dp[ 1 ][ i ][ 0 ] , dp[ 1 ][ i ][ 1 ] ) );
}
int main(){
  freopen( "subtrees.in" , "r" , stdin );
  freopen( "subtrees.out" , "w" , stdout );
  init();
  solve();
}
