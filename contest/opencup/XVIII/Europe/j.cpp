#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1010101
int n , c[ N ];
vector<int> v[ N ];
int go( int now , int prt ){
  int sz = 1;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    sz += go( son , now );
  }
  c[ sz ] ++;
  return sz;
}
bool tg[ N ];
int main(){
  scanf( "%d" , &n );
  //n = 720720;
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    //int ui = i + 1;
    //int vi = i;
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
  go( 1 , 1 );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + i ; j <= n ; j += i )
      c[ i ] += c[ j ];
  vector<int> ans;
  ans.push_back( n - 1 );
  for( int i = 2 ; i < n ; i ++ ){
    if( n % i ) continue;
    int nd = ( i - 1 ) * ( n / i );
    if( c[ i ] == n / i )
      ans.push_back( n - 1 - nd );
  }
  reverse( ans.begin() , ans.end() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
