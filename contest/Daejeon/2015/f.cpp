#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define K 20
int n , m;
vector< int > v[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i <= n ; i ++ )
    v[ i ].clear();
  for( int i = 0 ; i < m ; i ++ ){
    int ui , vi; scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
  }
  for( int i = 1 ; i <= n ; i ++ )
    v[ 0 ].push_back( i );
}
int p[ N ][ K ] , dep[ N ];
inline int lca( int ui , int vi ){
  if( dep[ ui ] > dep[ vi ] ) swap( ui , vi );
  int dlt = dep[ vi ] - dep[ ui ];
  for( int i = 0 ; i < K ; i ++ )
    if( ( dlt >> i ) & 1 )
      vi = p[ vi ][ i ];
  if( ui == vi ) return ui;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ ui ][ i ] != p[ vi ][ i ] ){
      ui = p[ ui ][ i ];
      vi = p[ vi ][ i ];
    }
  return p[ ui ][ 0 ];
}
int in[ N ] , ptr;
bool vvst[ N ];
void go( int now , int prt , int tdep ){
  p[ now ][ 0 ] = prt; dep[ now ] = tdep;
  vvst[ now ] = true;
  in[ now ] = ++ ptr;
  for( int x : v[ now ] ){
    if( x == prt || vvst[ x ] ) continue;
    go( x , now , tdep + 1 );
  }
}
bool ins[ N ] , vst[ N ] , ocyc;
int sstk[ N ] , bk[ N ][ 4 ] , nxt[ N ][ 4 ];
//   odd_step odd_dep
// 0      0     0
// 1      0     1
// 2      1     0
// 3      1     1
void dfs( int now , int prt , int ndep ){
  if( ocyc ) return;
  sstk[ ndep ] = now;
  ins[ now ] = true;
  vst[ now ] = true;
  dep[ now ] = ndep;
  for( int x : v[ now ] ){
    // back_edge
    if( !ins[ x ] ) continue;
    if( ( dep[ now ] - dep[ x ] ) % 2 == 0 ){
      //puts( "BACK" );
      puts( "1" );
      printf( "%d\n" , dep[ now ] - dep[ x ] + 1 );
      for( int i = dep[ x ] ; i <= dep[ now ] ; i ++ )
        printf( "%d\n" , sstk[ i ] );
      ocyc = true;
      return;
    }
    if( dep[ x ] & 1 ){
      if( bk[ now ][ 3 ] == -1 ||
          dep[ x ] < dep[ bk[ now ][ 3 ] ] ){
        bk[ now ][ 3 ] = x;
        nxt[ now ][ 3 ] = x;
      }
    }else{
      if( bk[ now ][ 2 ] == -1 ||
          dep[ x ] < dep[ bk[ now ][ 2 ] ] ){
        bk[ now ][ 2 ] = x;
        nxt[ now ][ 2 ] = x;
      }
    }
  }
  vector< int > cro;
  for( int x : v[ now ] ){
    // cross_edge
    if( ins[ x ] || !vst[ x ] ) continue;
    if( in[ x ] >= in[ now ] ) continue;
    cro.push_back( x );
    int tlca = lca( now , x );
    for( int step = 0 ; step < 2 ; step ++ )
      for( int odep = 0 ; odep < 2 ; odep ++ ){
        if( bk[ x ][ step * 2 + odep ] == -1 ) continue;
        int who = bk[ x ][ step * 2 + odep ];
        if( lca( tlca , who ) != who ) continue;
        int ss = ( step + 1 + dep[ now ] - dep[ who ] ) & 1;
        if( ss == 1 ){
          //puts( "CROSS" );
          vector< int > ans;
          ans.push_back( now );
          int tmp = x , us = step;
          while( tmp != who ){
            ans.push_back( tmp );
            tmp = nxt[ tmp ][ us * 2 + odep ];
            us = 1 - us;
          }
          for( int i = dep[ who ] ; i < dep[ now ] ; i ++ )
            ans.push_back( sstk[ i ] );
          puts( "1" );
          printf( "%d\n" , (int)ans.size() );
          for( size_t i = 0 ; i < ans.size() ; i ++ )
            printf( "%d\n" , ans[ i ] );
          ocyc = true;
          return;
        }
      }
  }
  for( int x : v[ now ] ){
    // forward_edge
    if( ins[ x ] || !vst[ x ] ) continue;
    if( in[ x ] <= in[ now ] ) continue;
    for( int step = 0 ; step < 2 ; step ++ )
      for( int odep = 0 ; odep < 2 ; odep ++ ){
        if( bk[ x ][ step * 2 + odep ] == -1 ) continue;
        int who = bk[ x ][ step * 2 + odep ];
        if( lca( now , who ) != who ) continue;
        int ss = ( step + 1 + dep[ now ] - dep[ who ] ) & 1;
        if( ss == 1 ){
          //puts( "FORWARD" );
          vector< int > ans;
          ans.push_back( now );
          int tmp = x , us = step;
          while( tmp != who ){
            ans.push_back( tmp );
            tmp = nxt[ tmp ][ us * 2 + odep ];
            us = 1 - us;
          }
          for( int i = dep[ who ] ; i < dep[ now ] ; i ++ )
            ans.push_back( sstk[ i ] );
          puts( "1" );
          printf( "%d\n" , (int)ans.size() );
          for( size_t i = 0 ; i < ans.size() ; i ++ )
            printf( "%d\n" , ans[ i ] );
          ocyc = true;
          return;
        }
      }
  }
  for( int x : v[ now ] ){
    // tree_edge
    if( ins[ x ] || vst[ x ] ) continue;
    dfs( x , now , ndep + 1 );
    if( ocyc ) return;
    for( int step = 0 ; step < 2 ; step ++ )
      for( int odep = 0 ; odep < 2 ; odep ++ ){
        if( bk[ x ][ step * 2 + odep ] == -1 ) continue;
        int who = bk[ x ][ step * 2 + odep ];
        if( lca( who , now ) != who ) continue;
        int &sta = bk[ now ][ ( 1 - step ) * 2 + odep ];
        if( sta == -1 || dep[ who ] < dep[ sta ] ){
          sta = who;
          nxt[ now ][ ( 1 - step ) * 2 + odep ] = x;
        }
      }
  }
  for( int x : cro ){
    // cross_edge
    int tlca = lca( now , x );
    for( int step = 0 ; step < 2 ; step ++ )
      for( int odep = 0 ; odep < 2 ; odep ++ ){
        if( bk[ x ][ step * 2 + odep ] == -1 ) continue;
        int who = bk[ x ][ step * 2 + odep ];
        if( lca( tlca , who ) != who ) continue;
        int &sta = bk[ now ][ ( 1 - step ) * 2 + odep ];
        if( sta == -1 || dep[ who ] < dep[ sta ] ){
          sta = who;
          nxt[ now ][ ( 1 - step ) * 2 + odep ] = x;
        }
      }
  }
  ins[ now ] = false;
}
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j < 4 ; j ++ )
      bk[ i ][ j ] = -1;
  ptr = 0;
  for( int i = 0 ; i <= n ; i ++ )
    vvst[ i ] = false;
  go( 0 , 0 , 0 );
  for( int i = 1 ; i < K ; i ++ )
    for( int j = 0 ; j <= n ; j ++ )
      p[ j ][ i ] = p[ p[ j ][ i - 1 ] ][ i - 1 ];
  for( int i = 0 ; i <= n ; i ++ )
    vst[ i ] = ins[ i ] = false;
  ocyc = false;
  dfs( 0 , 0 , 0 );
  if( !ocyc ) puts( "-1" );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
