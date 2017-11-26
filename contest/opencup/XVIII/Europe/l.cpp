#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1514
#define X 202020
typedef long long LL;
int d[ N * 2 ];
int tg[ N * 2 ];
char buf[ 9 ];
int n , tp[ X ] , x[ X ] , y[ X ] , r[ X ];
LL ans;
//inline void add( int xi , int yi , int msk ){
  //tg[ xi ][ yi ] |= msk;
//}
int cb[ 16 ];
//void solve(){
    //for( int j = 1 ; j < N + N ; j ++ ){
      //d[ i ][ j ] += d[ i ][ j - 1 ];
      //if( d[ i ][ j ] )
        //ans += 4;
      //else
        //ans += cb[ (int)tg[ i ][ j ] ];
    //}
//}
set<int> ava;
vector<int> in[ N * 2 ] , out[ N * 2 ];
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < 16 ; i ++ )
    cb[ i ] = __builtin_popcount( i );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s%d%d%d" , buf , &x[ i ] , &y[ i ] , &r[ i ] );

    tp[ i ] = buf[ 0 ] - 'A';
    x[ i ] += N;
    y[ i ] += N;
    r[ i ] >>= 1;
    in[ x[ i ] - r[ i ] ].push_back( i );
    out[ x[ i ] + r[ i ] ].push_back( i );
  }
  for( int i = 0 ; i < N + N ; i ++ ){
    for( int j = 0 ; j < N + N ; j ++ )
      d[ j ] = tg[ j ] = 0;
    for( auto id : in[ i ] )
      ava.insert( id );
    for( auto id : out[ i ] )
      ava.erase( id );
    for( int j : ava ){
      if( tp[ j ] == 0 ){
        d[ y[ j ] - r[ j ] ] ++;
        d[ y[ j ] + r[ j ] ] --;
        continue;
      }
      int dn , up;
      if( i < x[ j ] ){
        int magic = r[ j ] - (x[ j ] - i);
        dn = y[ j ] - magic - 1;
        up = y[ j ] + magic;
        tg[ dn ] |= 3;
        tg[ up ] |= 6;
      }else{
        int magic = r[ j ] - (i - x[ j ] + 1);
        dn = y[ j ] - magic - 1;
        up = y[ j ] + magic;
        tg[ dn ] |= 9;
        tg[ up ] |= 12;
      }
      if( dn + 1 <= up - 1 ){
        d[ dn + 1 ] ++;
        d[ up ] --;
      }
    }
    for( int j = 1 ; j < N + N ; j ++ ){
      d[ j ] += d[ j - 1 ];
      if( d[ j ] ) ans += 4;
      else ans += cb[ tg[ j ] ];
    }
  }
  printf( "%lld.%02lld\n" , ans / 4 , (ans % 4) * 25 );
}
