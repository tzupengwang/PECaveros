#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector< tuple<int,int,int> > ans;
void solve( int x , int y , int z ){
  int dx = -100 , dy = -100;
  while( x < y + z - 1 ){
    ans.push_back( make_tuple( dx , dy , 0 ) );
    x --;
    y --;
    z --;
    dx ++;
    dy ++;
  }
  for( int i = 0 ; i < y ; i ++ )
    ans.push_back( make_tuple( dx + i , dy , 0 ) );
  for( int i = 1 ; i < z ; i ++ )
    ans.push_back( make_tuple( dx , dy + i , 0 ) );
  int res = x - (y + z - 1);
  for( int i = 1 ; i < y and res > 0 ; i ++ )
    for( int j = 1 ; j < z and res > 0 ; j ++ ){
      ans.push_back( make_tuple( dx + i , dy + j , 0 ) );
      res --;
    }
}
int a , b , c;
int main(){
  cin >> a >> b >> c;
  int mx = max( a , max( b , c ) );
  int mn = min( a , min( b , c ) );
  int md = a + b + c - mx - mn;
  if( mx > mn * md ){
    puts( "-1" );
    exit(0);
  }
  if( a >= b and a >= c )
    solve( a , b , c );
  else if( b >= a and b >= c ){
    solve( b , a , c );
    for( auto&& pp : ans )
      swap( get<1>( pp ) , get<2>( pp ) );
  }
  else if( c >= a and c >= b ){
    solve( c , a , b );
    for( auto&& pp : ans ){
      int x = get<0>( pp );
      int y = get<1>( pp );
      int z = get<2>( pp );
      pp = make_tuple( z , x , y );
    }
  }
  printf( "%d\n" , (int)ans.size() );
  for( auto x : ans )
    printf( "%d %d %d\n" , get<0>( x ) , get<1>( x ) , get<2>( x ) );
}
