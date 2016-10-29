#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
LL n , m , a , b , x[ N ] , x2[ N ] , ans;
LL sx[ N ] , posx[ N ];
void init(){
  scanf( "%lld%lld%lld%lld" , &n , &m , &a , &b );
  ans = 0;
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%lld" , &x[ i ] );
  for( int i = 1 ; i <= m ; i ++ ){
    LL xi , yi; scanf( "%lld%lld" , &xi , &yi );
    ans += b * yi;
    x2[ i ] = xi;
  }
  x2[ 0 ]     = -1000000000;
  x2[ m + 1 ] = +1000000000;
  sort( x + 1 , x + n + 1 );
  sort( x2 + 1 , x2 + m + 1 );
  for( int i = 1 ; i <= m ; i ++ )
    sx[ i ] = sx[ i - 1 ] + x2[ i ];
  for( int i = 1 ; i <= n ; i ++ ){
    posx[ i ] = 0;
    while( posx[ i ] < m && x2[ posx[ i ] + 1 ] <= x[ i ] )
      posx[ i ] ++;
  }
}
LL dp[ N ][ N ];
#define INF 10000000000000000ll
inline LL cost( LL idx , LL pl , LL pr ){
  LL xx = pr - pl + 1 , flr = a / b;
  LL candl = max( pl - 1 , pr - ( xx + flr ) / 2 );
  LL candr = min( pr + 1 , pl + ( xx + flr ) / 2 );
  //printf( "%lld %lld %lld : %lld %lld %lld %lld\n" , idx , pl , pr , candl , candr , x2[ candl ] , x2[ candr ] );
  if( x[ idx ] < x2[ candl ] ){
    LL ncst = a * abs( x2[ candl ] - x[ idx ] );
    LL bl = pl , br = pr;
    br = min( br , candl );
    if( bl <= br )
      ncst += b * ( x2[ candl ] * ( br - bl + 1 ) - ( sx[ br ] - sx[ bl - 1 ] ) );
    bl = pl; br = pr;
    bl = max( bl , candl + 1 );
    if( bl <= br )
      ncst += b * ( - x2[ candl ] * ( br - bl + 1 ) + ( sx[ br ] - sx[ bl - 1 ] ) );
    return ncst;
  }
  if( x[ idx ] > x2[ candr ] ){
    LL ncst = a * abs( x2[ candr ] - x[ idx ] );
    LL bl = pl , br = pr;
    br = min( br , candr );
    if( bl <= br )
      ncst += b * ( x2[ candr ] * ( br - bl + 1 ) - ( sx[ br ] - sx[ bl - 1 ] ) );
    bl = pl; br = pr;
    bl = max( bl , candr + 1 );
    if( bl <= br )
      ncst += b * ( - x2[ candr ] * ( br - bl + 1 ) + ( sx[ br ] - sx[ bl - 1 ] ) );
    return ncst;
  }
  LL ncst = 0;
  LL bl = pl , br = pr;
  br = min( br , posx[ idx ] );
  if( bl <= br )
    ncst += b * ( ( br - bl + 1 ) * x[ idx ] - ( sx[ br ] - sx[ bl - 1 ] ) );
  bl = pl , br = pr;
  bl = max( bl , posx[ idx ] + 1 );
  if( bl <= br )
    ncst += b * ( sx[ br ] - sx[ bl - 1 ] - ( br - bl + 1 ) * x[ idx ] );
  return ncst;
}
void go( int i , int l , int r , int ql , int qr ){
  if( l > r ) return;
  int mid = ( l + r ) >> 1 , bst = ql;
  dp[ i ][ mid ] = dp[ i - 1 ][ mid ];
  for( int ii = ql ; ii <= min( mid , qr ) ; ii ++ ){
    LL tdp = dp[ i - 1 ][ ii - 1 ] + cost( i , ii , mid );
    //printf( "%d %d from %d %d dp=%lld cost %lld get %lld\n" ,
            //i , mid , i - 1 , ii - 1 , dp[ i - 1 ][ ii - 1 ] ,
            //cost( i , ii , mid ) , tdp );
    if( tdp < dp[ i ][ mid ] ){
      dp[ i ][ mid ] = tdp;
      bst = ii;
    }
  }
  go( i , l , mid - 1 , ql , bst );
  go( i , mid + 1 , r , bst , qr );
}
int _cs;
void solve(){
  dp[ 1 ][ 0 ] = 0;
  for( int i = 1 ; i <= m ; i ++ )
    dp[ 1 ][ i ] = cost( 1 , 1 , i );
  for( int i = 2 ; i <= n ; i ++ )
    go( i , 1 , m , 1 , m );
  printf( "Case #%d: %lld\n" , ++ _cs , dp[ n ][ m ] + ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
