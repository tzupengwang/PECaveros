#include <bits/stdc++.h>
using namespace std;

typedef pair< int , int > ii ;

int n , n2 ;
vector< int > v[ 100005 ] ;
int deg[ 100005 ] ;
int deg2[ 100005 ] ;
int id[ 100005 ] ;
int ans[ 100005 ] ;
int col[ 100005 ] ;
deque< int > cand ;
set< ii > st ;

unsigned long long rest[ 101010 ];
unsigned long long pos[ 101010 ];

int main() {
#ifdef ONLINE_JUDGE
  freopen( "bicoloring.in" , "r" , stdin ) ;
  freopen( "bicoloring.out" , "w" , stdout ) ;
#endif
  scanf( "%d" , &n2 ) ;
  n = n2 / 2 ;
  for ( int i = 1 ; i < n2 ; i ++ ) {
    int x , y ;
    scanf( "%d%d" , &x , &y ) ;
    deg[ x ] ++ ;
    deg[ y ] ++ ;
    v[ x ].push_back( y ) ;
    v[ y ].push_back( x ) ;
  }
  for ( int i = 1 ; i <= n2 ; i ++ ) id[ i ] = i ;
  sort( id + 1 , id + n2 + 1 , [&]( int x , int y ) {
    return deg[ x ] > deg[ y ] ;
  }) ;
  for ( int i = 1 ; i <= n + 1 ; i ++ ) {
    ans[ id[ i ] ] = i ;
    for ( int ng : v[ id[ i ] ] ) {
      if ( ans[ ng ] ) {
        deg2[ ng ] ++ ;
        deg2[ id[ i ] ] ++ ;
        st.insert( ii( ans[ ng ] , i ) ) ;
        st.insert( ii( i , ans[ ng ] ) ) ;
      }
    }
  }
  int lst = 0;
  //for ( int i = 1 ; i <= n + 1 ; i ++ ) col[ i ] = i ;
  //random_shuffle( col + 1 , col + n + 2 ) ;
  for( int i = 1 ; i <= n + 1 ; i ++ ){
    rest[ i / 64 ] |= ( 1llu << ( i % 64 ) );
    pos[ i / 64 ] |= ( 1llu << ( i % 64 ) );
    lst = i / 64;
  }
  //for ( int i = 1 ; i <= n + 1 ; i ++ ) cand.push_back( col[ i ] ) ;
  for ( int i = n + 1 + 1 ; i <= 2 * n ; i ++ ) {
    for ( int ng : v[ id[ i ] ] ) {
      if ( ans[ ng ] )
        deg2[ id[ i ] ] += 1 + deg2[ ng ] ;
    }
  }
  sort( id + n + 1 + 1 , id + n2 + 1 , [&]( int x , int y ) {
    if ( deg[ x ] != deg[ y ] ) return deg[ x ] > deg[ y ] ;
    return deg2[ x ] > deg2[ y ] ;
  }) ;
  priority_queue< pair<int,int> > Q;
  for( int i = n + 1 + 1 ; i <= 2 * n ; i ++ )
    Q.push( { deg2[ id[ i ] ] , id[ i ] } );

  for ( int i = n + 1 + 1 ; i <= 2 * n ; i ++ ) {
    int now = Q.top().second; Q.pop();
    if( ans[ now ] ){
      i --;
      continue;
    }
    vector< int > bye;
    for( int ng : v[ now ] )
      if( ans[ ng ] )
        bye.push_back( ans[ ng ] );

    for( int x : bye ) pos[ x / 64 ] ^= ( 1llu << ( x % 64 ) );

    for( int j = lst ; j >= 0 ; j -- ){
      unsigned long long kk = pos[ j ] & rest[ j ];
      bool flag = false;
      while( kk ){
        unsigned long long tmp = kk & (-kk); kk -= tmp;
        int can = j * 64 + __lg( tmp );
        bool okay = true ;
        for ( int ng : v[ now ] ) {
          if ( ans[ ng ] != 0 && st.count( ii( can , ans[ ng ] ) ) ) {
            okay = false ;
            break ;
          }
        }
        if ( okay ) {
          ans[ now ] = can ;
          rest[ can / 64 ] ^= ( 1llu << ( can % 64 ) );
          for ( int ng : v[ now ] ) {
            if ( ans[ ng ] ) {
              st.insert( ii( ans[ ng ] , can ) ) ;
              st.insert( ii( can , ans[ ng ] ) ) ;
            }else{
              deg2[ ng ] += 1 + deg2[ now ];
              Q.push( { deg2[ ng ] , ng } );
            }
          }
          flag = true;
          break ;
        }
      }
      if( flag ) break;
    }

    for( int x : bye ) pos[ x / 64 ] ^= ( 1llu << ( x % 64 ) );

    //while ( true ) {
      //int can = cand.front() ; cand.pop_front() ;
      //bool okay = true ;
      //for ( int ng : v[ now ] ) {
        //if ( ans[ ng ] == can || ( ans[ ng ] != 0 && st.count( ii( can , ans[ ng ] ) ) ) ) {
          //okay = false ;
          //break ;
        //}
      //}
      //if ( okay ) {
        //ans[ now ] = can ;
        //for ( int ng : v[ now ] ) {
          //if ( ans[ ng ] ) {
            //st.insert( ii( ans[ ng ] , can ) ) ;
            //st.insert( ii( can , ans[ ng ] ) ) ;
          //}else{
            //deg2[ ng ] += 1 + deg2[ now ];
            //if( !ans[ ng ] )
              //Q.push( { deg2[ ng ] , ng } );
          //}
        //}
        //break ;
      //} else {
        //cand.push_back( can ) ;
      //}
    //}
  }
  for ( int i = 1 ; i <= 2 * n ; i ++ ) {
    printf( "%d%c" , ans[ i ] , " \n"[ i == 2 * n ] ) ;
  }

  return 0 ;
}
