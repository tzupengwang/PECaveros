#include <bits/stdc++.h>
using namespace std;
#define mod 1000003
typedef long long ll;
inline int add( int x , int y ){
  return ( x + y ) % mod;
}
inline int sub( int x , int y ){
  return ( x - y + mod ) % mod;
}
inline ll mul( ll x , ll y ){
  return ( x * y ) % mod;
}
#define K 30
#define MAX 150000
struct Poly{
public:
  vector<int> v;
  int n;
  Poly(){ n = 0; v.clear(); }
  Poly( int _n ){
    n = _n;
    v.resize( n );
    for( int i = 0 ; i < n ; i ++ )
      v[ i ] = 0;
  }
  Poly operator+( const Poly& tp ) const{
    Poly pp( max( n , tp.n ) );
    for( int i = 0 ; i < pp.n ; i ++ ){
      if( i < n ) pp.v[ i ] = add( pp.v[ i ] , v[ i ] );
      if( i < tp.n ) pp.v[ i ] = add( pp.v[ i ] , tp.v[ i ] );
    }
    return pp;
  }
  Poly operator-( const Poly& tp ) const{
    Poly pp( max( n , tp.n ) );
    for( int i = 0 ; i < pp.n ; i ++ ){
      if( i < n ) pp.v[ i ] = add( pp.v[ i ] , v[ i ] ); 
      if( i < tp.n ) pp.v[ i ] = sub( pp.v[ i ] , tp.v[ i ] );
    }
    return pp;
  }
};

typedef long double D;
//typedef __float128_t D;
//typedef double D;

struct CP
{
  D a , b;
};

CP operator+(const CP& a , const CP& b) { return CP{ a.a+b.a , a.b+b.b }; }
CP operator-(const CP& a , const CP& b) { return CP{ a.a-b.a , a.b-b.b }; }
CP operator*( const CP& a , const CP& b )
{
  return {a.a*b.a-a.b*b.b,a.a*b.b+a.b*b.a};
}

D pi = acosl( -1 );

CP A[ MAX ] , B[ MAX ] , C[ MAX ];
int rev[ MAX ];

int rv( int x )
{
  int res = 0;
  for( int i = 0 ; i < 31 ; i++ )
    if( x & (1 << i) ) res += 1 << (31-i-1);
  return res;
}

CP P[ 2 ][ MAX ];

void FFT( CP *s , CP *bac , int N , int tp )
{
  int d = log2( N );
  for( int i = 0 ; i < N ; i++ )
    s[ rev[ i ] >> (31-d) ] = bac[ i ];
  for( int i = 1 ; i <= d ; i++ )
  {
    int step = 1 << i;
    int v = step >> 1 , rstep = N / step;
    for( int j = 0 ; j < N ; j += step )
    {
      CP* t = P[ tp ];
      for( int k = 0 ; k < v ; k++ , t += rstep )
      {
        CP dd = (*t) * s[ k+j+v ];
        s[ k+j+v ] = s[ k+j ] - dd;
        s[ k+j ] = s[ k+j ] + dd;
      }
    }
  }
}
Poly operator*( const Poly& p , const Poly& tp ){
  int N = 1 , k = p.n + tp.n;
  while( N<=k ) N*=2;
  P[ 0 ][ 0 ] = CP{ 1 , 0 };
  P[ 1 ][ 0 ] = CP{ 1 , 0 };
  for( int i = 1 ; i < N ; i++ )
  {
    P[ 0 ][ i ] = CP{ cosl( 2*i*pi/N ) , sinl( 2*i*pi/N ) };
    P[ 1 ][ i ] = CP{ cosl( 2*i*pi/N ) , -sinl( 2*i*pi/N ) };
  }

  for( int i = 0 ; i < N ; i++ )
  {
    if( i < p.n )
      A[ i ] = CP{ (D)p.v[ i ] , 0 };
    else
      A[ i ] = CP{ 0 , 0 };
  }
  for( int i = 0 ; i < N ; i++ )
  {
    if( i < tp.n )
      B[ i ] = CP{ (D)tp.v[ i ] , 0 };
    else
      B[ i ] = CP{ 0 , 0 };
  }

  FFT( C , A , N , 0 );
  FFT( A , B , N , 0 );

  for( int i = 0 ; i < N ; i++ )
    A[ i ] = A[ i ] * C[ i ];

  FFT( C , A , N , 1 );

  Poly res( N );
  for( int i = 0 ; i < N ; i++ )
  {
    //ll tmp = round( C[ i ].a / N );
    ll tmp = C[ i ].a / N + 0.1;
    tmp %= mod;
    res.v[ i ] = tmp;
  }
  return res;
}

const int MAXM = 30010;
const int MAXN = 1000010;

int n , p , m;
int pw[ MAXN ];

Poly dp( int l )
{
  if( l == 0 )
  {
    Poly res( m+5 );
    res.v[ 0 ] = 1;
    return res;
  }
  Poly b = dp( l / 2 );
  Poly a( m+5 );
  for( int i = 0 ; i < m ; i++ )
  {
    int tmp = b.v[ i ];
    int jmp = pw[ l - l/2 ];
    if( l&1 )
    {
      for( int j = 'A' ; j <= 'Z' ; j++ )
      {
        int jj = ( j * pw[ l/2 ] ) % m;
        int nx = ( i * jmp + jj ) % m;
        a.v[ nx ] = add( a.v[ nx ] , tmp );
      }
    }
    else
    {
      int nx = ( i*jmp ) % m;
      a.v[ nx ] = add( a.v[ nx ] , tmp );
    }
  }
  Poly c = a * b;
  for( int i = m ; i < c.n ; i++ )
  {
    int prv = i % m;
    c.v[ prv ] = add( c.v[ prv ] , c.v[ i ] );
    c.v[ i ] = 0;
  }
  c.v.resize( m+5 );
  c.n = m+5;
  return c;
}

int main(){
  for( int i = 0 ; i < MAX; i ++ )
    rev[ i ] = rv( i );
  scanf( "%d%d%d" , &n , &m , &p );
  p %= m;
  pw[ 0 ] = 1;
  for( int i = 1 ; i <= n ; i++ )
    pw[ i ] = ( p * pw[ i-1 ] ) % m;
  Poly f = dp( n );
  int ans = 0;
  for( int i = 0 ; i < m ; i ++ )
  {
    //printf( "f %d %d\n" , i , f.v[ i ] );
    //if( f.v[ i ] <= 0 ) continue ;
    int tmp = mul( f.v[ i ] , ( f.v[ i ] - 1 + mod ) );
    tmp = mul( tmp , (mod+1)/2 );
    ans = add( ans , tmp );
  }
  printf( "%d\n" , ans );
}
