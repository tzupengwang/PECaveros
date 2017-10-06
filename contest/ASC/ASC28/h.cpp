#include <bits/stdc++.h>
using namespace std;
#define N 1021
vector< tuple<int,int,int> > e;
int d[ N ];
int main(){
#ifdef ONLINE_JUDGE
  freopen( "test.in" , "r" , stdin );
  freopen( "test.out" , "w" , stdout );
#endif
  int n , m;
  cin >> n >> m;
  for( int i = 1 ; i < n ; i ++ )
    e.push_back( make_tuple( i , i + 1 , 1 ) );
  m -= n - 1;
  for( int i = 2 ; i <= n ; i ++ )
    d[ i ] = 1000000;
  for( int i = 1 ; i < n and m > 0 ; i ++ )
    for( int j = i + 2 ; j <= n and m > 0 ; j ++ ){
      d[ j ] --;
      e.push_back( make_tuple( i , j , d[ j ] - ( i - 1 ) ) );
      m --;
    }
  for( auto i : e )
    printf( "%d %d %d\n" , get<0>( i ) , get<1>( i ) , get<2>( i ) );
}
