#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 3096
char buf[ N ];
struct Board{
  int n , m , sn , sm;
  bitset<N> b[ N ];
  Board(){
    for( int i = 0 ; i < N ; i ++ )
      b[ i ].reset();
  }
  void pre(){
    bool first = false;
    sn = sm = 0;
    for( int i = 0 ; i < N and !first ; i ++ )
      for( int j = 0 ; j < N and !first ; j ++ )
        if( b[ i ][ j ] and !first ){
          first = true;
          sn = i;
          sm = j;
        }
  }
  void read(){
    scanf( "%d%d" , &n , &m );
    for( int i = 0 ; i < n ; i ++ ){
      scanf( "%s" , buf );
      for( int j = 0 ; j < m ; j ++ )
        b[ i ][ j ] = (buf[ j ] == '*');
    }
    pre();
  }
  Board Xor( const Board& he , int& me_shift_n , int& me_shift_m ,
                               int& he_shift_n , int& he_shift_m ) const{
    Board ret;
    ret.sn = max( sn , he.sn );
    ret.sm = max( sm , he.sm );
    me_shift_n = ret.sn -    sn , me_shift_m = ret.sm -    sm;
    he_shift_n = ret.sn - he.sn , he_shift_m = ret.sm - he.sm;
    for( int i = 0 ; i + me_shift_n < N ; i ++ )
      ret.b[ i + me_shift_n ] ^= (b[ i ] << me_shift_m);
    for( int i = 0 ; i + he_shift_n < N ; i ++ )
      ret.b[ i + he_shift_n ] ^= (he.b[ i ] << he_shift_m);
    ret.pre();
    return ret;
  };
  bool Equal( const Board& he , int& me_shift_n , int& me_shift_m ,
                                int& he_shift_n , int& he_shift_m ) const{
    int rsn = max( sn , he.sn );
    int rsm = max( sm , he.sm );
    me_shift_n = rsn -    sn , me_shift_m = rsm -    sm;
    he_shift_n = rsn - he.sn , he_shift_m = rsm - he.sm;
    for( int i = max( me_shift_n , he_shift_n ) ; i < N ; i ++ )
      if( (   b[ i - me_shift_n ] << me_shift_m) !=
          (he.b[ i - he_shift_n ] << he_shift_m) )
        return false;
    return true;
  }
} a[ 3 ] , b;
int sgn( int now ){
  return now == 0 ? 1 : -1;
}
void go( int base ){
  int men1 , mem1 , hen1 , hem1;
  int men2 , mem2 , hen2 , hem2;
  b = a[ 2 ].Xor( a[ base ] , men1 , mem1 , hen1 , hem1 );
  if( a[ base ^ 1 ].Equal( b , men2 , mem2 , hen2 , hem2 ) ){
    puts( "YES" );
    printf( "%d %d\n" , (mem2 - (hem1 + hem2)) * sgn( base ) ,
                        (men2 - (hen1 + hen2)) * sgn( base ) );
    exit(0);
  }
}
int main(){
#ifndef LOCAL
  freopen( "kids.in" , "r" , stdin );
  freopen( "kids.out" , "w" , stdout );
#endif
  for( int i = 0 ; i < 3 ; i ++ )
    a[ i ].read();
  go( 0 );
  go( 1 );
  int men , mem , hen , hem;
  int men2 , mem2 , hen2 , hem2;
  b = a[ 1 ].Xor( a[ 0 ] , men , mem , hen , hem );
  if( b.Equal( a[ 2 ] , men2 , mem2 , hen2 , hem2 ) ){
    puts( "YES" );
    printf( "%d %d\n" , mem - hem , men - hen );
    exit(0);
  }
  puts( "NO" );
}
