#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202
#define M 202
#define NONE -2
#define TSAN -1
LL sub( LL a , LL b , LL mod ){
  a -= b;
  return a < 0 ? a + mod : a;
}
const LL inf = 1e9;
LL mul( LL a , LL b , LL mod ){
  if( mod < inf ) return a * b % mod;
  LL ret = 0;
  while( b ){
    if( b & 1LL ) ret = (ret + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return ret;
}
pair<LL,LL> gcd( LL a , LL b , LL lcm ){
  if( b == 0 ) return {1, 0};
  pair<LL,LL> q = gcd( b , a % b , lcm );
  return {q.second, sub( q.first , mul( q.second , (a / b) , lcm ) , lcm )};
}
pair<LL,LL> cr( LL x1 , LL m1 , LL x2 , LL m2 ){
  if( x1 == -2 ) return {x2 , m2};
  if( x2 == -2 ) return {x1 , m1};
  if( x1 == -1 or x2 == -1 ) return {-1, -1};
  LL g = __gcd( m1 , m2 );
  if( (x2 - x1) % g ) return {-1, -1};
  m1 /= g; m2 /= g;
  LL lcm = (m1 * g) * m2;
  pair<LL,LL> p = gcd(m1, m2, lcm);
  LL res = (x2 - x1) % lcm;
  if( res < 0 ) res += lcm;
  res = mul( res , (p.first % lcm + lcm) % lcm , lcm );
  res = mul( res , m1 , lcm );
  res = (res + x1) % lcm;
  return {res , lcm};
}
int n , m;
int a[ N ][ N ] , b[ N ][ N ];
int ql , qr , qu , qd;
#define lgN 8
LL aa[ lgN ][ lgN ][ N ][ N ];
LL am[ lgN ][ lgN ][ N ][ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      scanf( "%d" , &a[ i ][ j ] );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      scanf( "%d" , &b[ i ][ j ] );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      aa[ 0 ][ 0 ][ i ][ j ] = a[ i ][ j ];
      am[ 0 ][ 0 ][ i ][ j ] = b[ i ][ j ];
    }
  for( int ii = 1 ; ii < lgN ; ii ++ ){
    int i2 = (1 << (ii - 1));
    for( int i = 1 ; i + (1 << ii) - 1 <= n ; i ++ ){
      for( int j = 1 ; j <= m ; j ++ ){
        LL ca = -2 , cm = -2;
        tie( ca , cm ) =
          cr( ca , cm , aa[ ii - 1 ][ 0 ][ i ][ j ] ,
                        am[ ii - 1 ][ 0 ][ i ][ j ] );
        tie( ca , cm ) =
          cr( ca , cm , aa[ ii - 1 ][ 0 ][ i + i2 ][ j ] ,
                        am[ ii - 1 ][ 0 ][ i + i2 ][ j ] );
        aa[ ii ][ 0 ][ i ][ j ] = ca;
        am[ ii ][ 0 ][ i ][ j ] = cm;
      }
    }
    for( int i = 1 ; i <= n ; i ++ ){
      for( int j = 1 ; j + (1 << ii) - 1 <= m ; j ++ ){
        LL ca = -2 , cm = -2;
        tie( ca , cm ) =
          cr( ca , cm , aa[ 0 ][ ii - 1 ][ i ][ j ] ,
                        am[ 0 ][ ii - 1 ][ i ][ j ] );
        tie( ca , cm ) =
          cr( ca , cm , aa[ 0 ][ ii - 1 ][ i ][ j + i2 ] ,
                        am[ 0 ][ ii - 1 ][ i ][ j + i2 ] );
        aa[ 0 ][ ii ][ i ][ j ] = ca;
        am[ 0 ][ ii ][ i ][ j ] = cm;
      }
    }
  }
  for( int ii = 1 ; ii < lgN ; ii ++ )
    for( int jj = 1 ; jj < lgN ; jj ++ )
      for( int i = 1 ; i + (1 << ii) - 1 <= n ; i ++ )
        for( int j = 1 ; j + (1 << jj) - 1 <= m ; j ++ ){
          LL ca = -2 , cm = -2;
          int i2 = (1 << (ii - 1));
          int j2 = (1 << (jj - 1));
          tie( ca , cm ) =
            cr( ca , cm , aa[ ii - 1 ][ jj - 1 ][ i ][ j ] , 
                          am[ ii - 1 ][ jj - 1 ][ i ][ j ] );
          tie( ca , cm ) =
            cr( ca , cm , aa[ ii - 1 ][ jj - 1 ][ i + i2 ][ j ] , 
                          am[ ii - 1 ][ jj - 1 ][ i + i2 ][ j ] );
          tie( ca , cm ) =
            cr( ca , cm , aa[ ii - 1 ][ jj - 1 ][ i ][ j + j2 ] , 
                          am[ ii - 1 ][ jj - 1 ][ i ][ j + j2 ] );
          tie( ca , cm ) =
            cr( ca , cm , aa[ ii - 1 ][ jj - 1 ][ i + i2 ][ j + j2 ] , 
                          am[ ii - 1 ][ jj - 1 ][ i + i2 ][ j + j2 ] );
          aa[ ii ][ jj ][ i ][ j ] = ca;
          am[ ii ][ jj ][ i ][ j ] = cm;
        }
}
int cs , lg[ N ];
LL query(){
  int bt1 = lg[ qr - ql + 1 ];
  int bt2 = lg[ qd - qu + 1 ];
  int tb1 = (1 << bt1);
  int tb2 = (1 << bt2);
  LL ca = -2 , cm = -2;
  tie( ca , cm ) =
    cr( ca , cm , aa[ bt1 ][ bt2 ][ ql ][ qu ] ,
                  am[ bt1 ][ bt2 ][ ql ][ qu ] );
  tie( ca , cm ) =
    cr( ca , cm ,
        aa[ bt1 ][ bt2 ][ qr - tb1 + 1 ][ qu ],
        am[ bt1 ][ bt2 ][ qr - tb1 + 1 ][ qu ] );
  tie( ca , cm ) =
    cr( ca , cm ,
        aa[ bt1 ][ bt2 ][ ql ][ qd - tb2 + 1 ],
        am[ bt1 ][ bt2 ][ ql ][ qd - tb2 + 1 ] );
  tie( ca , cm ) =
    cr( ca , cm ,
        aa[ bt1 ][ bt2 ][ qr - tb1 + 1 ][ qd - tb2 + 1 ] ,
        am[ bt1 ][ bt2 ][ qr - tb1 + 1 ][ qd - tb2 + 1 ]  );
  return ca;
}
void solve(){
  printf( "Case #%d:\n" , ++ cs );
  int q; scanf( "%d" , &q ); while( q -- ){
    scanf( "%d%d%d%d" , &ql , &qu , &qr , &qd );
    printf( "%lld\n" , query() );
  }
}
int main(){
  int ii = 0;
  for( int i = 1 ; i < N ; i ++ ){
    if( (1 << (ii + 1)) <= i ) ii ++;
    lg[ i ] = ii;
  }
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
