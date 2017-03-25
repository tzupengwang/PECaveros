#include <bits/stdc++.h>
using namespace std;
#define N 303030
typedef long long LL;
typedef pair<int,int> PII;
const LL INF = 10000000000000000LL;
map< pair<int,int> , int > M;
vector< int > qq[ N ];
LL o[ N ][ 2 ] , r[ N ][ 2 ];
int n , d , a[ N ] , mid;
void init(){
  scanf( "%d%d" , &n , &d );
  for( int i = 1 ; i <= d ; i ++ )
    scanf( "%d" , &a[ i ] );
  for( int i = 1 ; i < d ; i ++ ){
    int a1 = a[ i ] , a2 = a[ i + 1 ];
    if( a1 > a2 ) swap( a1 , a2 );
    if( M.count( { a1 , a2 } ) == 0 ){
      o[ mid ][ 0 ] = 
      o[ mid ][ 1 ] = 
      r[ mid ][ 0 ] = 
      r[ mid ][ 1 ] = INF;
      M[ { a1 , a2 } ] = mid ++;
    }
    qq[ M[ { a1 , a2 } ] ].push_back( a1 == a[ i ] ? 0 : 1 );
  }
  int m; scanf( "%d" , &m ); while( m -- ){
    int ai , bi; char ci[ 9 ]; LL di;
    scanf( "%d%d%s%lld" , &ai , &bi , ci , &di );
    int a1 = ai , a2 = bi;
    if( a1 > a2 ) swap( a1 , a2 );
    if( M.count( { a1 , a2 } ) == 0 ) continue;
    int id = M[ { a1 , a2 } ] , at = 0;
    if( a1 != ai ) at = 1;
    if( ci[ 0 ] == 'O' )
      o[ id ][ at ] = min( o[ id ][ at ] , di );
    else
      r[ id ][ at ] = min( r[ id ][ at ] , di );
  }
}
LL ans;
void solve(){
  //for( auto i : M )
    //printf( "%d %d : %d\n" , i.first.first , i.first.second , i.second );
  for( int i = 0 ; i < mid ; i ++ ){
    int sz = (int)qq[ i ].size();
    LL tans = 0;
    o[ i ][ 0 ] = min( o[ i ][ 0 ] , r[ i ][ 0 ] );
    o[ i ][ 1 ] = min( o[ i ][ 1 ] , r[ i ][ 1 ] );
    for( int j = 0 ; j < sz ; j ++ )
      tans += o[ i ][ qq[ i ][ j ] ];
    vector<int> v[ 2 ];
    for( int j = 0 ; j < sz ; j ++ )
      v[ qq[ i ][ j ] ].push_back( j );
    int ssz[ 2 ];
    for( int j = 0 ; j < 2 ; j ++ )
      ssz[ j ] = (int)v[ j ].size();
    int bl = 0 , br = min( ssz[ 0 ] , ssz[ 1 ] ) , ba = 0;
    while( bl <= br ){
      int bmid = ( bl + br ) >> 1;
      bool ok = true;
      for( int ii = 0 , j = bmid ; ii < bmid ; ii ++ , j -- )
        if( v[ 0 ][ ii ] > v[ 1 ][ ssz[ 1 ] - j ] ){
          ok = false;
          break;
        }
      if( ok ) ba = bmid , bl = bmid + 1;
      else br = bmid - 1;
    }
    vector<int> tv[ 2 ];
    for( int j = 0 ; j < ba ; j ++ ){
      tv[ 0 ].push_back( v[ 0 ][ j ] );
      tv[ 1 ].push_back( v[ 1 ][ ssz[ 1 ] - j - 1 ] );
    }

    LL bans = tans;
    bans = min( bans ,
                tans - (LL)ba * max( 0ll , ( o[ i ][ 0 ] + o[ i ][ 1 ] - r[ i ][ 0 ] ) ) );
    
    vector<int> bs;
    bs.resize( sz );
    for( int j = sz - 1 ; j >= 0 ; j -- ){
      bs[ j ] = ( qq[ i ][ j ] == 0 );
      if( j < sz - 1 ) bs[ j ] += bs[ j + 1 ];
    }

    for( int j = 0 , mx = sz , pre = 0 ; j < sz ; j ++ ){
      if( qq[ i ][ j ] == 0 ) continue;
      // ( 1 , 0 )
      mx = min( mx , pre + bs[ j ] );
      if( mx < pre + 1 ) break;
      pre ++;
      int nxt0 = v[ 0 ].back(); v[ 0 ].pop_back();
      if( ( tv[ 1 ].size() and j    == tv[ 1 ].back() ) or
          ( tv[ 0 ].size() and nxt0 == tv[ 0 ].back() ) ){
        tv[ 1 ].pop_back();
        tv[ 0 ].pop_back();
      }
      
      bans = min( bans ,
        tans - (LL)tv[ 0 ].size() * max( 0ll , ( o[ i ][ 0 ] + o[ i ][ 1 ] - r[ i ][ 0 ] ) )
             - (LL)pre * max( 0ll , ( o[ i ][ 0 ] + o[ i ][ 1 ] - r[ i ][ 1 ] ) ) );
    }
    ans += bans;
  }
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
