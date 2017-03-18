#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , c[ N ];
bool tag[ 10101010 ];
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &c[ i ] );
  sort( c , c + n );
  for( int i = 0 ; i < n ; i ++ )
    tag[ c[ i ] ] = true;
  vector<int> ans;
  for( int i = 0 ; i < n ; i ++ ){
    bool gg = false;
    for( int j = c[ i ] + c[ i ] ; j < 10000001 ; j += c[ i ] )
      if( tag[ j ] ){
        gg = true;
        break;
      }
    if( !gg )
      ans.push_back( c[ i ] );
  }
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
