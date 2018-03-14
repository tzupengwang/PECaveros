#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
#define N 100
#define K 42
inline LL mypow( LL a , LL b ){
  LL ret = 1;
  while( b ){
    if( b & 1 ) ret *= a;
    a *= a;
    b >>= 1;
  }
  return ret;
}
LL n , b[ N ] , q;
unordered_map<LL,int> memo;
void solve1(){
  int hf = n / 2;
  {
    for( int i = 0 ; i < (1 << hf) ; i ++ ){
      LL s = 0;
      for( int j = 0 ; j < hf ; j ++ )
        if( (i >> j) & 1 )
          s += b[ j ];
      memo[ s ] = i;
    }
  }
  int nhf = n - hf;
  {
    for( int i = 0 ; i < (1 << nhf) ; i ++ ){
      LL s = 0;
      for( int j = 0 ; j < nhf ; j ++ )
        if( (i >> j) & 1 )
          s += b[ hf + j ];
      LL goal = q - s;
      auto it = memo.find( goal );
      if( it != memo.end() ){
        int msk1 = it->second;
        for( int j = 0 ; j < hf ; j ++ )
          if( (msk1 >> j) & 1 )
            putchar( '1' );
          else
            putchar( '0' );
        for( int j = 0 ; j < nhf ; j ++ )
          if( (i >> j) & 1 )
            putchar( '1' );
          else
            putchar( '0' );
        puts( "" );
        exit(0);
      }
    }
  }
  assert( false );
}
LL a[ N ];
bool tk[ N ];
pair<LL,LL> low( LL x ){
  LL bs = 1 , bc = 0;
  while( x % 2 == 0 ){
    bs <<= 1;
    x >>= 1;
    bc ++;
  }
  return {bs, bc};
}
void solve2(){
  LL bs = 1 , bc = 0;
  tie( bs , bc ) = low( b[ 0 ] );
  for( LL a0 = 1 ; ; a0 ++ ){
    if( a0 % (bs << 1) == 0 ) continue;
    LL tt , t;
    tie( tt , t ) = low( a0 );
    // b0 * r + 2^64 * x = a0 * bs
    // (b0 / bs) * r + 2 ^ (64 - bc) = a0
    //LL r = a0 * mypow( b[ 0 ] / bs , (1LLU << (63 - bc)) - 1LLU ); 
    //LL rr = (b[ 0 ] / tt) * mypow( a0 / tt , (1LLU << (63 - t)) - 1LLU );
    LL r = (a0 / tt) * mypow( b[ 0 ] / tt , (1LLU << (63 - t)) - 1LLU );
    //LL r = (a0 / tt) * mypow( b[ 0 ] / tt , (1LLU << (63 - t)) - 1 );
    //if( t ) rr %= (1LLU << (64 - t));
    //LL r = mypow( rr , (1LLU << 63) - 1LLU );
    //if( bc ) r %= (1LLU << (64 - bc));
    //if( a0 <= 10 )
      //cerr << a0 << " " << r << endl;
    LL s = 0;
    bool ok = true;
    for( LL i = 0 ; i < n and ok ; i ++ ){
      a[ i ] = b[ i ] * r;
      if( a[ i ] <= s ) ok = false;
      s += a[ i ];
    }
    if( not ok ) continue;
    LL qq = q * r;
    for( int i = n - 1 ; i >= 0 ; i -- ){
      tk[ i ] = false;
      if( qq >= a[ i ] ){
        tk[ i ] = true;
        qq -= a[ i ];
      }
    }
    if( qq ) continue;
    for( int i = 0 ; i < (int)n ; i ++ )
      if( tk[ i ] )
        putchar( '1' );
      else
        putchar( '0' );
    puts( "" );
    exit(0);
  }
}
int main(){
  scanf( "%llu" , &n );
  //n = K;
  for( LL i = 0 ; i < n ; i ++ )
    scanf( "%llu" , &b[ i ] );
    //b[ i ] = rand() * rand() + 1;
  scanf( "%llu" , &q );
  //q = rand();
  if( n <= K ) solve1();
  solve2();
}
