#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
bool np[ N ];
vector<int> fac[ N ] , pos[ N ];
int BIT[ N ] , lb[ N ];
void build(){
  for( int i = 2 ; i < N ; i ++ ) if( !np[ i ] ){
    for( int j = i ; j < N ; j += i ){
      np[ j ] = true;
      fac[ j ].push_back( i );
    }
  }
  for( int i = 1 ; i < N ; i ++ ) BIT[ i ] = N;
  for( int i = 1 ; i < N ; i ++ ) lb[ i ] = i & (-i);
}
void modify( int p , int x ){
  p += 500005;
  for( int i = p ; i < N ; i += lb[ i ] )
    BIT[ i ] = min( BIT[ i ] , x );
}
void fuck( int p , int x ){
  p += 500005;
  for( int i = p ; i < N ; i += lb[ i ] )
    BIT[ i ] = x;
}
int query( int p ){
  p += 500005;
  int ret = N;
  for( int i = p ; i ; i -= lb[ i ] )
    ret = min( ret , BIT[ i ] );
  return ret;
}
int n , a[ N ];
void init(){
  //srand( time( 0 ) );
  scanf( "%d" , &n );
  //n = 500000;
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
    //a[ i ] = (long long)rand() * rand() % 1000000 + 1;
}
int al , ar , alen;
int ap[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j : fac[ a[ i ] ] )
      pos[ j ].push_back( i );
  for( int i = 2 ; i < N ; i ++ ){
    if( pos[ i ].empty() ) continue;
    int sz = (int)pos[ i ].size();
    for( int j = 1 ; j <= sz ; j ++ ){
      ap[ j - 1 ] = pos[ i ][ j - 1 ] - 1;
      modify( 2 * ( j - 1 ) - ap[ j - 1 ] , j - 1 );
      int bst = query( j + j - pos[ i ][ j - 1 ] );
      if( bst < N ){ // position
        int bl = ap[ bst ]; // not include
        int br = pos[ i ][ j - 1 ];
        int cc = j - bst;
        int mr = cc + cc - ( br - bl );
        {
          int mst = min( bl , mr );
          mr -= mst;
          bl -= mst;
        }
        {
          int mst = min( n - br , mr );
          br += mst;
        }
        if( br - bl > alen ){
          alen = br - bl;
          al = bl + 1; 
          ar = br; 
        }
      }
    }
    for( int j = 1 ; j <= sz ; j ++ )
      fuck( 2 * ( j - 1 ) - ap[ j - 1 ] , N );
  }
  printf( "%d %d\n" , al , ar );
}
int main(){
  build();
  init();
  solve();
}
