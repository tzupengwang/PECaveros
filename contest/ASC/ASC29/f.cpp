#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202020
#define S 33
#define T 126
char s[ N ] , t[ N ];
#define BS 13131
int mod = 1000000007;
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mpow( int a , int b ){
  int ret = 1 , aa = a;
  while( b ){
    if( b & 1 ) ret = mul( ret , aa );
    aa = mul( aa , aa );
    b >>= 1;
  }
  return ret;
}
int lens , lent , bss;
int bs[ N ] , tar , sum[ 133 ] , rnk[ 133 ];
vector<int> ans;
void solve(){
  for( int i = 0 ; i < 133 ; i ++ )
    rnk[ i ] = 133;
  int curvl = 0;
  for( int i = lens - 1 ; i >= 0 ; i -- ){
    curvl = mul( curvl , BS );
    for( int j = S ; j <= T ; j ++ )
      sum[ j ] = mul( sum[ j ] , BS );
    int ornk = rnk[ (int)s[ i ] ];
    for( int j = S ; j <= T ; j ++ )
      if( rnk[ j ] < ornk ){
        curvl = add( curvl , sum[ j ] );
        rnk[ j ] ++;
      }
    curvl = sub( curvl , mul( ornk - 1 , sum[ (int)s[ i ] ] ) );
    rnk[ (int)s[ i ] ] = 1;
    curvl = add( curvl , 1 );
    sum[ (int)s[ i ] ] = add( sum[ (int)s[ i ] ] , 1 );
    if( i + lent < lens ){
      int who = s[ i + lent ];
      curvl = sub( curvl , mul( bss , rnk[ who ] ) );
      sum[ who ] = sub( sum[ who ] , bss );
    }
    if( i + lent <= lens and curvl == tar )
      ans.push_back( i + 1 );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "substring.in" , "r" , stdin );
  freopen( "substring.out" , "w" , stdout );
#endif
  bs[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ )
    bs[ i ] = mul( bs[ i - 1 ] , BS );
  scanf( "%s" , s );
  scanf( "%s" , t );
  lens = strlen( s );
  lent = strlen( t );
  bss = bs[ lent ];
  char cc[ 133 ] = {}, np = 1;
  for( int i = 0 ; i < lent ; i ++ ){
    if( !cc[ (int)t[ i ] ] ) cc[ (int)t[ i ] ] = np ++;
    t[ i ] = cc[ (int)t[ i ] ];
  }
  for( int i = lent - 1 ; i >= 0 ; i -- )
    tar = add( mul( tar , BS ) , t[ i ] );
  solve();
  reverse( ans.begin() , ans.end() );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
