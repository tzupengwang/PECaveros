#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , m , s , f;
int t[ N ] , x[ N ];
int dp[ N ][ 2 ];
int inv( int xx ){
  return m - xx + 1;
}
int cal( int lb , int rb ){
  dp[ lb ][ 0 ] = abs( x[ lb ] - x[ lb - 1 ] );
  dp[ lb ][ 1 ] = abs( inv( x[ lb ] ) - x[ lb - 1 ] );
  for( int i = lb + 1 ; i <= rb ; i ++ ){
    dp[ i ][ 0 ] = min(
        abs( x[ i ] - x[ i - 1 ] ) + dp[ i - 1 ][ 0 ] ,
        abs( x[ i ] - inv( x[ i - 1 ] ) ) + dp[ i - 1 ][ 1 ] );
    dp[ i ][ 1 ] = min(
        abs( inv( x[ i ] ) - x[ i - 1 ] ) + dp[ i - 1 ][ 0 ] ,
        abs( inv( x[ i ] ) - inv( x[ i - 1 ] ) ) + dp[ i - 1 ][ 1 ] );
  }
  return min( abs( x[ rb ] - x[ rb + 1 ] ) + dp[ rb ][ 0 ] ,
              abs( inv( x[ rb ] ) - x[ rb + 1 ] ) + dp[ rb ][ 1 ] );
}
int solve(){
  int ans = 0;
  for( int lb = 1 , rb = 1 ; lb <= n ; lb = rb ){
    if( t[ lb ] == 1 ){
      if( t[ lb + 1 ] == 1 )
        ans += abs( x[ lb ] - x[ lb + 1 ] );
      rb = lb + 1;
      continue;
    }
    rb = lb;
    while( rb <= n and t[ rb ] == 2 ) rb ++;
    sort( x + lb , x + rb );
    int cst1 = cal( lb , rb - 1 );
    reverse( x + lb , x + rb );
    int cst2 = cal( lb , rb - 1 );
    reverse( x + lb , x + rb );
    ans += min( cst1 , cst2 );
  }
  return ans;
}
int main(){
  cin >> n >> m >> s >> f;
  t[ 1 ] = 1; x[ 1 ] = s;
  for( int i = 2 ; i <= n ; i ++ )
    cin >> t[ i ] >> x[ i ];
  t[ n + 1 ] = 1; x[ n + 1 ] = f;
  cout << solve() << endl;
  exit(0);
  if( t[ 2 ] == 1 )
    dp[ 1 ][ 0 ] = abs( s - x[ 2 ] );
  else{
    dp[ 1 ][ 0 ] = abs( s - x[ 2 ] );
    dp[ 1 ][ 1 ] = abs( s - ( m - x[ 2 ] + 1 ) );
  }
  for( int i = 2 ; i < n ; i ++ )
    if( t[ i ] == 1 ){
      if( t[ i + 1 ] == 1 )
        dp[ i ][ 0 ] = abs( x[ i ] - x[ i + 1 ] ) + dp[ i - 1 ][ 0 ];
      else{
        dp[ i ][ 0 ] = abs( x[ i ] - x[ i + 1 ] ) + dp[ i - 1 ][ 0 ];
        dp[ i ][ 1 ] = abs( x[ i ] - ( m - x[ i + 1 ] + 1 ) ) + dp[ i - 1 ][ 0 ];
      }
    }else{
      if( t[ i + 1 ] == 1 ){
        dp[ i ][ 0 ] = min(
            abs( x[ i ] - x[ i + 1 ] ) + dp[ i - 1 ][ 0 ] ,
            abs( ( m - x[ i ] + 1 ) - x[ i + 1 ] ) + dp[ i - 1 ][ 1 ] );
      }else{
        dp[ i ][ 0 ] = min(
            abs( x[ i ] - x[ i + 1 ] ) + dp[ i - 1 ][ 0 ] ,
            abs( ( m - x[ i ] + 1 ) - x[ i + 1 ] ) + dp[ i - 1 ][ 1 ] );
        dp[ i ][ 1 ] = min(
            abs( x[ i ] - ( m - x[ i + 1 ] + 1 ) ) + dp[ i - 1 ][ 0 ] ,
            abs( ( m - x[ i ] + 1 ) - ( m - x[ i + 1 ] + 1 ) ) + dp[ i - 1 ][ 1 ] );
      }
    }
  int ans = 0;
  if( t[ n ] == 1 )
    ans = abs( x[ n ] - f ) + dp[ n - 1 ][ 0 ];
  else
    ans = min( abs( x[ n ] - f ) + dp[ n - 1 ][ 0 ],
               abs( ( m - x[ n ] + 1 ) - f ) + dp[ n - 1 ][ 1 ] );
  cout << ans << endl;
}
