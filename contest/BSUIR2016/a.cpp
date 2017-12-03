#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
typedef long long LL;
const int mod = 1000000007;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
vector<int> fac[ N ];
#define X 101010
int BIT[ X ] , lb[ X ];
void modify( int x , int d ){
  for( int i = x ; i < X ; i += lb[ i ] )
    BIT[ i ] = add( BIT[ i ] , d );
}
int query( int x ){
  int ret = 0;
  for( int i = x ; i ; i -= lb[ i ] )
    ret = add( ret , BIT[ i ] );
  return ret;
}
void build(){
  for( int i = 1 ; i < N ; i ++ )
    for( int j = i ; j < N ; j += i )
      fac[ j ].push_back( i );
  for( int i = 1 ; i < X ; i ++ )
    lb[ i ] = i & (-i);
}
int n , a[ X ] , b[ X ];
void init(){
  scanf( "%d" , &n );
  //n = 100000;
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
    //a[ i ] = i;
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &b[ i ] );
    //b[ i ] = 720720;

  vector<int> li;
  for( int i = 1 ; i <= n ; i ++ )
    li.push_back( a[ i ] );
  sort( li.begin() , li.end() );
  li.resize( unique( li.begin() , li.end() ) - li.begin() );
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = lower_bound( li.begin() , li.end() , a[ i ] ) - li.begin() + 1;
}
vector<int> cand[ N ];
int ans[ N ] , sv[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j : fac[ b[ i ] ] )
      cand[ j ].push_back( i );
  for( int i = 1 ; i < N ; i ++ ){
    for( int j : cand[ i ] ){
      int cnt = add( query( a[ j ] - 1 ) , 1 );
      ans[ i ] = add( ans[ i ] , cnt );
      sv[ j ] = cnt;
      modify( a[ j ] , cnt );
    }
    for( int j : cand[ i ] )
      modify( a[ j ] , sub( 0 , sv[ j ] ) );
  }
  int fans = 0;
  for( int i = N - 1 ; i >= 1 ; i -- ){
    for( int j = i + i ; j < N ; j += i )
      ans[ i ] = sub( ans[ i ] , ans[ j ] );
    fans = add( fans , mul( ans[ i ] , i ) );
  }
  printf( "%d\n" , fans );
}
int main(){
  build();
  init();
  solve();
}
