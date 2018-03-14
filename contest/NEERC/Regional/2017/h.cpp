#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#ifdef TEST
bool is_p( LL x ){
  for( LL i = 2 ; i * x <= x ; i ++ )
    if( x % i == 0 )
      return false;
  return true;
}
LL gen_prime(){
  while( true ){
    LL p = ((LL)rand() * (LL)rand()) & ((1LL << 30) - 1);
    p |= (1LL | (1LL << 29));
    if( is_p( p ) )
      return p;
  }
}
#endif
LL n;
LL modit( LL x , LL y ){
  x %= y;
  return x < 0 ? x + y : x;
}
LL mul( LL x , LL y , LL mod = n ){
  LL ret = 0;
  while( y ){
    if( y & 1LL ) ret = (ret + x) % mod;
    x = (x + x) % mod;
    y >>= 1;
  }
  return ret;
}
LL mypow( LL x , LL y ){
  LL ret = 1;
  while( y ){
    if( y & 1LL ) ret = mul( ret , x );
    x = mul( x , x );
    y >>= 1;
  }
  return ret;
}
LL myrand(){
  LL ret = 1;
  for( int i = 0 ; i < 4 ; i ++ )
    ret = mul( ret , modit( rand() , n - 1 ) + 1 );
  return ret;
}
LL len( LL x ){
  int ret = 0;
  while( x ){
    ret ++;
    x >>= 1;
  }
  return ret;
}
int cost( LL x , LL y ){
  return (len( x ) + 1) *
         (len( y ) + 1);
}
#ifdef TEST
int modPow( LL ai , LL di ){
  int ret = 0;
  LL r = 1;
  for( int i = 0 ; i < 60 ; i ++ ){
    if( (di >> i) & 1LL ){
      ret += cost( r , ai );
      r = mul( r , ai );
    }
    ret += cost( ai , ai );
    ai = mul( ai , ai );
  }
  return ret;
}
#endif
#define N 30000
double mean( LL a[ N ] ){
  return accumulate( a , a + N , 0LL ) / (double)N;
}
double cov( LL a[ N ] , LL b[ N ] ){
  double am = mean( a );
  double bm = mean( b );
  double dif = 0;
  for( int i = 0 ; i < N ; i ++ )
    dif += (a[ i ] - am) * (b[ i ] - bm);
  return dif;
}
LL a[ N ] , t[ N ] , t1[ N ] , t2[ N ];
LL na[ N ] , r[ N ];
LL solve(){
  LL d = 0;
  for( int j = 0 ; j < N ; j ++ )
    r[ j ] = 1;
  for( int i = 0 ; i < 62 ; i ++ ){
    if( (*max_element( t , t + N )) == 0 )
      return d;
    for( int j = 0 ; j < N ; j ++ ){
      na[ j ] = mul( a[ j ] , a[ j ] );
      t1[ j ] = cost(  a[ j ] , r[ j ] );
      t2[ j ] = cost( na[ j ] , r[ j ] );
    }
    double c1 = cov( t1 , t );
    double c2 = cov( t1 , t1 );
    double c3 = cov( t1 , t2 );
    if( i == 0 or fabs( c1 - c2 ) < fabs( c1 - c3 ) ){
      d |= (1LL << i);
      for( int j = 0 ; j < N ; j ++ ){
        t[ j ] -= cost( a[ j ] , r[ j ] );
        r[ j ] = mul( r[ j ] , a[ j ] );
      }
    }
    for( int j = 0 ; j < N ; j ++ )
      a[ j ] = na[ j ];
  }
  //assert( false );
  return -1;
}
int main(){
#ifdef TEST
  srand( time( 0 ) );
  LL pp = gen_prime();
  LL qq = gen_prime();
  n = pp * qq;
  LL m = (pp - 1) * (qq - 1);
  LL d;
  while( true ){
    d = 1;
    for( int i = 0 ; i < 5 ; i ++ )
      d = mul( d , modit( rand() , m - 1 ) + 1 , m );
    if( __gcd( d , m ) == 1 ) break;
  }
  fprintf( stderr , "preprocess done, n = %lld, d = %lld\n" , n , d );


  clock_t s = clock();
#else
  scanf( "%lld" , &n );
  assert( n <= (1LL << 62) );
#endif
  for( LL i = 0 ; i < N ; i ++ ){
    a[ i ] = myrand();
#ifdef TEST
    t[ i ] = modPow( a[ i ] , d );
#else
    assert( 0 <= a[ i ] and a[ i ] < n );
    printf( "? %lld\n" , a[ i ] );
    fflush( stdout );
    scanf( "%lld" , &t[ i ] );
#endif
  }
#ifdef TEST
  fprintf( stderr , "query done, %.12f secs passed\n" , (double)(clock() - s) / CLOCKS_PER_SEC );
#endif
  for( LL i = 0 ; i < N ; i ++ ){
    LL ai = a[ i ];
    for( int j = 0 ; j < 60 ; j ++ ){
      t[ i ] -= cost( ai , ai );
      ai = mul( ai , ai );
    }
  }
  printf( "! %lld\n" , solve() );
  fflush( stdout );
#ifdef TEST
  fprintf( stderr , "query done, %.12f secs passed\n" , (double)(clock() - s) / CLOCKS_PER_SEC );
#endif
}
