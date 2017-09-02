#include <bits/stdc++.h>
using namespace std;
#define N 100000
bool p[ N ];
vector<int> pset;
void build(){
  for( int i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
    pset.push_back( i );
    for( int j = i ; j < N ; j += i )
      p[ j ] = true;
  }
  reverse( pset.begin() , pset.end() );
}
char c[ 1021 ] , tmp[ 1021 ];
int main(){
  build();
  while( scanf( "%s" , c ) == 1 ){
    if( strlen( c ) == 1 and c[ 0 ] == '0' ) break;
    int len = strlen( c );
    for( auto i : pset ){
      sprintf( tmp , "%d" , i );
      int tlen = strlen( tmp );
      bool found = false;
      for( int j = 0 ; j <= len - tlen and !found ; j ++ ){
        bool eq = true;
        for( int k = 0 ; k < tlen ; k ++ )
          if( tmp[ k ] != c[ j + k ] ){
            eq = false;
            break;
          }
        if( eq ) found = true;
      }
      if( found ){
        printf( "%d\n" , i );
        break;
      }
    }
  }
}
