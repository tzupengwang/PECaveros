#include <bits/stdc++.h>
using namespace std;
#define N 5050
#define K 3030
typedef long long LL;
LL n , k , a[ N ];
inline LL getint(){
  LL _x=0; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9') ) _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
LL ps[ N ] , ss[ N ];
LL sum( int lft , int rgt ){
  LL ret = ps[ rgt ] - ps[ lft - 1 ];
  ret -= ( ss[ rgt ] - ss[ lft - 1 ] ) * ( lft - 1 );
  return ret;
}
void init(){
  n = getint();
  k = getint();
  //n = 5000;
  //k = 3000;
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    //a[ i ] = rand() % 1000 + 1;
    ps[ i ] = ps[ i - 1 ] + a[ i ] * i;
    ss[ i ] = ss[ i - 1 ] + a[ i ];
  }
}
LL dp[ N ][ K ];
const LL inf = 1000000000000000LL;
void go( int id , int lft , int rgt , int lp , int rp ){
  if( lft > rgt ) return;
  int mid = ( lft + rgt ) >> 1;
  int bst = lp;
  for( int i = lp ; i <= rp ; i ++ ){
    LL tdp = dp[ i - 1 ][ mid - 1 ] + sum( i , id );
    if( tdp < dp[ id ][ mid ] ){
      dp[ id ][ mid ] = tdp;
      bst = i;
    }
  }
  go( id , lft , mid - 1 , lp , bst );
  go( id , mid + 1 , rgt , bst , rp );
}
void solve(){
  for( int i = 0 ; i <= k ; i ++ )
    dp[ 0 ][ i ] = dp[ 1 ][ i ] = inf;
  dp[ 0 ][ 0 ] = 0;
  dp[ 1 ][ 1 ] = sum( 1 , 1 );
  for( int i = 2 ; i <= n ; i ++ ){
    for( int j = 0 ; j <= k ; j ++ )
      dp[ i ][ j ] = inf;
    go( i , 1 , min( (LL)i , k ) , 1 , i );
  }
  printf( "%lld\n" , dp[ n ][ k ] );
}
int main(){
  init();
  solve();
}
