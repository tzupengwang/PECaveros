#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp>
typedef cc_hash_table<int,int> umap_t;
using namespace std;
typedef long long LL;
const int mod = 1000000007;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
struct Mat{
  vector< vector<int> > a;
  int T;
  Mat( int _n , int _i = 0 ){
    T = _n;
    a.resize( T );
    for( int i = 0 ; i < T ; i ++ )
      a[ i ].resize( T );
    //a.resize( T , vector<int>( T ) );
    for( int i = 0 ; i < T ; i ++ ){
      for( int j = 0 ; j < T ; j ++ )
        a[ i ][ j ] = 0;
      a[ i ][ i ] = _i;
    }
  }
  Mat operator*( const Mat& he ) const{
    Mat ret( T );
    for( int i = 0 ; i < T ; i ++ )
      for( int j = 0 ; j < T ; j ++ )
        for( int k = 0 ; k < T ; k ++ )
          ret.a[ i ][ j ] = add( ret.a[ i ][ j ],
                                 mul( a[ i ][ k ] , he.a[ k ][ j ] ) );
    return ret;
  }
  Mat operator^( LL tk ) const{
    Mat ret( T , 1 ) , A( T );
    for( int i = 0 ; i < T ; i ++ )
      for( int j = 0 ; j < T ; j ++ )
        A.a[ i ][ j ] = a[ i ][ j ];
    while( tk ){
      if( tk & 1 ) ret = ret * A;
      A = A * A;
      tk >>= 1;
    }
    return ret;
  }
  void print() const{
    for( int i = 0 ; i < T ; i ++ , puts( "" ) )
      for( int j = 0 ; j < T ; j ++ )
        printf( "%d " , a[ i ][ j ] );
  }
};
int n , k , MSK , MSK2;
int dp[ 2 ][ 1 << 17 ];
int mapping[ 1 << 17 ] , mid;
int who[ 1 << 17 ];
void build_map(){
  MSK = (1 << (k + k)) - 1;
  MSK2 = (MSK << 1) | 1;
  for( int i = 0 ; i < (1 << (k + k)) ; i ++ ){
    mapping[ i ] = -1;
    if( __builtin_popcount( MSK ^ i ) == k ){
      who[ mid ] = i;
      mapping[ i ] = mid ++;
    }
  }
}
void solve1(){
  cerr << "Method 1" << endl;
  int st = mapping[ MSK ^ ((1 << k) - 1) ];
  dp[ 0 ][ st ] = 1;
  for( int i = 0 ; i < n ; i ++ ){
    int now = i & 1 , nxt = 1 - now;
    for( int j = 0 ; j < mid ; j ++ )
      dp[ nxt ][ j ] = 0;
    //dp[ nxt ].clear();
    for( int _ = 0 ; _ < mid ; _ ++ ){
    //for( auto j : dp[ now ] ){
      //if( j.second == 0 ) continue;
      if( dp[ now ][ _ ] == 0 ) continue;
      int msk = who[ _ ];
      msk = (msk << 1);
      int can = MSK2 ^ msk;
      while( can ){
        int cur = can & (-can);
        int nmsk = msk | cur;
        if( ((nmsk >> (k + k)) & 1) and
            mapping[ nmsk & MSK ] != -1 ){
          int to = mapping[ nmsk & MSK ];
          dp[ nxt ][ to ] = add( dp[ nxt ][ to ] , 
                                 dp[ now ][ _ ] );
        }
        can ^= cur;
      }
    }
  }
  cout << dp[ n & 1 ][ st ] << endl;
  exit(0);
}
void solve2(){
  cerr << "Method 2" << endl;
  Mat a( mid );
  for( int i = 0 ; i < (1 << (k + k)) ; i ++ ){
    if( mapping[ i ] == -1 ) continue;
    int msk = (i << 1);
    int can = MSK2 ^ msk;
    while( can ){
      int cur = can & (-can);
      int nmsk = msk | cur;
      if( ( (nmsk >> (k + k)) & 1 ) and
          mapping[ nmsk & MSK ] != -1 ){
        a.a[ mapping[ nmsk & MSK ] ][ mapping[ i ] ] ++;
      }
      can ^= cur;
    } 
  }
  a = a ^ n;
  int st = mapping[ MSK ^ ((1 << k) - 1) ];
  int ans = a.a[ st ][ st ];
  printf( "%d\n" , ans );
}
inline int f(){
  Mat a( 2 );
  a.a[ 0 ][ 0 ] = 0; a.a[ 0 ][ 1 ] = 1;
  a.a[ 1 ][ 0 ] = 1; a.a[ 1 ][ 1 ] = 1;
  a = a ^ ( n - 1 );
  return add( a.a[ 1 ][ 0 ] , a.a[ 1 ][ 1 ] );
}
int main(){
  cin >> n >> k;
  if( k == 0 ){
    puts( "1" );
    exit(0);
  }
  if( n - 1 <= k ){
    LL ans = 1;
    for( LL i = 2 ; i <= n ; i ++ )
      ans *= i;
    cout << ans << endl;
    exit(0);
  }
  if( k == 1 ){
    cout << f() << endl;
    exit(0);
  }
  build_map();
  if( k >= 5 )
    solve1();
  else
    solve2();
}
