#include <bits/stdc++.h>
using namespace std;
#define N 514
int n , a[ N ];
queue< char > q[ N ];
stack< char > f[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
  for( int i = 1 ; i <= n ; i ++ ){
    string ss; cin >> ss;
    int len = ss.length();
    for( int j = 0 ; j < len ; j ++ )
      q[ i ].push( ss[ j ] );
  }
}
int who[ N ];
void solve(){
  int nxt = 1;
  for( int move = 1 ; move <= 1000000 ; move ++ ){
    char cc = q[ nxt ].front(); q[ nxt ].pop();
    if( f[ nxt ].size() )
      who[ f[ nxt ].top() - 'A' ] = 0;
    f[ nxt ].push( cc );
    //printf( "%d %c at %d\n" , nxt , cc , move );
    if( who[ cc - 'A' ] ){
      int win = who[ cc - 'A' ] , lose = nxt;
      if( a[ lose ] < a[ win ] ) swap( win , lose );
      while( f[ lose ].size() ){
        q[ lose ].push( f[ lose ].top() ); 
        f[ lose ].pop();
      }
      while( f[ win ].size() ){
        q[ lose ].push( f[ win ].top() ); 
        f[ win ].pop();
      }
      who[ cc - 'A' ] = 0;
    }else{
      who[ cc - 'A' ] = nxt;
    }
    // win
    for( int i = nxt , j = 0 ; j < n ; j ++ , i = ( i == n ? 1 : i + 1 ) )
      if( q[ i ].empty() && f[ i ].empty() ){
        printf( "Player %d wins after %d moves.\n" , i , move );
        exit( 0 );
      }
    // draw
    nxt = ( nxt == n ? 1 : nxt + 1 );
    bool got = false;
    for( int j = 0 ; j < n ; j ++ ){
      if( q[ nxt ].empty() )
        nxt = ( nxt == n ? 1 : nxt + 1 );
      else{
        got = true;
        break;
      }
    }
    if( !got ){
      printf( "Draw after %d moves.\n" , move );
      exit( 0 );
    }
  }
  puts( "Abandoned after 1000000 moves." );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "jungle.in" , "r" , stdin );
  freopen( "jungle.out" , "w" , stdout );
#endif
  init();
  solve();
}
