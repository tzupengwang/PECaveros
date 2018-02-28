#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1035
const int msk = (1 << 14) - 1;
int lb[ 1 << 14 ] , hb[ 1 << 14 ];
int push_left( int cur , int v , bool& ok ){
  if( !cur ) return v;
  int lft = cur & msk;
  int rgt = (cur >> 14) & msk;
  int H = hb[lft]; lft ^= H;

  if (!lft) {
    if (v < H) lft += v;
    else if (v == H) H += v;
    else rgt += H, H = v;
  } else {
    int L = lb[lft];
    if (v <= L) {
      lft += v;
      if (hb[lft] == H) H += hb[lft], lft -= hb[lft];
    } else {
      ok = false;
      return 0;
    }
  }

  return lft + H + (rgt << 14);
}
int push_right( int cur , int v , bool& ok ){
  if( !cur ) return v;
  int lft = cur & msk;
  int rgt = (cur >> 14) & msk;
  int H = hb[lft]; lft ^= H;

  if (!rgt) {
    if (v < H) rgt += v;
    else if (v == H) H += v;
    else lft += H, H = v;
  } else {
    int L = lb[rgt];
    if (v <= L) {
      rgt += v;
      if (hb[rgt] == H) H += hb[rgt], rgt -= hb[rgt];
    }
    else {
      ok = false;
      return 0;
    }
  }

  return lft + H + (rgt << 14);
}
int n , a[ N ];
void init(){
  scanf( "%d" , &n );
  //n = 1024;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    //a[ i ] = 1;
  }
}
unordered_map<int,int> bk[ N ];
char ans[ N ];
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    bk[ i ].clear();
  bk[ 1 ][ a[ 1 ] ] = 0;
  for( int i = 2 ; i <= n ; i ++ ){
    for( auto ps : bk[ i - 1 ] ){
      {
        bool ok = true;
        int to = push_left( ps.first , a[ i ] , ok );
        if( ok )
          bk[ i ][ to ] = (ps.first << 1);
      }
      {
        bool ok = true;
        int to = push_right( ps.first , a[ i ] , ok );
        if( ok )
          bk[ i ][ to ] = (ps.first << 1) | 1;
      }
    }
  }
  for( auto s : bk[ n ] ){
    if( __builtin_popcount( s.first ) == 1 ){
      ans[ n + 1 ] = 0;
      int now = s.first;
      for( int i = n ; i >= 1 ; i -- ){
        ans[ i ] = "lr"[ bk[ i ][ now ] & 1 ];
        now = bk[ i ][ now ] >> 1;
      }
      puts( ans + 1 );
      return;
    }
  }
  puts( "no" );
}
int main(){
  for( int i = 1 ; i < (1 << 14) ; i ++ ){
    lb[ i ] = i & (-i);
    for( int j = 0 ; j < 14 ; j ++ )
      if( (i >> j) & 1 )
        hb[ i ] = (1 << j);
  }
  int t; scanf( "%d" , &t );
  //int t = 10;
  while( t -- ){
    init();
    solve();
  }
}
