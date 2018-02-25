#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
#define sN 100
#define BS 13131
inline int add( int a , int b , int mod ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b , int mod ){
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul( LL a , int b , int mod ){
  a *= b;
  return a >= mod ? a % mod : a;
}
const int mod1 = 1000000009;
const int mod2 = 1000000007;
int n , m;
int st[ N ] , slen[ N ];
LL goal[ N ];
char c[ N ] , p[ N ] , np[ N + N ];
int fl[ N ] , plen;
void solve2(){
  fl[ 0 ] = -1;
  for( int i = 1 , f = -1 ; i < plen ; i ++ ){
    while( f >= 0 and p[ f + 1 ] != p[ i ] ) f = fl[ f ];
    if( p[ f + 1 ] == p[ i ] ) f ++;
    fl[ i ] = f;
  }
  int ans = 0 , pre = 0;
  for( int i = 1 , f = -1 ; i <= n ; i ++ ){
    while( f >= 0 and p[ f + 1 ] != c[ i ] ) f = fl[ f ];
    if( p[ f + 1 ] == c[ i ] ) f ++;
    if( f + 1 == plen ){
      if( ans == 0 or pre + plen <= i ){
        ans ++;
        pre = i;
      }
      f = fl[ f ];
    }
  }
  printf( "%d\n" , ans );
}
void init(){
  scanf( "%d%d" , &n , &m );
  scanf( "%s" , c + 1 );
}
unordered_map<LL,int> ans , pre;
void pre_solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    LL hs1 = 0 , hs2 = 0;
    for( int j = 1 ; j <= sN and i + j - 1 <= n ; j ++ ){
      hs1 = add( mul( hs1 , BS , mod1 ) , c[ i + j - 1 ] , mod1 );
      hs2 = add( mul( hs2 , BS , mod2 ) , c[ i + j - 1 ] , mod2 );
      LL hsvl = (hs1 << 32) | hs2;
      auto it = pre.find( hsvl );
      if( it == pre.end() )
        continue;
      if( it->second + j <= i ){
        pre[ hsvl ] = i;
        ans[ hsvl ] ++;
      }
    }
  }
}
void solve(){
  int ptr = 0;
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%s" , np + ptr );
    st[ i ] = ptr;
    slen[ i ] = strlen( np + ptr );

    if( slen[ i ] <= sN ){
      LL hs1 = 0 , hs2 = 0;
      for( int j = 0 ; j < slen[ i ] ; j ++ ){
        hs1 = add( mul( hs1 , BS , mod1 ) , np[ st[ i ] + j ] , mod1 );
        hs2 = add( mul( hs2 , BS , mod2 ) , np[ st[ i ] + j ] , mod2 );
      }
      LL hsvl = (hs1 << 32) | hs2;
      goal[ i ] = hsvl;
      pre[ hsvl ] = -N;
    }
    
    ptr += slen[ i ] + 1;
  }
  pre_solve();
  for( int i = 0 ; i < m ; i ++){
  //while( m -- ){
    for( int j = 0 ; j < slen[ i ] ; j ++ )
      p[ j ] = np[ st[ i ] + j ];
    p[ slen[ i ] ] = 0;
    plen = slen[ i ];
    //scanf( "%s" , p );
    //plen = strlen( p );
    if( plen <= sN ){
      auto it = ans.find( goal[ i ] );
      int rans = 0;
      if( it != ans.end() ) rans = it->second;
      printf( "%d\n" , rans );
      continue;
    }
    solve2();
  }
}
int main(){
  init();
  solve();
}
