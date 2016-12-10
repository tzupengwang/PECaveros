#include <bits/stdc++.h>
using namespace std;
#define N 101010
char c[ N ];
int cnt[ 26 ] , id;
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    scanf( "%s" , c );
    for( int i = 0 ; i < 26 ; i ++ ) cnt[ i ] = 0;
    for( int i = 0 ; c[ i ] ; i ++ )
      cnt[ c[ i ] - 'a' ] ++;
    int ans = *min_element( cnt , cnt + 26 );
    printf( "Case %d: %d\n" , ++id ,  ans );
  }
}
