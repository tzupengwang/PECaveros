#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 30303
LL n , r , k;
LL a[ N ] , b[ N ] , c[ N ] , bs[ N ] , cs[ N ];
void init(){
  scanf( "%lld%lld%lld" , &n , &r , &k );
  for( LL i = 1 ; i <= n ; i ++ )
    scanf( "%lld" , &a[ i ] );
  for( LL i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &b[ i ] );
    b[ i ] -= a[ i ];
    bs[ i ] = bs[ i - 1 ] + b[ i ];
  }
  for( LL i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &c[ i ] );
    c[ i ] -= a[ i ];
    cs[ i ] = cs[ i - 1 ] + c[ i ];
  }
}
#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree< pair<LL,int> ,null_type,less< pair<LL,int> >,rb_tree_tag,tree_order_statistics_node_update> set_t;
LL pwho[ N ];
LL Sum( int id ){
  return bs[ id + r - 1 ] - bs[ id - 1 ]; 
}
LL Sumc( int id ){
  return cs[ id + r - 1 ] - cs[ id - 1 ]; 
}
LL cal( LL goal ){ // >= goal
  LL ret = 0 , dlt = 0;
  // ele in += dlt
  set_t bk , in;
  for( int x = n - r + 1 ; x >= 1 ; x -- ){
    if( x + r <= n - r + 1 )
      bk.insert( make_pair( Sum( x + r ) , x + r ) );
    if( x + r <= n ){
      {
        LL at = bk.order_of_key(
            make_pair( goal - Sum( x ) , -1 ) );
        ret += bk.size() - at;
      }
      {
        LL at = in.order_of_key(
            make_pair( goal - Sum( x ) - dlt , -1 ) );
        ret += in.size() - at;
      }
    }
    in.insert( make_pair( Sumc( x ) - Sum( x ) - dlt , x ) );
    pwho[ x ] = Sumc( x ) - Sum( x ) - dlt;
    dlt += 2 * b[ x + r - 1 ] - c[ x + r - 1 ];
    if( x + r - 1 <= n - r + 1 )
      in.erase( make_pair( pwho[ x + r - 1 ] , x + r - 1 ) );
  }
  return ret;
}
LL C( LL _ ){ return _ * (_ - 1) / 2; }
void solve(){
  LL bl = 0 , br = accumulate( c , c + n + 1 , 0LL ) , ba = 0;
  k = C( n - r + 1 ) - k + 1;
  while( bl <= br ){
    LL bmid = (bl + br) >> 1;
    //cerr << bmid << " " << cal( bmid ) << endl;
    if( cal( bmid ) < k )
      br = bmid - 1;
    else
      ba = bmid , bl = bmid + 1;
  }
  printf( "%lld\n" , ba + accumulate( a , a + n + 1 , 0LL ) );
}
int main(){
  init();
  solve();
}
