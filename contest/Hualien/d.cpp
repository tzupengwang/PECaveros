#include <bits/stdc++.h>
using namespace std;
#define N 222
#define INF 10000000
int n , m;
int d[ N ][ N ];
int main(){
  while( cin >> n and n ){
    cin >> m;
    for( int i = 0 ; i < n ; i ++ ){
      for( int j = 0 ; j < n ; j ++ )
        d[ i ][ j ] = INF;
      d[ i ][ i ]=  0;
    }
    while( m -- ){
      int a , b;
      cin >> a >> b;
      d[ a ][ b ] = d[ b ][ a ] = 1;
    }
    for( int k = 0 ; k < n ; k ++ )
      for( int i = 0 ; i < n ; i ++ )
        for( int j = 0 ; j < n ; j ++ )
          d[ i ][ j ] = min( d[ i ][ j ] ,
                             d[ i ][ k ] + d[ k ][ j ] );
    map<int,int> M;
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        if( i != j )
          M[ d[ i ][ j ] ] ++;
    for( auto i : M )
      printf( "%d %d\n" , i.first , i.second );
  }
}
