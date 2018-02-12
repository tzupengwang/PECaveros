#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 5140
LL n , w , h , m , len;
LL sumx[ N ] , sumy[ N ];
int lftmst[ N ] , rgtmst[ N ] , bb[ N ];
unordered_set<int> bye[ N ];
void pre_solve(){
  len = w * n * 2;
  sumy[ 1 ] = (w * n) * n;
  sumx[ 1 ] = (2 + (n - 1) * 2) * n * w / 2;
  sumy[ 2 ] = sumx[ 1 ];
  sumx[ 2 ] = sumy[ 1 ];
  for( int i = 3 ; i <= h ; i ++ ){
    sumx[ i ] = sumx[ i - 2 ];
    sumy[ i ] = sumy[ i - 2 ];
  }
  for( int i = 1 ; i <= h ; i ++ ){
    lftmst[ i ] = 1;
    rgtmst[ i ] = n;
  }
}
bool remove( int li , int ki ){
  LL curx = (ki * 2 - 1) * w , cury = (w * n);
  if( li % 2 == 0 ) swap( curx , cury );
  bb[ li ] ++;
  sumx[ li ] -= curx;
  sumy[ li ] -= cury;
  bye[ li ].insert( ki );
  while( lftmst[ li ] <= rgtmst[ li ] and
         bye[ li ].find( lftmst[ li ] ) != bye[ li ].end() )
    lftmst[ li ] ++;
  while( lftmst[ li ] <= rgtmst[ li ] and
         bye[ li ].find( rgtmst[ li ] ) != bye[ li ].end() )
    rgtmst[ li ] --;
  if( lftmst[ li ] > rgtmst[ li ] )
    return true;
  LL n_tot = 0 , totx = 0 , toty = 0;
  for( int i = h - 1 ; i >= 1 ; i -- ){
    n_tot += n - bb[ i + 1 ];
    totx += sumx[ i + 1 ];
    toty += sumy[ i + 1 ];
    if( i & 1 ){
      if( totx <= (lftmst[ i ] * 2 - 2) * w * n_tot or
          totx >= (rgtmst[ i ] * 2    ) * w * n_tot )
        return true;
    }else{
      if( toty <= (lftmst[ i ] * 2 - 2) * w * n_tot or
          toty >= (rgtmst[ i ] * 2    ) * w * n_tot )
        return true;
    }
  }
  return false;
}
void solve(){
  for( int i = 0 ; i < m ; i ++ ){
    int li , ki;
    scanf( "%d%d" , &li , &ki );
    if( remove( li , ki ) ){
      printf( "yes\n%d\n" , i + 1 );
      exit(0);
    }
  }
  puts( "no" );
}
int main(){
#ifndef LOCAL
  freopen( "jenga.in" , "r" , stdin );
  freopen( "jenga.out" , "w" , stdout );
#endif
  scanf( "%lld%lld" , &n , &w );
  scanf( "%lld%lld" , &h , &m );
  pre_solve();
  solve();
}
