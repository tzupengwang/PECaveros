#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int mpow( int a , int b ){
  if( !b ) return 1;
  int ret = mpow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
#define N 111
int n , k , b[ N ] , len , slen;
bitset<N> bb;
char buf[ N ];
int dp[ 2 ][ 8 ];

int C[ 9 ][ 9 ];

inline int bit( int p ){
  return bb[ p % len ];
}

void reset( int id ){
  for( int i = 0 ; i < 8 ; i ++ )
    dp[ id ][ i ] = 0;
}

int cc[ 2 ][ 8 ][ 8 ][ 8 ];
bool gt[ 2 ][ 8 ];

void go_cal( int bt , int xn ){
  if( gt[ bt ][ xn ] ) return;
  gt[ bt ][ xn ] = true;
  for( int n_bnd = 0 ; n_bnd <= xn ; n_bnd ++ ){
    int other = xn - n_bnd;
    for( int one = 0 ; one <= n_bnd ; one ++ ){
      if( one and bt == 0 ) break;
      
      for( int other_one = 0 ; other_one <= other ; other_one ++ ){
        if( (one + other_one) & 1 ) continue;
        int to = mul( C[ n_bnd ][ one ] , C[ other ][ other_one ] );
        
        int nxt_bnd = one;
        if( bt == 0 )
          nxt_bnd = n_bnd;

        int& nxt_dp = cc[ bt ][ xn ][ n_bnd ][ nxt_bnd ];
        nxt_dp = add( nxt_dp , to );
      }
    }
  }
}

int cal( int xn ){
  reset( slen & 1 );
  dp[ slen & 1 ][ xn ] = 1;
  for( int i = slen - 1 ; i >= 0 ; i -- ){
    int now = i & 1 , pre = 1 ^ now;
    reset( now );
    go_cal( bit( i ) , xn );
    for( int j = 0 ; j <= xn ; j ++ )
      if( dp[ pre ][ j ] )
        for( int u = 0 ; u <= j ; u ++ )
          dp[ now ][ u ] = add( dp[ now ][ u ],
                                mul( dp[ pre ][ j ] ,
                                     cc[ bit( i ) ][ xn ][ j ][ u ] ) );
  }
  return dp[ 0 ][ 0 ];
}

int ca[ N ];
int fac[ N ] , ifac[ N ];

int main(){

  fac[ 0 ] = ifac[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    ifac[ i ] = mpow( fac[ i ] , mod - 2 );
  }

  for( int i = 0 ; i < 9 ; i ++ )
    C[ i ][ 0 ] = C[ i ][ i ] = 1;
  for( int i = 2 ; i < 9 ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      C[ i ][ j ] = add( C[ i - 1 ][ j ],
                         C[ i - 1 ][ j - 1 ] );

  scanf( "%d%d" , &n , &k );
  scanf( "%s" , buf );
  len = strlen( buf );
  for( int i = 0 ; i < len ; i ++ )
    bb[ i ] = buf[ len - i - 1 ] - '0';
  slen = len * k;

  int R = 0;
  for( int i = slen - 1 ; i >= 0 ; i -- )
    R = add( add( R , R ) , bit( i ) );

  for(int i = n ; i >= 1 ; i -= 2){
    ca[ i ] = cal( i );
    // printf( "%d => %d\n" , i , ca[ i ] );
  }

  // cerr << "Correct ans = " << bf( R ) << endl;
  // cerr << "Find ans = " << find_ans() << endl;
  // cerr << (LL)bf( R ) * fac[ n ] << endl;

  int ans = 0;

  if( n == 3 ){
    ans = ca[ 3 ];
    ans = sub( ans , mul( mul( 3 , R ) , ca[ 1 ] ) );
    ans = add( ans , mul( 2 , ca[ 1 ] ) );
  }
  if( n == 4 ){
    ans = ca[ 4 ];
    ans = sub( ans , mul( mul( 6 , R ) , ca[ 2 ] ) );
    ans = add( ans , mul( 8 , ca[ 2 ] ) );
    ans = add( ans , mul( 3 , mul( R , sub( R , 1 ) ) ) );
    ans = sub( ans , mul( 3 , R ) );
  }
  if( n == 5 ){
    ans = ca[ 5 ];
    ans = sub( ans , mul( mul( 10 , R ) , ca[ 3 ] ) );
    ans = add( ans , mul( 20 , ca[ 3 ] ) );

    ans = sub( ans , mul( mul( 35 , R ) , ca[ 1 ] ) );

    ans = add( ans , mul( 24 , ca[ 1 ] ) );
    ans = add( ans , mul( mul( 15 , mul( R , sub( R , 1 ) ) ) , ca[ 1 ] ) );
  }
  if( n == 6 ){
    ans = ca[ 6 ];
    ans = sub( ans , mul( mul( 15 , R ) , ca[ 4 ] ) );
    ans = add( ans , mul( 40 , ca[ 4 ] ) );

    ans = sub( ans , mul( mul( 165 , R ) , ca[ 2 ] ) );
    ans = add( ans , mul( mul( 45 , mul( R , sub( R , 1 ) ) ) , ca[ 2 ] ) );
    ans = add( ans , mul( 184 , ca[ 2 ] ) );

    ans = sub( ans , mul( mul( 15 , mul( R , sub( R , 1 ) ) ) , sub( R , 2 ) ) );
    ans = add( ans , mul( 45 , mul( R , sub( R , 1 ) ) ) );
    ans = sub( ans , mul( 45 , R ) );
  }
  if ( n == 7 ) {
    ans = ca[ 7 ];
    ans = sub( ans , mul( mul( 21 , R ) , ca[ 5 ] ) );
    ans = add( ans , mul( 70 , ca[ 5 ] ) );

    ans = add( ans , mul( mul( 105 , mul( R , sub( R , 1 ) ) ) , ca[ 3 ] ) );
    ans = sub( ans , mul( mul( 525 , R ) , ca[ 3 ] ) );
    ans = add( ans , mul( 784 , ca[ 3 ] ) );

    ans = add( ans , mul( mul( 315 , mul( R , sub( R , 1 ) ) ) , ca[ 1 ] ) );
    ans = add( ans , mul( mul( 210 , mul( sub( R , 2 ) , sub( R , 1 ) ) ) , ca[ 1 ] ) );
    ans = sub( ans , mul( mul( mul( 105 , mul( R , sub( R , 1 ) ) ) , sub( R , 2 ) ) , ca[ 1 ] ) );
    ans = sub( ans , mul( mul( 609 , R ) , ca[ 1 ] ) );
    ans = add( ans , mul( 300 , ca[ 1 ] ) );
    // exit(1);
  }

  // cout << "My ans: " << ans << endl;

  ans = mul( ans , ifac[ n ] );

  cout << ans << endl;
}
