#include <bits/stdc++.h>
using namespace std;
#define N 20202
typedef long long LL;
int n , r;
vector<int> vv;
void init(){
  vv.clear();
  for( int i = 0 ; i < n ; i ++ ){
    int x , y;
    scanf( "%d.%d" , &x , &y );
    vv.push_back( x * 1000 + y );
  }
  sort( vv.begin() , vv.end() );
}
int hf = 180000;
LL C( LL x ){
  return x * ( x - 1 ) / 2;
}
int _cs;
void solve(){
  LL tot = (LL)n * (LL)( n - 1 ) * (LL)( n - 2 ) / 6;
  for( int i = 0 ; i < n ; i ++ )
    vv.push_back( vv[ i ] + hf + hf );
  for( int i = 0 , j = 0 ; i < n ; i ++ ){
    while( vv[ j ] <= vv[ i ] + hf ) j ++;
    int res = j - i - 1;
    tot -= C( res );
  }
  printf( "Case %d: %lld\n" , ++ _cs, tot );
}
int main(){
  while( scanf( "%d%d" , &n , & r ) == 2 && n ){
    init();
    solve();
  }
}
