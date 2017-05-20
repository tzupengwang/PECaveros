#include <bits/stdc++.h>
using namespace std;
#define N 505050
char c[ N ] , ccc[ N ];
int a , b , tlen[ N ] , p[ N ];
bool lst[ N ];
int main(){
  while( fgets( c , N , stdin ) ){
    fgets( ccc , N , stdin );
    sscanf( ccc , "%d%d" , &a , &b );
    int len = strlen( c ) - 1;
    for( int i = 0 , pp = 0 ; i < len ; i ++ ){
      lst[ i ] = false;
      if( i + 1 == len or c[ i + 1 ] == ' ' )
        lst[ i ] = true;
      p[ i ] = pp;
      if( c[ i ] == ' ' ) pp = i + 1;
      if( i == 0 or c[ i - 1 ] == ' ' ){
        int til = i;
        while( til < len and ( isalpha( c[ til ] ) ) ) til ++;
        tlen[ i ] = til - i;
      }
    }
    for( int i = a ; i <= b ; i ++ ){
      int now = 0 , cc = 0;
      while( now < len ){
        assert( tlen[ now ] > 0 );
        if( cc ) cc ++;
        cc += tlen[ now ];
        now += i - 1;
        if( now >= len ) break;
        if( c[ now ] == ' ' ){
          now ++;
          continue;
        }
        if( lst[ now ] ){
          now += 2;
          continue;
        }
        now = p[ now ];
      }
      printf( "%d\n" , cc );
    }
  }
}
