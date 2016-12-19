#include <bits/stdc++.h>
using namespace std;
int nxtp[ 5 ][ 2 ];
int nxtm[ 5 ][ 2 ];
int good[ 5 ][ 2 ];
char c[ 9 ];
#define N 101010
void init(){
  for( int i = 0 ; i < 5 ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ ){ // 0 nice
      scanf( "%s" , c );
      good[ i ][ j ] = c[ 0 ] - '0';
      nxtp[ i ][ j ] = c[ 1 ] == 'L' ? -1 : 1;
      nxtm[ i ][ j ] = c[ 2 ] - 'A';
    }
}
int st[ N ];
//int got[ N ][ 5 ][ 2 ];
//clock_t s;
void solve(){
  int pos = N / 2 , cm = 0 , cnt = 0;
  while( true ){
    ++ cnt;
    //printf( "%d %d\n" , pos , cm );
    if( pos < 0 || pos >= N || cnt > 1e8 ){
      //puts( "unhappy beaver" );
      puts( "unhappy beaver" );
      exit( 0 );
    }
    //got[ pos ][ cm ][ st[ pos ] ] ++;
    int nxm = nxtm[ cm ][ st[ pos ] ];
    if( nxm >= 5 ){
      //puts( "happy beaver" );
      puts( "happy beaver" );
      exit( 0 );
    }
    int nxp = pos + nxtp[ cm ][ st[ pos ] ];
    st[ pos ] = good[ cm ][ st[ pos ] ];
    cm = nxm;
    pos = nxp;
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "beavers.in" , "r" , stdin );
  freopen( "beavers.out" , "w" , stdout );
#endif
  //s = clock();
  init();
  solve();
}
