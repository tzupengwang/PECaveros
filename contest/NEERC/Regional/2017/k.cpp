#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
#define N 100
#define K 40
inline LL mypow( LL a , LL b ){
  LL ret = 1;
  while( b -- ){
    ret *= a;
    a *= a;
  }
  return ret;
}
LL n , b[ N ] , q;
void solve1(){
  vector< pair<LL,int> > memo;
  int hf = n / 2;
  {
    for( int i = 0 ; i < (1 << hf) ; i ++ ){
      LL s = 0;
      for( int j = 0 ; j < hf ; j ++ )
        if( (i >> j) & 1 )
          s += b[ j ];
      memo.push_back( {s, i} );
    }
  }
  sort( memo.begin() , memo.end() );
  int nhf = n - hf;
  {
    for( int i = 0 ; i < (1 << nhf) ; i ++ ){
      LL s = 0;
      for( int j = 0 ; j < nhf ; j ++ )
        if( (i >> j) & 1 )
          s += b[ hf + j ];
      LL goal = q - s;
      int at = lower_bound( memo.begin() , memo.end() , make_pair(goal, -1) ) - memo.begin();
      if( at == (int)memo.size() or
          memo[ at ].first != goal )
        continue;
#ifdef TEST
      continue;
#endif
      int msk1 = memo[ at ].second;
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
  exit(0);
}
LL a[ N ];
bool tk[ N ];
pair<LL,LL> low( LL x ){
  LL bs = 1 , bc = 0;
  while( x % 2LLU == 0LLU ){
    bs <<= 1;
    x >>= 1;
    bc ++;
  }
  return {bs, bc};
}
void solve2(){
  LL bs = 1 , bc = 0;
  tie( bs , bc ) = low( b[ 0 ] );
  for( LL a0 = 1 ; a0 <= (1LLU << (66 - n)) / bs ; a0 += 2 ){
    LL rr = a0 * mypow( b[ 0 ] / bs , 63 - bc );
    if( bc ) rr &= ((1LLU << (64 - bc)) - 1LLU);
    for( LL md = 0 ; md < bs ; md ++ ){
      LL r = rr;
      if( bc ) r = rr | (md << (64 - bc));
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
}
int main(){
#ifdef TEST
  srand( 514514 );
  n = K + 2;
  LL r = (rand() * rand()) | 1;
  b[ 0 ] = r;
  LL ps = 1;
  for( LL i = 1 ; i < n ; i ++ ){
    a[ i ] = ps + 1;
    ps += a[ i ];
    b[ i ] = a[ i ] * r;
  }
  for( LL i = 0 ; i < n ; i ++ )
    if( rand() % 5 == 0 )
      q += b[ i ];
  //n = K;
  //for( LL i = 0 ; i < n ; i ++ )
    //b[ i ] = rand() * rand() + 1;
  //q = rand() * rand() + 1;
#else
  scanf( "%llu" , &n );
  for( LL i = 0 ; i < n ; i ++ )
    scanf( "%llu" , &b[ i ] );
  scanf( "%llu" , &q );
#endif
  if( n <= K ) solve1();
  solve2();
}
