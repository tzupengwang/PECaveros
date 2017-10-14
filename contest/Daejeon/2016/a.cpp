#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , m , deg[ N ];
set< pair<int,int> > M;
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    for( int i = 0 ; i < n ; i ++ )
      deg[ i ] = 0;
    M.clear();
    while( m -- ){
      int ui , vi;
      scanf( "%d%d" , &ui , &vi );
      M.insert( { ui , vi } );
      M.insert( { vi , ui } );
      deg[ ui ] ++;
      deg[ vi ] ++;
    }
    int ans = 0;
    for( int i = 0 ; i < n ; i ++ )
      if( ( deg[ i ] == 1 or deg[ ( i + 1 ) % n ] == 1 ) and
          ( M.find( make_pair( i , ( i + 1 ) % n ) ) == M.end() ) ){
        ans ++;
        deg[ i ] ++;
        deg[ ( i + 1 ) % n ] ++;
      }
    printf( "%d\n" , ans );
  }
}
