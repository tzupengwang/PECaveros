#include <bits/stdc++.h>
using namespace std;
long long n , p;
#define N 401
int cnt[ N ] , ps[ N ];
void init(){
  for( int i = 0 ; i < N ; i ++ )
    ps[ i ] = cnt[ i ] = 0;
  while( n -- ){
    int ai , bi;
    scanf( "%d.%d" , &ai , &bi );
    cnt[ ai * 100 + bi ] ++;
    ps[ ai * 100 + bi ] ++;
  }
  for( int i = 399 ; i >= 0 ; i -- )
    ps[ i ] += ps[ i + 1 ];
}
int okay( int ai , int bi ){
  int tans = 0;
  vector< int > vv;
  for( int i = ai ; i <= 400 ; i += bi ){
    int l = i , r = min( 401 , i + bi );
    int sum = ps[ l ];
    if( r < 401 ) sum -= ps[ r ];
    vv.push_back( sum );
  }
  int rg = (int)vv.size();
  if( rg <= 1 ) return 0;
  for( int st = 1 ; st < 100 ; st ++ ){
    long long sum = 0 , dlt = 0;
    for( size_t j = 0 ; j < vv.size() ; j ++ ){
      sum += (long long)vv[ j ] * st;
      if( sum > p ) break;
      dlt += (long long)vv[ j ] * j;
    }
    if( sum > p ) break;
    if( dlt == 0 ){
      if( sum == p ){
        int mx = ( 100 - st ) / ( rg - 1 );
        if( 1 <= mx )
          tans += mx;
      }
    }else if( ( p - sum ) % dlt == 0 ){
      long long dd = ( p - sum ) / dlt;
      if( st + ( rg - 1 ) * dd <= 100 && dd )
        tans ++;
    }
  }
  return tans;
}
void solve(){
  int ans = 0;
  for( int i = 250 ; i < 400 ; i ++ )
    for( int d = 1 ; i + d <= 400 ; d ++ )
      ans += okay( i , d );
  printf( "%d\n" , ans );
}
int main(){
  while( scanf( "%lld%lld" , &n , &p ) == 2 ){
    if( n == 0 && p == 0 ) break;
    init();
    solve();
  }
}
