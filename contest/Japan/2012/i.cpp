#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
int w , n , a[ N ];
bool init(){
#ifdef TEST
  w = 80000;
  n = 50000;
#else
  scanf( "%d%d" , &w , &n );
#endif
  if( w == 0 and n == 0 )
    return false;
  for( int i = 1 ; i <= n ; i ++ ){
#ifdef TEST
    a[ i ] = 1;
#else
    scanf( "%d" , &a[ i ] );
#endif
  }
  return true;
}
int dp[ N ] , s[ N ] , bst[ N ];
int f( int i , int j ){ // i .. j
  if( i == j ) return -1;
  int tot = s[ j ] - s[ i - 1 ];
  if( tot > w ) return -1;
  int res = w - tot;
  if( res < j - i ) return -1;
  return res / ( j - i ) + ( res % ( j - i ) != 0 );
}
void dq2( int l , int r , int ql , int qr ){
  if( ql > qr ) return;
  int qmid = ( ql + qr ) >> 1;
  int tbst = -1 , curbst = N;
  for( int i = max( 1 , l ) ; i <= min( r , qmid ) ; i ++ ){
    int cst = f( i , qmid );
    if( cst == -1 ) continue;
    int tdp = max( cst , dp[ i - 1 ] );
    if( tdp < curbst ){
      curbst = tdp;
      dp[ qmid ] = min( dp[ qmid ] , curbst );
      tbst = i;
    }
  }
  if( tbst == -1 ){
    dq2( l , r , ql , qmid - 1 );
    return;
  }
  dq2( l , tbst , ql , qmid - 1 );
  dq2( tbst , r , qmid + 1 , qr );
}
void dq( int l , int r ){
  if( l == r ) return;
  int mid = ( l + r ) >> 1;
  dq( l , mid );
  dq2( l , mid , mid + 1 , r );
  dq( mid + 1 , r ); 
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    dp[ i ] = N;
  dp[ 0 ] = 1;
  //dp[ 1 ] = 1;
  for( int i = 1 ; i <= n ; i ++ )
    s[ i ] = s[ i - 1 ] + a[ i ];
  dq( 0 , n );
  //for( int i = 2 ; i <= n ; i ++ ){
    //bst[ i ] = bst[ i - 1 ];
    //for( int j = max( 1 , bst[ i ] ) ; j < i ; j ++ ){
      //int cst = f( j , i );
      //if( cst == -1 ) continue;
      //int tdp = max( dp[ j - 1 ] , cst );
      //if( tdp < dp[ i ] ){
        //dp[ i ] = tdp;
        //bst[ i ] = j;
      //}
    //}
  //}
  int ans = min( dp[ n ] , dp[ n - 1 ] );
  for( int i = n - 1 ; i >= 1 ; i -- ){
    if( f( i , n ) == -1 ) break;
    ans = min( ans , dp[ i - 1 ] );
  }
  printf( "%d\n" , ans );
}
int main(){
  while( init() ){
    solve();
#ifdef TEST
    break;
#endif
  }
}
