#include <bits/stdc++.h>
using namespace std;
#define N 1021
struct Tree{
  char c[ N * 10 ] , clr[ N ];
  vector< int > son[ N ];
  int n , len , id[ N * 10 ] , pr[ N * 10 ];
  int root , sz[ N ];
  int go( int l , int r ){
    int now = id[ l ];
    clr[ now ] = c[ l ];
    for( int i = l + 1 ; i <= r ; ){
      son[ now ].push_back( go( i + 1 , pr[ i ] - 1 ) );
      i = pr[ i ] + 1;
    }
    return now;
  }
  void go2( int now ){
    sz[ now ] = 1;
    for( int x : son[ now ] ){
      go2( x );
      sz[ now ] += sz[ x ];
    }
  }
  void parse(){
    vector< int > vv;
    for( int i = 0 ; i < len ; i ++ )
      if( c[ i ] == '(' )
        vv.push_back( i );
      else if( c[ i ] == ')' ){
        pr[ vv.back() ] = i;
        vv.pop_back();
      }
    root = go( 1 , len - 2 );
    go2( root );
  }
  void init(){
    scanf( "%s" , c );
    len = strlen( c );
    n = 0;
    for( int i = 0 ; c[ i ] ; i ++ )
      if( isalpha( c[ i ] ) )
        id[ i ] = ++ n;
    for( int i = 1 ; i <= n ; i ++ )
      son[ i ].clear();
    parse();
    //printf( "%d\n" , root );
    //for( int i = 1 ; i <= n ; i ++ )
      //printf( "%d %d\n" , i , sz[ i ] );
    //for( int i = 1 ; i <= n ; i ++ )
      //for( int x : son[ i ] )
        //printf( "%d %d\n" , i , x );
    //puts( "" );
    //exit( 0 );
  }
} t[ 2 ];
void init(){
  for( int i = 0 ; i < 2 ; i ++ )
    t[ i ].init();
}
int dp[ N ][ N ] , tdp[ N ][ N ];
#define INF 10000000
void DP( int nd1 , int nd2 ){
  if( dp[ nd1 ][ nd2 ] != -1 ) return;
  for( int s1 : t[ 0 ].son[ nd1 ] )
    for( int s2 : t[ 1 ].son[ nd2 ] )
      DP( s1 , s2 );
  int n1 = (int)t[ 0 ].son[ nd1 ].size();
  int n2 = (int)t[ 1 ].son[ nd2 ].size();
  for( int i = 0 ; i <= n1 ; i ++ )
    for( int j = 0 ; j <= n2 ; j ++ ){
      if( i == 0 && j == 0 ){
        tdp[ i ][ j ] = 0;
        continue;
      }
      tdp[ i ][ j ] = INF;
      if( i > 0 ){
        int tcst = tdp[ i - 1 ][ j ] + t[ 0 ].sz[ t[ 0 ].son[ nd1 ][ i - 1 ] ];
        if( tcst < tdp[ i ][ j ] ) tdp[ i ][ j ] = tcst;
        //if( nd1 == 2 && nd2 == 2 ){
          //printf( "%d %d cst: %d\n" , i , j , tcst );
        //}
      }
      if( j > 0 ){
        int tcst = tdp[ i ][ j - 1 ] + t[ 1 ].sz[ t[ 1 ].son[ nd2 ][ j - 1 ] ];
        if( tcst < tdp[ i ][ j ] ) tdp[ i ][ j ] = tcst;
        //if( nd1 == 2 && nd2 == 2 ){
          //printf( "%d %d cst: %d\n" , i , j , tcst );
        //}
      }
      if( i > 0 && j > 0 ){
        int tcst = tdp[ i - 1 ][ j - 1 ] + dp[ t[ 0 ].son[ nd1 ][ i - 1 ] ][ t[ 1 ].son[ nd2 ][ j - 1 ] ];
        if( tcst < tdp[ i ][ j ] ) tdp[ i ][ j ] = tcst;
        //if( nd1 == 2 && nd2 == 2 ){
          //printf( "%d %d cst: %d\n" , i , j , tcst );
        //}
      }
    }
  dp[ nd1 ][ nd2 ] = tdp[ n1 ][ n2 ] + ( t[ 0 ].clr[ nd1 ] != t[ 1 ].clr[ nd2 ] );
  //printf( "%d %d : %d\n" , nd1 , nd2 , dp[ nd1 ][ nd2 ] );
}
void solve(){
  int n1 = t[ 0 ].n , n2 = t[ 1 ].n;
  for( int i = 1 ; i <= n1 ; i ++ )
    for( int j = 1 ; j <= n2 ; j ++ )
      dp[ i ][ j ] = -1;
  DP( t[ 0 ].root , t[ 1 ].root );
  printf( "%d\n" , dp[ t[ 0 ].root ][ t[ 1 ].root ] );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
