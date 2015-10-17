#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int __ = 1;
ll mygcd( ll _a , ll _b ){
  ll _r;
  while( _b ){
    _r = _a % _b;
    _a = _b;
    _b = _r;
  }
  return _a;
}
class Frac{
public:
  ll up, dn;
  Frac(){
    up = 0;
    dn = 1;
  }
  Frac( ll tmp ){
    up = tmp;
    dn = 1;
  }
  Frac( ll _up , ll _dn ){
    up = _up;
    dn = _dn;
  }
  Frac operator+( const Frac& n2 ) const{
    ll ndn = dn * n2.dn;
    ll nup = up * n2.dn + dn * n2.up;
    ll tg = mygcd( ndn , nup );
    ndn /= tg;
    nup /= tg;
    Frac tnum( nup , ndn );
    return tnum;
  }
  Frac operator-( const Frac& n2 ) const{
    ll ndn = dn * n2.dn;
    ll nup = up * n2.dn - dn * n2.up;
    ll tg = mygcd( ndn , nup );
    ndn /= tg;
    nup /= tg;
    Frac tnum( nup , ndn );
    return tnum;
  }
  bool operator<( const Frac& n2 ) const{
    return up * n2.dn < dn * n2.up;
  }
  bool operator>( const Frac& n2 ) const{
    return up * n2.dn > dn * n2.up;
  }
  bool operator==( const Frac& n2 ) const{
    return up * n2.dn == dn * n2.up;
  }
};
#define N 110
int n , m , s , t;
Frac dist[ N ][ N ] , ans;
Frac zero( 0 , 1 );
int deg[ N ];
vector<int> odd;
void init(){
  scanf( "%d%d%d%d" , &n , &m , &s , &t );
  for( int i = 1 ; i <= n ; i ++ ){
    deg[ i ] = 0;
  }
  odd.clear();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      Frac tn( ( i == j ? 0 : 100000000 ) , 1 );
      dist[ i ][ j ] = tn;
    }
  ans = zero;
  while( m -- ){
    int a , b , _u , _v;
    scanf( "%d%d%d%d"  , &a , &b , &_u , &_v );
    Frac tn( _v , _u );
    if( tn < dist[ a ][ b ] ) dist[ a ][ b ] = tn;
    if( tn < dist[ b ][ a ] ) dist[ b ][ a ] = tn;
    ans = ans + tn;
    deg[ a ] ++;
    deg[ b ] ++;
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( deg[ i ] % 2 == 1 ){
      if( i == s || i == t ) continue;
      odd.push_back( i );
    }
  for( int k = 1 ; k <= n ; k ++ )
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        if( dist[ i ][ k ] + dist[ k ][ j ] < dist[ i ][ j ] )
          dist[ i ][ j ] = dist[ i ][ k ] + dist[ k ][ j ];
}
#define K 30
int on , hon;
Frac cal( vector<int>& tv ){
  Frac tvl( 0 , 1 );
  for( int i = 0 ; i < on ; i += 2 )
    tvl = tvl + dist[ tv[ i ] ][ tv[ i + 1 ] ];
  return tvl;
}
Frac test(){
  Frac tans = cal( odd );
//  for( int i = 0 ; i < on ; i ++ ){
  while( true ){
    //printf( "%lld %lld\n" , tans.up , tans.dn );
    bool flag = false;
    for( int j = 0 ; j < hon && !flag ; j ++ )
      for( int k = j + 1 ; k < hon && !flag ; k ++ ){
        int n1 = odd[ j * 2 ] , n2 = odd[ j * 2 + 1 ];
        int m1 = odd[ k * 2 ] , m2 = odd[ k * 2 + 1 ];
        Frac tans1 = tans, tans2 = tans;
        if( dist[ m1 ][ n2 ] + dist[ n1 ][ m2 ] <
            dist[ n1 ][ n2 ] + dist[ m1 ][ m2 ] )
          tans1 = ( tans + dist[ m1 ][ n2 ] + dist[ n1 ][ m2 ] )
                       - dist[ n1 ][ n2 ] - dist[ m1 ][ m2 ];
        if( dist[ m2 ][ n2 ] + dist[ n1 ][ m1 ] <
            dist[ n1 ][ n2 ] + dist[ m1 ][ m2 ] )
          tans2 = ( tans + dist[ m2 ][ n2 ] + dist[ n1 ][ m1 ] )
                       - dist[ n1 ][ n2 ] - dist[ m1 ][ m2 ];
        if( tans1 < tans2 ){
          if( tans1 < tans ){
            swap( odd[ j * 2 ] , odd[ k * 2 ] );
            tans = tans1;
            flag = true;
          }
        }else{
          if( tans2 < tans ){
            swap( odd[ j * 2 ] , odd[ k * 2 + 1 ] );
            tans = tans2;
            flag = true;
          }
        }
      }
    if( !flag ) break;
  }
  return tans;
}
Frac dp[ 1 << 19 ];
bool got[ 1 << 19 ];
Frac solve2(){
  Frac tn( 100000000 , 1 );
  for( int i = 0 ; i < ( 1 << on ) ; i ++ )
    got[ i ] = false;
  got[ 0 ] = true;
  dp[ 0 ] = zero;
  for( int i = 0 ; i < ( 1 << on ) ; i ++ ) if( got[ i ] ){
    for( int j = 0 ; j < on ; j ++ ) if( ( i & ( 1 << j ) ) == 0 )
      for( int k = j + 1 ; k < on ; k ++ ) if( ( i & ( 1 << k ) ) == 0 ){
        Frac tcst = dp[ i ] + dist[ odd[ j ] ][ odd[ k ] ];
        if( !got[ i ^ ( 1 << j ) ^ ( 1 << k ) ] ||
            tcst < dp[ i ^ ( 1 << j ) ^ ( 1 << k ) ] ){
          got[ i ^ ( 1 << j ) ^ ( 1 << k ) ] = true;
          dp[ i ^ ( 1 << j ) ^ ( 1 << k ) ] = tcst;
        }
      }
  }
  return dp[ ( 1 << on ) - 1 ];
}
void solve(){
  Frac nans = ans + ans;
  on = (int)odd.size();
  if( on <= 18 ){
    nans = ans + solve2();
    printf( "%lld %lld\n" , nans.dn , nans.up );
    return;
  }
  hon = on / 2;
  for( int i = 0 ; i < K ; i ++ ){
    Frac tmp = test();
    if( tmp + ans < nans )
      nans = tmp + ans;
    random_shuffle( odd.begin() , odd.end() );
  }
  printf( "%lld %lld\n" , nans.dn , nans.up );
}
int main(){
  srand( 514514 );
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
