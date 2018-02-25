#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b , int smod = mod ){
  a -= b;
  return a < 0 ? a + smod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
#define N 202020
int n , m , a[ N ] , q , ql[ N ] , qr[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    a[ i ] %= m;
  }
  scanf( "%d" , &q );
  for( int i = 0 ; i < q ; i ++ )
    scanf( "%d%d" , &ql[ i ] , &qr[ i ] );
}
int ans[ N ];
int ldp[ N ][ 20 ] , rdp[ N ][ 20 ];
void go( int lb , int rb , const vector<int>& wt ){
  if( wt.empty() ) return;
  int mid = (lb + rb) >> 1;
  {
    for( int i = 0 ; i < m ; i ++ )
      ldp[ mid + 1 ][ i ] = 0;
    ldp[ mid + 1 ][ 0 ] = 1;
    for( int i = mid ; i >= lb ; i -- )
      for( int j = 0 ; j < m ; j ++ )
        ldp[ i ][ j ] = add( ldp[ i + 1 ][ j ] ,
                             ldp[ i + 1 ][ sub( j , a[ i ] , m ) ] );
  }
  {
    for( int i = 0 ; i < m ; i ++ )
      rdp[ mid ][ i ] = 0;
    rdp[ mid ][ 0 ] = 1;
    for( int i = mid + 1 ; i <= rb ; i ++ )
      for( int j = 0 ; j < m ; j ++ )
        rdp[ i ][ j ] = add( rdp[ i - 1 ][ j ] ,
                             rdp[ i - 1 ][ sub( j , a[ i ] , m ) ] );
  }
  vector<int> to_l , to_r;
  for( auto qid : wt ){
    int cql = ql[ qid ] , cqr = qr[ qid ];
    if( cql <= mid + 1 and cqr >= mid ){
      //printf( "deal with %d lb = %d, rb = %d, mid = %d, ql = %d,  qr = %d\n" ,
              //qid , lb , rb , mid , cql , cqr );
      for( int i = 0 ; i < m ; i ++ )
        ans[ qid ] = add( ans[ qid ] , 
                          mul( ldp[ cql ][ i ] , rdp[ cqr ][ (m - i) % m ] ) );
      continue;
    }
    if( cqr <= mid )
      to_l.push_back( qid );
    else if( mid < cql )
      to_r.push_back( qid );
    else
      assert( false );
  }
  go( lb , mid , to_l );
  go( mid + 1 , rb , to_r );
}
void solve(){
  vector<int> cand;
  for( int i = 0 ; i < q ; i ++ )
    cand.push_back( i );
  go( 1 , n , cand );
  for( int i = 0 ; i < q ; i ++ )
    printf( "%d\n" , ans[ i ] );
}
int main(){
  init();
  solve();
}
