#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define K 80000000
int mod;
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int mpow( int a , int x ){
  if( !x ) return 1;
  int ret = mpow( mul( a , a ) , x >> 1 );
  if( x & 1 ) ret = mul( ret , a );
  return ret;
}
int a , l , r , ord;
vector<int> ans;
void check( int x ){
  if( mpow( a , x ) == 1 )
    ord = min( ord , x );
}
inline int inv( int x ){
  return mpow( x , mod - 2 );
}
LL sqrtM;
//unordered_set<int> ap;
bitset<1000000000> ap;
int iai[ 100000 ];
int main(){
  cin >> mod >> a >> l >> r;
  int m = mod;
  ord = m - 1;
  for( LL i = 1 ; i * i <= m - 1 ; i ++ ){
    if( (m - 1) % i ) continue;
    check( i );
    check( (m - 1) / i );
  }
  if( ord <= K ){
    for( int i = 0 , ca = 1 ; i < ord ; i ++ , ca = mul( ca , a ) )
      if( l <= ca and ca <= r )
        ans.push_back( ca );
  }else{
    while( sqrtM * sqrtM <= m ) sqrtM ++;
    iai[ 0 ] = 1;
    for( int i = 1 , ai = 1 ; i < sqrtM ; i ++ ){
      ai = mul( ai , a );
      iai[ i ] = inv( ai );
    }
    int tap = mpow( a , sqrtM ) , nap = tap;
    for( int i = 1 ; i < sqrtM ; i ++ ){
      ap[ tap ] = true;
      //ap.insert( tap );
      tap = mul( tap , nap );
    }
    for( int i = l ; i <= r ; i ++ ){
      bool gt = false;
      for( int j = 0 ; j < sqrtM ; j ++ ){
        int nd = mul( i , iai[ j ] );
        if( ap[ nd ] ){
        //if( ap.find( nd ) != ap.end() ){
          gt = true;
          break;
        }
      }
      if( gt )
        ans.push_back( i );
    }
  }
  sort( ans.begin() , ans.end() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
