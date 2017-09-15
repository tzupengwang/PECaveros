#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1111
int sg[ N ];
int main(){
#ifdef ONLINE_JUDGE
  freopen( "nim.in" , "r" , stdin );
  freopen( "nim.out" , "w" , stdout );
#endif
  //sg[ 0 ] = 0;
  //for( int i = 1 ; i < N ; i ++ ){
    //int til = 1;
    //while( til * til <= i ) til ++;
    //til --;
    //set<int> S;
    //for( int j = 1 ; j <= til ; j ++ )
      //S.insert( sg[ i - j ] );
    //while( S.count( sg[ i ] ) )
      //sg[ i ] ++;
  //}
  ////for( int i = 0 ; i < 100 ; i ++ ){
    //printf( "%4d " , sg[ i ] );
    //if( i % 10 == 9 ) puts( "" );
  //}
  //for( int i = 0 ; i < N ; i ++ )
    //if( !sg[ i ] )
      //printf( "%d\n" , i );
  LL n; cin >> n;
  LL gt = 0 , add = 2 , res = 1;
  while( gt < n ){
    gt += add; res --;
    if( res == 0 ){
      add ++; res = 2;
      if( add == ( add & (-add) ) )
        res --;
    }
  }
  puts( gt == n ? "LOSE" : "WIN" );
}
