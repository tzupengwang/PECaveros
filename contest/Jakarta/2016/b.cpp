#pragma GCC optimize("O3")
#include <bits/stdc++.h>
//#include <bits/extc++.h>
//using namespace __gnu_pbds;
//#include <ext/pb_ds/assoc_container.hpp>
//typedef cc_hash_table<int,int> umap_t;
using namespace std;
typedef long long LL;
#define N 50505
const int base = 27;
int n;
char c[ N ][ 12 ];
int len[ N ];
LL hsh[ N ][ 11 ] , bs[ 12 ];
void build(){
  bs[ 0 ] = 1;
  for( int i = 1 ; i < 12 ; i ++ )
    bs[ i ] = bs[ i - 1 ] * 27;
}
int _cs;
unordered_set<LL> mp[ 12 ];
unordered_map<LL,int> mc[ 12 ] , m2[ 12 ];
//umap_t mc[ 12 ] , m2[ 12 ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < 12 ; i ++ ){
    mp[ i ].clear();
    mc[ i ].clear();
    m2[ i ].clear();
  }
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , c[ i ] );
    len[ i ] = strlen( c[ i ] );
    LL hsvl = 0;
    for( int j = 0 ; j < len[ i ] ; j ++ ){
      hsvl = hsvl * 27 + c[ i ][ j ] - 'a';
      hsh[ i ][ j ] = hsvl;
    }
    mp[ len[ i ] ].insert( hsvl );
    //mp[ len[ i ] ][ hsvl ] = 1;
    for( int j = 0 ; j < len[ i ] ; j ++ ){
      LL thsh = hsvl - ( c[ i ][ j ] - 'a' ) * bs[ len[ i ] - j - 1 ]
                     + 26LL                  * bs[ len[ i ] - j - 1 ];
      mc[ len[ i ] ][ thsh ] ++;
    }
  }
  for( int i = 0 ; i < n ; i ++ ){
    if( len[ i ] > 1 ){ // delete
      for( int j = 0 ; j < len[ i ] ; j ++ ){
        LL thsh = hsh[ i ][ len[ i ] - 1 ] - hsh[ i ][ j ] * bs[ len[ i ] - j - 1 ];
        if( j ) thsh += hsh[ i ][ j - 1 ] * bs[ len[ i ] - j - 1 ];
        m2[ len[ i ] - 1 ][ thsh ] ++;
      }
    }
  }
}
void solve(){
  int bst = -1 , who = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int got = 0;
    if( len[ i ] > 1 ){ // delete
      for( int j = 0 ; j < len[ i ] ; j ++ ){
        LL thsh = hsh[ i ][ len[ i ] - 1 ] - hsh[ i ][ j ] * bs[ len[ i ] - j - 1 ];
        if( j ) thsh += hsh[ i ][ j - 1 ] * bs[ len[ i ] - j - 1 ];
        auto it = mp[ len[ i ] - 1 ].find( thsh );
        if( it != mp[ len[ i ] - 1 ].end() ) got ++;
      }
    }
    { // change
      for( int j = 0 ; j < len[ i ] ; j ++ ){
        LL thsh = hsh[ i ][ len[ i ] - 1 ] - ( c[ i ][ j ] - 'a' ) * bs[ len[ i ] - j - 1 ] +
                                             26 * bs[ len[ i ] - j - 1 ];
        got += mc[ len[ i ] ][ thsh ] - 1;
      }
    }
    auto it = m2[ len[ i ] ].find( hsh[ i ][ len[ i ] - 1 ] );
    if( it != m2[ len[ i ] ].end() )
      got += it->second;
    if( got > bst ){
      bst = got;
      who = i;
    }
  }
  printf( "Case #%d: %s\n" , ++ _cs , c[ who ] );
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
