#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PLL;
vector< PLL > v;
inline bool cmp( PLL p1 , PLL p2 ){
  return p1.first * p2.second > p1.second * p2.first;
}
void build(){
  vector< pair< LL , PLL > > qq;
  for( int i = 1 ; i <= 1021 ; i ++ )
    for( int j = 1 ; j <= 1021 ; j ++ )
      if( __gcd( i , j ) == 1 )
        qq.push_back( { i * i + j * j , { i , j } } );
  // printf( "%d\n" , (int)vv.size() );
  sort( qq.begin() , qq.end() );
  for( int i = 0 ; i < 100000 ; i ++ )
    v.push_back( qq[ i ].second );
  sort( v.begin() , v.end() , cmp );
  // printf( "%lld %lld\n" , v[ 0 ].first , v[ 0 ].second );
  // printf( "%lld %lld\n" , v.back().first , v.back().second );
  for( int i = 99999 ; i >= 0 ; i -- )
    v.push_back( { -v[ i ].first , +v[ i ].second } );
  for( int i = 199999 ; i >= 0 ; i -- )
    v.push_back( { +v[ i ].first , -v[ i ].second } );
}
int main(){
  build();
  int n; scanf( "%d" , &n );
  PLL tp = { 20000000 , 0 };
  for( int i = 0 ; i < n ; i ++ ){
    printf( "%lld %lld\n" , tp.first , tp.second );
    tp.first += v[ i ].first;
    tp.second += v[ i ].second;
  }
}
