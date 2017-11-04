#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 4040
#define BS 13131
inline int add( int a , int b , int mod ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , int b , int mod ){
  a *= b;
  return a >= mod ? a % mod : a;
}
#include <bits/extc++.h>
using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp>
typedef cc_hash_table<LL,int> umap_t;
const int mods[ 2 ] = { 1000000007 , 1000000009 };
struct Int{
  int vl[ 2 ];
  Int( int vv = 0 ){
    vl[ 0 ] = vl[ 1 ] = vv;
  }
  LL value(){
    return (LL)vl[ 0 ] * mods[ 1 ] + vl[ 1 ];
  }
  Int operator+( const Int& he ) const{
    Int ret;
    for( int i = 0 ; i < 2 ; i ++ )
      ret.vl[ i ] = add( vl[ i ] , he.vl[ i ] , mods[ i ] );
    return ret;
  }
  Int operator*( const Int& he ) const{
    Int ret ;
    for( int i = 0 ; i < 2 ; i ++ )
      ret.vl[ i ] = mul( vl[ i ] , he.vl[ i ] , mods[ i ] );
    return ret;
  }
};
LL hsh[ N ];
umap_t cnt[ N ];
//unordered_set<LL> cnt[ N ];
char c[ N ];
int main(){
  Int bs( BS );
  {
    scanf( "%s" , c );
    //for( int i = 0 ; i < 4000 ; i ++ )
      //c[ i ] = 'a' + rand() % 26;
    int len = strlen( c );
    for( int i = 0 ; i < len ; i ++ ){
      int tcnt[ 26 ] = {};
      for( int j = i ; j < len ; j ++ ){
        tcnt[ c[ j ] - 'a' ] ++;
        Int vl;
        for( int k = 0 ; k < 26 ; k ++ )
          vl = vl * bs + Int( tcnt[ k ] );
        //cnt[ j - i + 1 ].insert( vl.value() );
        cnt[ j - i + 1 ][ vl.value() ] = 1;
      }
    }
  }
  int ans = 0;
  {
    scanf( "%s" , c );
    //for( int i = 0 ; i < 4000 ; i ++ )
      //c[ i ] = 'a' + rand() % 26;
    int len = strlen( c );
    for( int i = 0 ; i < len ; i ++ ){
      int tcnt[ 26 ] = {};
      for( int j = i ; j < len ; j ++ ){
        tcnt[ c[ j ] - 'a' ] ++;
        if( j - i + 1 <= ans ) continue;
        Int vl;
        for( int k = 0 ; k < 26 ; k ++ )
          vl = vl * bs + Int( tcnt[ k ] );
        LL tar = vl.value();
        if( cnt[ j - i + 1 ].find( tar ) != cnt[ j - i + 1 ].end() )
          ans = max( ans , j - i + 1 );
      }
    }
  }
  cout << ans << endl;
}
