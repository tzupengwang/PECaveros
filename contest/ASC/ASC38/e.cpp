#include <bits/stdc++.h>
using namespace std;
map< int , int > M;
#define MX 1000001021
void modify( int pos , int dlt ){
  for( int i = pos ; i < MX ; i += ( i & (-i) ) )
    M[ i ] += dlt;
}
int query( int pos ){
  int sum = 0;
  for( int i = pos ; i ; i -= ( i & (-i) ) )
    sum += M[ i ];
  return sum;
}
int q , pans;
void solve(){
  scanf( "%d" , &q );
  while( q -- ){
    int cmd; scanf( "%d" , &cmd );
    if( cmd == 1 ){
      int li , ri;
      scanf( "%d%d" , &li , &ri );
      li += pans;
      ri += pans;
      li ++;
      ri ++;
      modify( li , +1 );
      modify( ri + 1 , -1 );
    }else{
      int xi;
      scanf( "%d" , &xi );
      xi ++;
      pans = query( xi );
      printf( "%d\n" , pans );
    }
  }
}
int main(){
  freopen( "environment.in" , "r" , stdin );
  freopen( "environment.out" , "w" , stdout );
  solve();
}
