#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 400000
inline int getint(){
  int _x=0; char _tc=getchar();    
  while( _tc<'0'||_tc>'9' ) _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
//bitset<N> bs , cur;
#define K 32
#define MSK 31
unsigned int bs[ K ][ (N >> 5) + 2 ] , cur[ (N >> 5) + 2 ];
int n , q , ax[ N ] , ay[ N ] , who[ N ];
int main(){
  n = getint();
  q = getint();
  //n = 400000;
  //q = 400000;
  int lst = 0;
  for( int i = 1 , t ; i <= n ; i ++ ){
    t = getint();
    //t = i - 1;
    who[ t ] = i;
    //bs[ t ] = 1;
    cur[ t >> 5 ] |= (1 << (t & MSK) );
    for( int j = 0 ; j < K ; j ++ ){
      if( t - j < 0 ) break;
      int xur = t - j;
      bs[ j ][ xur >> 5 ] |= (1 << (xur & MSK));
    }
  }
  lst = (399999) >> 5;
  ax[ 0 ] = 0;
  ay[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ ){
    // shift = i
    int dlt = i >> 5;
    int sft = i & MSK;
    int x = N;
    for( int j = 0 ; j + dlt <= lst ; j ++ ){
      int vv = cur[ j ] & bs[ sft ][ j + dlt ];
      if( vv ){
        x = __lg( vv & (-vv) ) + (j << 5);
        break;
      }
    }
    //cur >>= 1;
    //int x = (cur & bs)._Find_first();
    if( x == N ){
      ax[ i ] = ax[ i - 1 ];
      ay[ i ] = ay[ i - 1 ];
    }else{
      ax[ i ] = who[ x ];
      ay[ i ] = who[ x + i ];
    }
  }
  while( q -- ){
  //for( int i = 0 ; i < q ; i ++ ){
    int x = getint();
    //int x = i;
    printf( "%d %d\n" , ax[ x ] , ay[ x ] );
  }
}
