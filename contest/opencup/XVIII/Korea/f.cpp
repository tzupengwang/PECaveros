#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 15
const LL inf = 1e9;
const LL inf18 = inf * inf;
int n , bt[ 1 << N ];
LL d[ N ][ N ] , bns[ 1 << N ];
LL dp[ 1 << N ][ N ];
int cc[ 1 << N ][ N ] , ct[ 1 << N ];
LL DP( int msk , int rt ){
  if( bt[ msk ] == 1 ) return 0;
  if( dp[ msk ][ rt ] ) return dp[ msk ][ rt ];
  int res = msk ^ (1 << rt);
  int must = res & (-res);
  res ^= must;
  LL ret = inf18;
  for( int submsk = res ; ; submsk = (submsk - 1) & res ){
    for( int ii = 0 ; ii < ct[ submsk | must ] ; ii ++ ){
      int subrt = cc[ submsk | must ][ ii ];
      LL tdp = DP( submsk | must , subrt ) + DP( msk ^ submsk ^ must , rt ) +
               d[ rt ][ subrt ] * bns[ submsk | must ];

      //LL tdp = DP( submsk , subrt ) + DP( msk ^ submsk , rt ) +
               //d[ rt ][ subrt ] * bt[ submsk ] * (n - bt[ submsk ]);
      if( tdp < ret ) ret = tdp;
    }
    if( !submsk ) break;
  }
  return dp[ msk ][ rt ] = ret;
}
int main(){
  for( int i = 1 ; i < (1 << N) ; i ++ ){
    bt[ i ] = bt[ i >> 1 ] + (i & 1);
    for( int j = 0 ; j < N ; j ++ )
      if( (i >> j) & 1 )
        cc[ i ][ ct[ i ] ++ ] = j;
  }
  scanf( "%d" , &n );
  for( int i = 1 ; i < (1 << N) ; i ++ )
    bns[ i ] = bt[ i ] * (n - bt[ i ]);
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ ){
      scanf( "%lld" , &d[ i ][ j ] );
      d[ j ][ i ] = d[ i ][ j ];
    }
  printf( "%lld\n" , DP( (1 << n) - 1 , 0 ) );
}
